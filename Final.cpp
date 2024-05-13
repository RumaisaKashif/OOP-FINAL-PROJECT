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

class CyclePhase {
public:
    virtual void recordData() = 0;
    virtual string getName() = 0;
    virtual void storeDataToFile() = 0;
    virtual void recordSymptoms() = 0;
    virtual void recordDates() = 0;
};

// Declaration of validateDateInput function
string validateDateInput() {
    string date;
    regex datePattern("(0[1-9]|1[0-2])/(0[1-9]|[1-2][0-9]|3[0-1])/([0-9]{4})");
    while (true) {
        cin >> date;
        if (regex_match(date, datePattern)) {
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

            // Check if the entered date is in the future or if the month days are accurate
            if (year > currentYear ||
                (year == currentYear && month > currentMonth) ||
                (year == currentYear && month == currentMonth && day > currentDay) ||
                day < 1 ||
                day > 31 ||
                (month == 2 && day > 28) ||
                ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)) {
                cout << "Invalid date. Please enter a valid date: ";
                continue;
            }
            break;
        } else {
            cout << "Invalid date format. Please enter in MM/DD/YYYY format: ";
        }
    }
    return date;
}

class FollicularPhase : public CyclePhase {
public:
    void recordData() override {
        cout << "Recording data for the Follicular Phase..." << endl;
        char choice;
        cout << "\nDo you want to record symptoms? (y/n): ";
        cin >> choice;
        bool flag = false;
        try {
            if (choice == 'y' || choice == 'Y') {
                recordSymptoms();
                flag = true;
            } else if (choice == 'n' || choice == 'N') {
                throw("No symptom to append file.\n");
            } else {
                throw("Invalid choice.\n");
            }
        } catch (const char* msg) {
            cout << msg;
        } catch (...) {
            cout << "Invalid choice.\n";
        }
        cout << "\nDo you want to record dates? (y/n): ";
        cin >> choice;
        try {
            if (choice == 'y' || choice == 'Y') {
                recordDates();
                flag = true;
            } else if (choice == 'n' || choice == 'N') {
                throw("No date to append file.\n");
            } else {
                throw("Invalid choice.\n");
            }
        } catch (const char* msg) {
            cout << msg;
        } catch (...) {
            cout << "Invalid choice.\n";
        }
        // Store the recorded data in files
        try {
            if (flag)
                storeDataToFile();
            else
                throw("No data to append to follicular_data.txt\n");
        } catch (const char* msg) {
            cout << msg;
        }
    }

    string getName() override {
        return "Follicular Phase";
    }

    void recordSymptoms() override {
        cout << "Enter symptoms for the Follicular Phase (enter 'done' to finish): ";
        string symptom;
        while (true) {
            cin >> symptom;
            if (symptom == "done") {
                break; // Exit the loop if the user inputs "done"
            }
            symptoms.push_back(symptom);
        }
        // Clear input stream to prevent infinite loop
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    void recordDates() override {
        cout << "Enter start date of the Follicular Phase (MM/DD/YYYY): ";
        startDate = validateDateInput();
        cout << "Enter end date of the Follicular Phase (MM/DD/YYYY): ";
        endDate = validateDateInput();
    }

    friend string validateDateInput();

    void storeDataToFile() override {
        ofstream file("follicular_data.txt", ios_base::app); // Open a file for appending
        if (file.is_open()) {
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
            cout << "\nData appended to follicular_data.txt" << endl;
        } else {
            cerr << "Error: Unable to open file for writing" << endl;
        }
    }

private:
    string startDate;
    string endDate;
    vector<string> symptoms;
};

class OvulationPhase : public CyclePhase {
public:
    void recordData() override {
        cout << "Recording data for the Ovulation Phase..." << endl;
        char choice;
        cout << "\nDo you want to record symptoms? (y/n): ";
        cin >> choice;
        bool flag = false;
        try {
            if (choice == 'y' || choice == 'Y') {
                recordSymptoms();
                flag = true;
            } else if (choice == 'n' || choice == 'N') {
                throw("No symptom to append file.\n");
            } else {
                throw("Invalid choice.\n");
            }
        } catch (const char* msg) {
            cout << msg;
        } catch (...) {
            cout << "Invalid choice.\n";
        }
        cout << "\nDo you want to record dates? (y/n): ";
        cin >> choice;
        try {
            if (choice == 'y' || choice == 'Y') {
                recordDates();
                flag = true;
            } else if (choice == 'n' || choice == 'N') {
                throw("No date to append file.\n");
            } else {
                throw("Invalid choice.\n");
            }
        } catch (const char* msg) {
            cout << msg;
        } catch (...) {
            cout << "Invalid choice.\n";
        }
        // Store the recorded data in files
        try {
            if (flag)
                storeDataToFile();
            else
                throw("No data to append to ovulation_data.txt\n");
        } catch (const char* msg) {
            cout << msg;
        }
    }

