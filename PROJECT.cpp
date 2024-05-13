#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip> // for setw
#include <limits>
#include <regex> // for regular expressions

using namespace std;

// Forward declaration of validateDateInput function
string validateDateInput();

// Interface
class CyclePhase {
public:
    virtual void recordData() = 0;
    virtual string getName() = 0;
    virtual void storeDataToFile() = 0;
    virtual void recordSymptoms() = 0;
    virtual void recordDates() = 0;
};

string validateDateInput() {
    string date;
    // This regex matches MM/DD/YYYY format dates, with MM from 01 to 12, DD from 01 to 31, and YYYY being any four-digit year
    regex datePattern("((0?[1-9])|(1[0-2]))/((0?[1-9])|([1-2][0-9])|(3[0-1]))/([0-9]{4})");
    
    while (true) 
    {
        cin >> date;
        if (regex_match(date, datePattern)) 
        {
            // Extract month, day, and year from the date string
            int month = stoi(date.substr(0, 2));
            int day = stoi(date.substr(3, 2));
            int year = stoi(date.substr(6, 4));

            // Get current system date
            time_t now = time(0);
            tm *ltm = localtime(&now);
            int currentYear = 1900 + ltm->tm_year;
            int currentMonth = 1 + ltm->tm_mon;
            int currentDay = ltm->tm_mday;

            // Check if the entered date is a date representing the future and if the days are accurate
            if (year > currentYear ||
                (year == currentYear && month > currentMonth) ||
                (year == currentYear && month == currentMonth && day > currentDay) ||
                day < 1 ||
                day > 31 ||
                (month == 2 && day > 28) ||
                ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)) 
                {
                    cout << "Invalid date. Please enter a valid date: ";
                    continue;
                }
            break;
        } 
        else 
        {
            cout << "Invalid date format. Please enter date in MM/DD/YYYY format: ";
        }
    }
    return date;
}

// Class representing Phase 1 of the Menstrual Cycle
class FollicularPhase : public CyclePhase {
public:
    void recordData() 
    {
        cout << "Recording data for the Follicular Phase..." << endl;
        char choice;
        cout << "\nDo you want to record symptoms? (y/n): ";
        cin >> choice;
        bool flag = false;
        // Use exception handling to ensure accurate records
        try {
            if (choice == 'y' || choice == 'Y') 
            {
                recordSymptoms();
                flag = true;
            } 
            else if (choice == 'n' || choice == 'N') 
            {
                throw("No symptom to append file.\n");
            } 
            else 
            {
                throw("Invalid choice.\n");
            }
        } 
        catch (const char* msg) 
        {
            cout << msg;
        } 
        catch (...) 
        {
            cout << "Invalid choice.\n";
        }
        cout << "\nDo you want to record dates? (y/n): ";
        cin >> choice;
        try {
            if (choice == 'y' || choice == 'Y') 
            {
                recordDates();
                flag = true;
            } 
            else if (choice == 'n' || choice == 'N') 
            {
                throw("No date to append file.\n");
            } 
            else 
            {
                throw("Invalid choice.\n");
            }
        } 
        catch (const char* msg) 
        {
            cout << msg;
        } 
        catch (...) 
        {
            cout << "Invalid choice.\n";
        }
        // Store the recorded data in files
        try 
        {
            if (flag)
                storeDataToFile();
            else
                throw("No data to append to follicular_data.txt\n");
        } 
        catch (const char* msg) 
        {
            cout << msg;
        }
    }

    string getName() 
    {
        return "Follicular Phase";
    }

