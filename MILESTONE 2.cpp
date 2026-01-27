// *********************************************************
// Program: StudentAttendanceTracker.cpp
// Course: CCP6114 Programming Fundamentals
// Description: Tracks student attendance by loading,
// displaying, updating, deleting, and saving CSV files.
// *********************************************************

#include <iostream>
#include <fstream>
#include <cctype>   // for isdigit
using namespace std;

// ===== CONSTANTS =====
const int MAX_ROW = 100;   // maximum number of students

// ===== STRUCTS =====
struct Student {
    int id;        // student ID
    string name;   // student name
    int status;    // attendance status (0=absent, 1=present)
};

// ===== GLOBAL VARIABLES =====
Student sheet[MAX_ROW];  // array to store student records
int rowCount = 0;        // current number of rows
string termName;         // school term name

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
// Checks if a string contains only digits
bool isValidInt(string s){
    for(char c: s)
        if(!isdigit(c))
            return false;
    return !s.empty();
}

// ===== CREATE TERM =====
void createTerm(){
    cin.ignore();  // clear input buffer
    cout << "Enter term name: ";
    getline(cin, termName);
    cout << "Database \"" << termName << "\" created successfully.\n";
}

// ===== READ CSV FILE  =====
void readFile(){
    cin.ignore();  // clear input buffer
    string fileName;
    cout << "Enter CSV file name (e.g., Week1_Attendance.csv): ";
    getline(cin, fileName);

    ifstream file(fileName); // open file
    if(!file){
        cout << "Error: File \"" << fileName << "\" not found in current folder.\n";
        return;
    }

    rowCount = 0; // reset row count
    string line;

    while(getline(file, line)){
        if(line.empty()) continue; // skip empty lines

        // Find commas manually
        size_t pos1 = line.find(',');      // first comma
        if(pos1 == string::npos) continue; // invalid row

        size_t pos2 = line.find(',', pos1+1); // second comma
        if(pos2 == string::npos) continue;    // invalid row

        // Extract ID, Name, Status
        string idStr = line.substr(0, pos1);
        string nameStr = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string statusStr = line.substr(pos2 + 1);

        // Validate integers
        if(!isValidInt(idStr) || !isValidInt(statusStr)){
            cout << "Skipping invalid row: " << line << endl;
            continue;
        }

        // Store in sheet
        sheet[rowCount].id = stoi(idStr);
        sheet[rowCount].name = nameStr;
        sheet[rowCount].status = stoi(statusStr);
        rowCount++;

        if(rowCount >= MAX_ROW){
            cout << "Warning: Maximum row limit reached (" << MAX_ROW << ").\n";
            break;
        }
    }

    file.close();
    cout << "File \"" << fileName << "\" loaded successfully. Rows read: " << rowCount << endl;
}

// ===== DISPLAY ATTENDANCE SHEET =====
void displaySheet(){
    if(rowCount == 0){
        cout << "No records to display.\n";
        return;
    }

    cout << "\nStudentID, Name, Status\n";
    cout << "------------------------\n";
    for(int i=0; i<rowCount; i++){
        cout << sheet[i].id << ", "
             << sheet[i].name << ", "
             << sheet[i].status << endl;
    }
}

// ===== UPDATE ATTENDANCE =====
void updateRow(){
    string input;
    cout << "Enter StudentID to update: ";
    cin >> input;

    if(!isValidInt(input)){
        cout << "Error: Invalid StudentID. Must be an integer.\n";
        return;
    }

    int id = stoi(input);
    for(int i=0; i<rowCount; i++){
        if(sheet[i].id == id){
            int newStatus;
            cout << "Enter new status (0=Absent, 1=Present): ";
            cin >> newStatus;
            if(newStatus != 0 && newStatus != 1){
                cout << "Error: Status must be 0 or 1.\n";
                return;
            }
            sheet[i].status = newStatus;
            cout << "Attendance updated successfully.\n";
            return;
        }
    }
    cout << "Error: StudentID not found.\n";
}

// ===== DELETE ROW =====
void deleteRow(){
    int id;
    cout << "Enter StudentID to delete: ";
    cin >> id;

    for(int i=0; i<rowCount; i++){
        if(sheet[i].id == id){
            // Shift remaining rows up
            for(int j=i; j<rowCount-1; j++)
                sheet[j] = sheet[j+1];
            rowCount--;
            cout << "Student record deleted successfully.\n";
            return;
        }
    }
    cout << "Error: StudentID not found.\n";
}

// ===== COUNT ROWS =====
void countRows(){
    cout << "Total number of student records: " << rowCount << endl;
}

// ===== SAVE TO CSV =====
void saveFile(){
    ofstream file("Week1_Attendance_Updated.csv");
    if(!file){
        cout << "Error: Could not create output file.\n";
        return;
    }

    for(int i=0; i<rowCount; i++){
        file << sheet[i].id << ","
             << sheet[i].name << ","
             << sheet[i].status << "\n";
    }
    file.close();
    cout << "Attendance saved successfully as \"Week1_Attendance_Updated.csv\".\n";
}

// ===== MENU DISPLAY =====
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

// ===== MAIN FUNCTION =====
int main(){
    cout << "===========================================\n";
    cout << "   STUDENT ATTENDANCE TRACKER - MILESTONE 2\n";
    cout << "===========================================\n";

    int choice;
    do{
        menu();
        cin >> choice;

        switch(choice){
            case 1: createTerm(); break;
            case 2: readFile(); break;
            case 3: displaySheet(); break;
            case 4: updateRow(); break;
            case 5: deleteRow(); break;
            case 6: countRows(); break;
            case 7: saveFile(); break;
            case 8: cout << "Exiting program...\n"; break;
            default: cout << "Invalid choice. Please enter 1-8.\n";
        }

    } while(choice != 8);

    return 0;
}