    string getName() override {
        return "Ovulation Phase";
    }

    void recordSymptoms() override {
        cout << "Enter symptoms for the Ovulation Phase (enter 'done' to finish): ";
        string symptom;
        while (true) {
            cin >> symptom;
            if (symptom == "done") {
                break; // Exit the loop if the user inputs "done"
            }
            symptoms.push_back(symptom);
        }
        // Clear input stream to prevent infinite loop
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    void recordDates() override {
        cout << "Enter start date of the Ovulation Phase (MM/DD/YYYY): ";
        startDate = validateDateInput();
        cout << "Enter end date of the Ovulation Phase (MM/DD/YYYY): ";
        endDate = validateDateInput();
    }

    friend string validateDateInput();

    void storeDataToFile() override {
        ofstream file("ovulation_data.txt", ios_base::app); // Open a file for appending
        if (file.is_open()) {
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
            cout << "\nData appended to ovulation_data.txt" << endl;
        } else {
            cerr << "Error: Unable to open file for writing" << endl;
        }
    }

private:
    string startDate;
    string endDate;
    vector<string> symptoms;
};

class LutealPhase : public CyclePhase {
public:
    void recordData() override {
        cout << "Recording data for the Luteal Phase..." << endl;
        char choice;
        cout << "\nDo you want to record symptoms? (y/n): ";
        cin >> choice;
        bool flag = false;
        try {
            if (choice == 'y' || choice == 'Y') {
                recordSymptoms();
                flag = true;
            } else if (choice == 'n' || choice == 'N') {
                throw("No symptom to append file.\n");
            } else {
                throw("Invalid choice.\n");
            }
        } catch (const char* msg) {
            cout << msg;
        } catch (...) {
            cout << "Invalid choice.\n";
        }
        cout << "\nDo you want to record dates? (y/n): ";
        cin >> choice;
        try {
            if (choice == 'y' || choice == 'Y') {
                recordDates();
                flag = true;
            } else if (choice == 'n' || choice == 'N') {
                throw("No date to append file.\n");
            } else {
                throw("Invalid choice.\n");
            }
        } catch (const char* msg) {
            cout << msg;
        } catch (...) {
            cout << "Invalid choice.\n";
        }
        // Store the recorded data in files
        try {
            if (flag)
                storeDataToFile();
            else
                throw("No data to append to luteal_data.txt\n");
        } catch (const char* msg) {
            cout << msg;
        }
    }

    string getName() override {
        return "Luteal Phase";
    }