    void recordSymptoms() 
    {
        cout << "Enter symptoms for the Follicular Phase (enter 'done' to finish): ";
        string symptom;
        while (true) 
        {
            cin >> symptom;
            if (symptom == "done") {
                break; // Exit the loop and stop recording symptoms.
            }
            symptoms.push_back(symptom);
        }
        // Clear input stream to prevent infinite loop
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    void recordDates() 
    {
        cout << "Enter start date of the Follicular Phase (MM/DD/YYYY): ";
        startDate = validateDateInput();
        cout << "Enter end date of the Follicular Phase (MM/DD/YYYY): ";
        endDate = validateDateInput();
    }

    // Utlising friend function
    friend string validateDateInput();

    void storeDataToFile() 
    {
        ofstream file("follicular_data.txt", ios_base::app); // Open a file for appending
        if (file.is_open()) {
            if (!symptoms.empty() || (!startDate.empty() && !endDate.empty())) {
                // Formatting the .txt files into table format to make them more presentable for the user
                file << "+---------------------+---------------------+---------------------+" << endl; // Top border
                file << "| " << left << setw(20) << "Start Date" << "| " << setw(20) << "End Date" << "| " << setw(20) << "Symptoms" << "|" << endl;
                file << "|---------------------|---------------------|---------------------|" << endl;
                file << "| " << left << setw(20) << startDate << "| " << setw(20) << endDate << "| " << setw(20) << "" << "|" << endl;
                if (!symptoms.empty()) {
                    for (const string& symptom : symptoms) {
                        file << "| " << setw(20) << "" << "| " << setw(20) << "" << "| " << setw(20) << symptom << "|" << endl;
                    }
                }
                file << "+---------------------+---------------------+---------------------+" << endl; // Bottom border
                file << endl;
            }
            file.close(); // Close the file
            cout << "\nData appended to follicular_data.txt" << endl;
        } 
        else 
        {
            cerr << "Error: Unable to open file for writing" << endl;
        }
    }

private:
    string startDate;
    string endDate;
    vector<string> symptoms;
};

// Class representing Phase 2 of the Menstrual Cycle
class OvulationPhase : public CyclePhase {
public:
    void recordData() 
    {
        cout << "Recording data for the Ovulation Phase..." << endl;
        char choice;
        cout << "\nDo you want to record symptoms? (y/n): ";
        cin >> choice;
        bool flag = false;
        try {
            if (choice == 'y' || choice == 'Y') 
            {
                recordSymptoms();
                flag = true;
            } 
            else if (choice == 'n' || choice == 'N') 
            {
                throw("No symptom to append file.\n");
            } 
            else 
            {
                throw("Invalid choice.\n");
            }
        } 
        catch (const char* msg) 
        {
            cout << msg;
        } 
        catch (...) 
        {
            cout << "Invalid choice.\n";
        }
        cout << "\nDo you want to record dates? (y/n): ";
        cin >> choice;
        try {
            if (choice == 'y' || choice == 'Y') 
            {
                recordDates();
                flag = true;
            } 
            else if (choice == 'n' || choice == 'N') 
            {
                throw("No date to append file.\n");
            } 
            else 
            {
                throw("Invalid choice.\n");
            }
        } 
        catch (const char* msg) 
        {
            cout << msg;
        } 
        catch (...) 
        {
            cout << "Invalid choice.\n";
        }
        // Store the recorded data in files
        try 
        {
            if (flag)
                storeDataToFile();
            else
                throw("No data to append to ovulation_data.txt\n");
        } catch (const char* msg) {
            cout << msg;
        }
    }

    string getName() 
    {
        return "Ovulation Phase";
    }

    void recordSymptoms() 
    {
        cout << "Enter symptoms for the Ovulation Phase (enter 'done' to finish): ";
        string symptom;
        while (true) 
        {
            cin >> symptom;
            if (symptom == "done") {
                break; // Exit the loop and stop recording symptoms
            }
            symptoms.push_back(symptom);
        }
        // Clear input stream to prevent infinite loop
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    void recordDates() 
    {
        cout << "Enter start date of the Ovulation Phase (MM/DD/YYYY): ";
        startDate = validateDateInput();
        cout << "Enter end date of the Ovulation Phase (MM/DD/YYYY): ";
        endDate = validateDateInput();
    }

    // Utlising friend function to enhance code readability and reduce redundancy
    friend string validateDateInput();

    void storeDataToFile() 
    {
        ofstream file("ovulation_data.txt", ios_base::app); // Open a file for appending
        if (file.is_open()) {
            if (!symptoms.empty() || (!startDate.empty() && !endDate.empty())) 
            {
                // Formatting as table
                file << "+---------------------+---------------------+---------------------+" << endl; // Top border
                file << "| " << left << setw(20) << "Start Date" << "| " << setw(20) << "End Date" << "| " << setw(20) << "Symptoms" << "|" << endl;
                file << "|---------------------|---------------------|---------------------|" << endl;
                file << "| " << left << setw(20) << startDate << "| " << setw(20) << endDate << "| " << setw(20) << "" << "|" << endl;
                if (!symptoms.empty()) {
                    for (const string& symptom : symptoms) {
                        file << "| " << setw(20) << "" << "| " << setw(20) << "" << "| " << setw(20) << symptom << "|" << endl;
                    }
                }
                file << "+---------------------+---------------------+---------------------+" << endl; // Bottom border
                file << endl;
            }
            file.close(); // Close the file
            cout << "\nData appended to ovulation_data.txt" << endl;
        } 
        else 
        {
            cerr << "Error: Unable to open file for writing" << endl;
        }
    }

private:
    string startDate;
    string endDate;
    vector<string> symptoms;
};

// Class representing Phase 3 of the Menstrual Cycle
class LutealPhase : public CyclePhase {
public:
    void recordData() 
    {
        cout << "Recording data for the Luteal Phase..." << endl;
        char choice;
        cout << "\nDo you want to record symptoms? (y/n): ";
        cin >> choice;
        bool flag = false;
        try 
        {
            if (choice == 'y' || choice == 'Y') 
            {
                recordSymptoms();
                flag = true;
            } 
            else if (choice == 'n' || choice == 'N') 
            {
                throw("No symptom to append file.\n");
            } 
            else 
            {
                throw("Invalid choice.\n");
            }
        } 
        catch (const char* msg) 
        {
            cout << msg;
        } 
        catch (...) 
        {
            cout << "Invalid choice.\n";
        }
        cout << "\nDo you want to record dates? (y/n): ";
        cin >> choice;
        try 
        {
            if (choice == 'y' || choice == 'Y') 
            {
                recordDates();
                flag = true;
            } 
            else if (choice == 'n' || choice == 'N') {
                throw("No date to append file.\n");
            } 
            else {
                throw("Invalid choice.\n");
            }
        } 
        catch (const char* msg) 
        {
            cout << msg;
        } 
        catch (...) 
        {
            cout << "Invalid choice.\n";
        }
        // Store the recorded data in files
        try 
        {
            if (flag)
                storeDataToFile();
            else
                throw("No data to append to luteal_data.txt\n");
        } 
        catch (const char* msg) 
        {
            cout << msg;
        }
    }

