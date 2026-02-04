// *********************************************************
// Program: StudentAttendanceTracker.cpp
// Course: CCP6114 Programming Fundamentals
// Description: Tracks student attendance by loading,
// displaying, updating, deleting, and saving CSV files.
// *********************************************************

#include <iostream>
#include <fstream>
#include <cctype>
using namespace std;

// ===== CONSTANTS =====
const int MAX_ROW = 100;

// ===== STRUCTS =====
struct Student {
    int id;
    string name;
    int status; // 0 = absent, 1 = present
};

// ===== GLOBAL VARIABLES =====
Student sheet[MAX_ROW];
int rowCount = 0;
string termName = "";

bool termCreated = false;
bool fileLoaded = false;
string loadedFileName = "";

// ===== FUNCTION DECLARATIONS =====
bool isValidInt(string s);
void createTerm();
void readFile();
void displaySheet();
void updateRow();
void deleteRow();
void countRows();
void saveFile();
void menu();

// ===== VALIDATION FUNCTION =====
bool isValidInt(string s){
    if(s.empty()) return false;
    for(char c : s)
        if(!isdigit(c))
            return false;
    return true;
}

// ===== CREATE TERM =====
void createTerm(){
    while(true){
        cout << "Enter term name: ";
        getline(cin, termName);

        if(termName.empty()){
            cout << "Error: Term name cannot be empty. Please try again.\n";
        } else {
            break;
        }
    }

    rowCount = 0;
    fileLoaded = false;
    loadedFileName = "";
    termCreated = true;

    cout << "School term \"" << termName << "\" created successfully.\n";
}

// ===== READ CSV FILE =====
void readFile(){
    if(!termCreated){
        cout << "Error: Please create and name a school term first (Option 1).\n";
        return;
    }

    cout << "Enter CSV file name (e.g., FileName.csv): ";
    string fileName;
    getline(cin, fileName);

    ifstream file(fileName);
    if(!file){
        cout << "Error: File \"" << fileName << "\" not found.\n";
        return;
    }

    rowCount = 0;
    string line;

    while(getline(file, line)){
        if(line.empty()) continue;

        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);

        if(pos1 == string::npos || pos2 == string::npos)
            continue;

        string idStr = line.substr(0, pos1);
        string nameStr = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string statusStr = line.substr(pos2 + 1);

        if(!isValidInt(idStr) || !isValidInt(statusStr))
            continue;

        sheet[rowCount].id = stoi(idStr);
        sheet[rowCount].name = nameStr;
        sheet[rowCount].status = stoi(statusStr);

        rowCount++;
        if(rowCount >= MAX_ROW) break;
    }

    file.close();

    if(rowCount > 0){
        fileLoaded = true;
        loadedFileName = fileName;
        cout << "File loaded successfully. Records read: " << rowCount << endl;
    } else {
        cout << "No valid records found in file.\n";
    }
}

// ===== DISPLAY =====
void displaySheet(){
    if(!fileLoaded){
        cout << "Error: No attendance file loaded.\n";
        return;
    }

    cout << "\nTerm: " << termName << endl;
    cout << "StudentID, Name, Status \n";
    cout << "------------------------\n";

    for(int i = 0; i < rowCount; i++){
        cout << sheet[i].id << ", "
             << sheet[i].name << ", "
             << sheet[i].status << endl;
    }
}

// ===== UPDATE =====
void updateRow(){
    if(!fileLoaded){
        cout << "Error: Load a file first.\n";
        return;
    }

    cout << "Enter StudentID to update: ";
    string input;
    getline(cin, input);

    if(!isValidInt(input)){
        cout << "Invalid StudentID.\n";
        return;
    }

    int id = stoi(input);

    for(int i = 0; i < rowCount; i++){
        if(sheet[i].id == id){
            cout << "Enter new status (0 = Absent, 1 = Present): ";
            string statusInput;
            getline(cin, statusInput);

            if(!isValidInt(statusInput)){
                cout << "Invalid status.\n";
                return;
            }

            int status = stoi(statusInput);
            if(status != 0 && status != 1){
                cout << "Status must be 0 or 1.\n";
                return;
            }

            sheet[i].status = status;
            cout << "Attendance updated successfully.\n";
            return;
        }
    }

    cout << "StudentID not found.\n";
}

// ===== DELETE =====
void deleteRow(){
    if(!fileLoaded){
        cout << "Error: Load a file first.\n";
        return;
    }

    cout << "Enter StudentID to delete: ";
    string input;
    getline(cin, input);

    if(!isValidInt(input)){
        cout << "Invalid StudentID.\n";
        return;
    }

    int id = stoi(input);

    for(int i = 0; i < rowCount; i++){
        if(sheet[i].id == id){
            for(int j = i; j < rowCount - 1; j++)
                sheet[j] = sheet[j + 1];

            rowCount--;
            cout << "Student record deleted successfully.\n";
            return;
        }
    }

    cout << "StudentID not found.\n";
}

// ===== COUNT =====
void countRows(){
    cout << "Total number of student records: " << rowCount << endl;
}

// ===== SAVE =====
void saveFile(){
    if(!fileLoaded){
        cout << "Error: No file loaded to save.\n";
        return;
    }

    ofstream file(loadedFileName);
    if(!file){
        cout << "Error: Could not save file.\n";
        return;
    }

    for(int i = 0; i < rowCount; i++){
        file << sheet[i].id << ","
             << sheet[i].name << ","
             << sheet[i].status << "\n";
    }

    file.close();
    cout << "Attendance saved successfully.\n";
}

// ===== MENU =====
void menu(){
    cout << "\n========== MENU ==========\n";
    cout << "1. Create School Term\n";
    cout << "2. Load Attendance File\n";
    cout << "3. Display Attendance Sheet\n";
    cout << "4. Update Attendance\n";
    cout << "5. Delete Attendance\n";
    cout << "6. Count Records\n";
    cout << "7. Save Attendance to File\n";
    cout << "8. Exit\n";
    cout << "==========================\n";
    cout << "Enter choice: ";
}

// ===== MAIN =====
int main(){
    cout << "===========================================\n";
    cout << "   STUDENT ATTENDANCE TRACKER - MILESTONE 2\n";
    cout << "===========================================\n";

    string input;
    int choice = 0;

    do {
        menu();
        getline(cin, input);

        if(!isValidInt(input)){
            cout << "Invalid choice. Enter 1-8.\n";
            continue;
        }

        choice = stoi(input);

        switch(choice){
            case 1: createTerm(); break;
            case 2: readFile(); break;
            case 3: displaySheet(); break;
            case 4: updateRow(); break;
            case 5: deleteRow(); break;
            case 6: countRows(); break;
            case 7: saveFile(); break;
            case 8: cout << "Exiting program...\n"; break;
            default: cout << "Invalid choice. Enter 1-8.\n";
        }

    } while(choice != 8);

    return 0;
}