    void recordSymptoms() override {
        cout << "Enter symptoms for the Luteal Phase (enter 'done' to finish): ";
        string symptom;
        while (true) {
            cin >> symptom;
            if (symptom == "done") {
                break; // Exit the loop if the user inputs "done"
            }
            symptoms.push_back(symptom);
        }
        // Clear input stream to prevent infinite loop
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    void recordDates() override {
        cout << "Enter start date of the Luteal Phase (MM/DD/YYYY): ";
        startDate = validateDateInput();
        cout << "Enter end date of the Luteal Phase (MM/DD/YYYY): ";
        endDate = validateDateInput();
    }

    friend string validateDateInput();

    void storeDataToFile() override {
        ofstream file("luteal_data.txt", ios_base::app); // Open a file for appending
        if (file.is_open()) {
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
        } else {
            cerr << "Error: Unable to open file for writing" << endl;
        }
    }

private:
    string startDate;
    string endDate;
    vector<string> symptoms;
};

class MenstrualPhase : public CyclePhase {
public:
    void recordData() override {
        cout << "Recording data for the Menstrual Phase..." << endl;
        char choice;
        cout << "\nDo you want to record symptoms? (y/n): ";
        cin >> choice;
        bool flag = false;
        try {
            if (choice == 'y' || choice == 'Y') {
                recordSymptoms();
                flag = true;
            } else if (choice == 'n' || choice == 'N') {
                throw("No symptom to append file.\n");
            } else {
                throw("Invalid choice.\n");
            }
        } catch (const char* msg) {
            cout << msg;
        } catch (...) {
            cout << "Invalid choice.\n";
        }
        cout << "\nDo you want to record dates? (y/n): ";
        cin >> choice;
        try {
            if (choice == 'y' || choice == 'Y') {
                recordDates();
                flag = true;
            } else if (choice == 'n' || choice == 'N') {
                throw("No date to append file.\n");
            } else {
                throw("Invalid choice.\n");
            }
        } catch (const char* msg) {
            cout << msg;
        } catch (...) {
            cout << "Invalid choice.\n";
        }
        // Store the recorded data in files
        try {
            if (flag)
                storeDataToFile();
            else
                throw("No data to append to menstrual_data.txt\n");
        } catch (const char* msg) {
            cout << msg;
        }
    }

    string getName() override {
        return "Menstrual Phase";
    }

    void recordSymptoms() override {
        cout << "Enter symptoms for the Menstrual Phase (enter 'done' to finish): ";
        string symptom;
        while (true) {
            cin >> symptom;
            if (symptom == "done") {
                break; // Exit the loop if the user inputs "done"
            }
            symptoms.push_back(symptom);
        }
        // Clear input stream to prevent infinite loop
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    void recordDates() override {
        cout << "Enter start date of the Menstrual Phase (MM/DD/YYYY): ";
        startDate = validateDateInput();
        cout << "Enter end date of the Menstrual Phase (MM/DD/YYYY): ";
        endDate = validateDateInput();
    }

    friend string validateDateInput();

    void storeDataToFile() override {
        ofstream file("menstrual_data.txt", ios_base::app); // Open a file for appending
        if (file.is_open()) {
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
        } else {
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
        cout << "4. Other" << endl;

        int choice;
        cout << "Enter your choice (1-4): ";
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
        if(severity=1||2){
            cout<<"\n-Pain should subside in a few hours take pain killers according to doctor"<<endl;
        }
    }

    static void recommendDiarrhea() {
        cout << "Recommendations for diarrhea:" << endl;
        cout << "- Drink plenty of fluids to stay hydrated" << endl;
        cout << "- Eat bland, easy-to-digest foods such as bananas, rice, applesauce, and toast (BRAT diet)" << endl;
        cout << "- Avoid dairy products, caffeine, and fatty or spicy foods" << endl;
        cout << "- Consider taking over-the-counter medications such as loperamide (Imodium) to help reduce diarrhea" << endl;
    }

    static void recommendOther() {
        cout << "For other symptoms, it is recommended to consult a healthcare provider for personalized advice and treatment." << endl;
    }
};

int main() {
    while (true) {
        int choice;
        cout << "\nMenu:" << endl;
        cout << "1. Track Symptoms" << endl;
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