    string getName() 
    {
        return "Luteal Phase";
    }

    void recordSymptoms() 
    {
        cout << "Enter symptoms for the Luteal Phase (enter 'done' to finish): ";
        string symptom;
        while (true) {
            cin >> symptom;
            if (symptom == "done") 
            {
                break; // Exit the loop and stop recording symptoms
            }
            symptoms.push_back(symptom);
        }
        // Clear input stream to prevent infinite loop
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    void recordDates() 
    {
        cout << "Enter start date of the Luteal Phase (MM/DD/YYYY): ";
        startDate = validateDateInput();
        cout << "Enter end date of the Luteal Phase (MM/DD/YYYY): ";
        endDate = validateDateInput();
    }
    // Utilising friend function to enhance code readability and reduce redundancy
    friend string validateDateInput();

    void storeDataToFile() 
    {
        ofstream file("luteal_data.txt", ios_base::app); // Open a file for appending
        if (file.is_open()) 
        {
            // Formatting as table
            if (!symptoms.empty() || (!startDate.empty() && !endDate.empty())) {
                file << "+---------------------+---------------------+---------------------+" << endl; // Top border
                file << "| " << left << setw(20) << "Start Date" << "| " << setw(20) << "End Date" << "| " << setw(20) << "Symptoms" << "|" << endl;
                file << "|---------------------|---------------------|---------------------|" << endl;
                file << "| " << left << setw(20) << startDate << "| " << setw(20) << endDate << "| " << setw(20) << "" << "|" << endl;
                if (!symptoms.empty()) {
                    for (const string& symptom : symptoms) {
                        file << "| " << setw(20) << "" << "| " << setw(20) << "" << "| " << setw(20) << symptom << "|" << endl;
                    }
                }
                file << "+---------------------+---------------------+---------------------+" << endl; // Bottom border
                file << endl;
            }
            file.close(); // Close the file
            cout << "\nData appended to luteal_data.txt" << endl;
        } 
        else 
        {
            cerr << "Error: Unable to open file for writing" << endl;
        }
    }

private:
    string startDate;
    string endDate;
    vector<string> symptoms;
};

// Class representing Phase 4 of the Menstrual Cycle
class MenstrualPhase : public CyclePhase {
public:
    void recordData() 
    {
        cout << "Recording data for the Menstrual Phase..." << endl;
        char choice;
        cout << "\nDo you want to record symptoms? (y/n): ";
        cin >> choice;
        bool flag = false;
        try 
        {
            if (choice == 'y' || choice == 'Y') 
            {
                recordSymptoms();
                flag = true;
            } 
            else if (choice == 'n' || choice == 'N') 
            {
                throw("No symptom to append file.\n");
            } 
            else 
            {
                throw("Invalid choice.\n");
            }
        } 
        catch (const char* msg) 
        {
            cout << msg;
        } 
        catch (...) 
        {
            cout << "Invalid choice.\n";
        }
        cout << "\nDo you want to record dates? (y/n): ";
        cin >> choice;
        try 
        {
            if (choice == 'y' || choice == 'Y') 
            {
                recordDates();
                flag = true;
            } 
            else if (choice == 'n' || choice == 'N') 
            {
                throw("No date to append file.\n");
            } 
            else 
            {
                throw("Invalid choice.\n");
            }
        } 
        catch (const char* msg) 
        {
            cout << msg;
        } 
        catch (...) 
        {
            cout << "Invalid choice.\n";
        }
        // Store the recorded data in files
        try 
        {
            if (flag)
                storeDataToFile();
            else
                throw("No data to append to menstrual_data.txt\n");
        } 
        catch (const char* msg) 
        {
            cout << msg;
        }
    }

    string getName() 
    {
        return "Menstrual Phase";
    }

    void recordSymptoms() 
    {
        cout << "Enter symptoms for the Menstrual Phase (enter 'done' to finish): ";
        string symptom;
        while (true) 
        {
            cin >> symptom;
            if (symptom == "done") 
            {
                break; // Exit the loop if the user inputs "done"
            }
            symptoms.push_back(symptom);
        }
        // Clear input stream to prevent infinite loop
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    void recordDates() 
    {
        cout << "Enter start date of the Menstrual Phase (MM/DD/YYYY): ";
        startDate = validateDateInput();
        cout << "Enter end date of the Menstrual Phase (MM/DD/YYYY): ";
        endDate = validateDateInput();
    }

    // Utilising friend function to enhance code readability and reduce redundancy
    friend string validateDateInput();

    void storeDataToFile() {
        ofstream file("menstrual_data.txt", ios_base::app); // Open a file for appending
        if (file.is_open()) 
        {
            // Formatting as table
            if (!symptoms.empty() || (!startDate.empty() && !endDate.empty())) {
                file << "+---------------------+---------------------+---------------------+" << endl; // Top border
                file << "| " << left << setw(20) << "Start Date" << "| " << setw(20) << "End Date" << "| " << setw(20) << "Symptoms" << "|" << endl;
                file << "|---------------------|---------------------|---------------------|" << endl;
                file << "| " << left << setw(20) << startDate << "| " << setw(20) << endDate << "| " << setw(20) << "" << "|" << endl;
                if (!symptoms.empty()) {
                    for (const string& symptom : symptoms) {
                        file << "| " << setw(20) << "" << "| " << setw(20) << "" << "| " << setw(20) << symptom << "|" << endl;
                    }
                }
                file << "+---------------------+---------------------+---------------------+" << endl; // Bottom border
                file << endl;
            }
            file.close(); // Close the file
            cout << "\nData appended to menstrual_data.txt" << endl;
        } 
        else 
        {
            cerr << "Error: Unable to open file for writing" << endl;
        }
    }

private:
    string startDate;
    string endDate;
    vector<string> symptoms;
};

class SymptomTracker {
public:
    static void trackSymptoms() {
        cout << "Welcome to symptom soother!" << endl;
        cout << "Please choose from the following symptoms:" << endl;
        cout << "1. Headaches" << endl;
        cout << "2. Cramps" << endl;
        cout << "3. Diarrhea" << endl;
        cout << "4. Fatigue" << endl;
        cout << "5. Backache" << endl;
        cout << "6. Acne" << endl;
        cout << "7. Cravings" << endl;
        cout << "8. Insomnia" << endl;
        cout << "9. Other" << endl;

        int choice;
        cout << "Enter your choice (1-9): ";
        cin >> choice;

        switch (choice) {
            case 1:
                recommendHeadache();
                break;
            case 2:
                recommendCramps();
                break;
            case 3:
                recommendDiarrhea();
                break;
            case 4:
                recommendFatigue();
                break;
            case 5:
                recommendBackache();
                break;
            case 6:
                recommendAcne();
                break;
            case 7:
                recommendCravings();
                break;
            case 8:
                recommendInsomnia();
                break;
            case 9:
                recommendOther();
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    }

private:
    static void recommendHeadache() {
        cout << "Recommendations for headaches:" << endl;
        cout << "- Rest in a quiet, dark room" << endl;
        cout << "- Apply a cold compress to your forehead" << endl;
        cout << "- Drink plenty of water" << endl;
        cout << "- Take pain relievers such as ibuprofen or acetaminophen" << endl;
    }

    static void recommendCramps() {
        cout << "Recommendations for cramps:" << endl;
        cout << "- Apply a heating pad to your abdomen" << endl;
        cout << "- Take a warm bath" << endl;
        cout << "- Practice relaxation techniques such as deep breathing" << endl;
        cout << "- Take pain relievers such as ibuprofen or acetaminophen" << endl;
        cout << "\n\n On a scale of 1 to 4, how severe are your cramps? (1 being mild, 4 being severe): ";
        int severity;
        cin >> severity;
        if (severity >= 3) {
            cout << "Consider consulting a healthcare provider for further evaluation and treatment." << endl;
        }
        if (severity == 1 || severity == 2) {
            cout << "\n-Pain should subside in a few hours take pain killers according to doctor" << endl;
        }
    }

    static void recommendDiarrhea() {
        cout << "Recommendations for diarrhea:" << endl;
        cout << "- Drink plenty of fluids to stay hydrated" << endl;
        cout << "- Eat bland, easy-to-digest foods such as bananas, rice, applesauce, and toast (BRAT diet)" << endl;
        cout << "- Avoid dairy products, caffeine, and fatty or spicy foods" << endl;
        cout << "- Consider taking over-the-counter medications such as loperamide (Imodium) to help reduce diarrhea" << endl;
    }

    static void recommendFatigue() {
        cout << "Recommendations for fatigue:" << endl;
        cout << "- Ensure you're getting enough sleep each night" << endl;
        cout << "- Take short breaks during the day to rest" << endl;
        cout << "- Stay hydrated and eat a balanced diet" << endl;
        cout << "- Consider light exercise, such as walking, to boost energy levels" << endl;
    }

    static void recommendBackache() {
        cout << "Recommendations for backache:" << endl;
        cout << "- Practice good posture" << endl;
        cout << "- Use ergonomic chairs or back supports" << endl;
        cout << "- Apply heat or cold packs to the affected area" << endl;
        cout << "- Perform gentle stretches and exercises to strengthen the back muscles" << endl;
    }

    static void recommendAcne() {
        cout << "Recommendations for acne:" << endl;
        cout << "- Cleanse your skin regularly with a gentle cleanser" << endl;
        cout << "- Avoid touching your face too often" << endl;
        cout << "- Use non-comedogenic moisturizers and makeup products" << endl;
        cout << "- Consider over-the-counter acne treatments containing benzoyl peroxide or salicylic acid" << endl;
    }

    static void recommendCravings() {
        cout << "Recommendations for cravings:" << endl;
        cout << "- Opt for healthier alternatives to satisfy cravings, such as fruits or nuts" << endl;
        cout << "- Practice portion control to avoid overeating" << endl;
        cout << "- Keep yourself busy with activities to distract from cravings" << endl;
        cout << "- Address underlying emotional triggers for cravings through mindfulness or therapy" << endl;
    }

    static void recommendInsomnia() {
        cout << "Recommendations for insomnia:" << endl;
        cout << "- Establish a regular sleep schedule and bedtime routine" << endl;
        cout << "- Create a relaxing sleep environment, with minimal noise and light" << endl;
        cout << "- Limit screen time before bed, as blue light can interfere with sleep" << endl;
        cout << "- Consider relaxation techniques such as meditation or deep breathing exercises" << endl;
    }

    static void recommendOther() {
        cout << "For other symptoms, it is recommended to consult a healthcare provider for personalized advice and treatment." << endl;
    }
};

int main() {
    cout << "♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥" << endl;
    cout << "♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥" << endl;
    cout << "♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥" << endl;
    cout << "  - - - - - - - - - - - - - - - - - - -  " << endl;
    cout << "      W e l c o m e   t o   M e n T o r  " << endl;
    cout << "  - - - - - - - - - - - - - - - - - - -  " << endl;
    cout << "♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥" << endl;
    cout << "♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥" << endl;
    cout << "♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥" << endl;
    
    while (true) {
        int choice;
        cout << "\nMenu:" << endl;
        cout << "1. Symptom Management" << endl;
        cout << "2. Record Follicular Phase Data" << endl;
        cout << "3. Record Ovulation Phase Data" << endl;
        cout << "4. Record Luteal Phase Data" << endl;
        cout << "5. Record Menstrual Phase Data" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                SymptomTracker::trackSymptoms();
                break;
            case 2: {
                FollicularPhase follicular;
                follicular.recordData();
                break;
            }
            case 3: {
                OvulationPhase ovulation;
                ovulation.recordData();
                break;
            }
            case 4: {
                LutealPhase luteal;
                luteal.recordData();
                break;
            }
            case 5: {
                MenstrualPhase menstrual;
                menstrual.recordData();
                break;
            }
            case 6:
                cout << "\nThank you for using MenTor.\nExiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice!" << endl;
                break;
        }
    }

    return 0;
}
