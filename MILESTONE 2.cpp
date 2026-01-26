// *********************************************************
// Program: StudentAttendanceTracker.cpp
// Course: CCP6114 Programming Fundamentals
// *********************************************************

#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
using namespace std;

const int MAX_ROW = 100;

struct Student {
    int id;
    string name;
    int status;
};

Student sheet[MAX_ROW];
int rowCount = 0;
string termName;

// ===== VALIDATION =====
bool isValidInt(string s){
    for(char c: s) if(!isdigit(c)) return false;
    return !s.empty();
}

// ===== DATABASE =====
void createTerm(){
    cin.ignore();
    cout << "Enter term name: ";
    getline(cin, termName);
    cout << "Database \"" << termName << "\" created.\n";
}

// ===== FILE READ =====
// ===== FILE READ =====
void readFile(){
    cin.ignore(); // clear input buffer
    string fileName;
    cout << "Enter CSV file name (e.g., Week1_Attendance.csv): ";
    getline(cin, fileName);

    ifstream file(fileName); // only filename, assumes file is in same folder as .exe
    if(!file){
        cout << "Error: File \"" << fileName << "\" not found in current folder.\n";
        return;
    }

    rowCount = 0;
    string line;
    while(getline(file,line)){
        if(line.empty()) continue; // skip empty lines
        stringstream ss(line);
        string id,name,status;

        getline(ss,id,',');
        getline(ss,name,',');
        getline(ss,status,',');

        if(!isValidInt(id) || !isValidInt(status)){
            cout << "Skipping invalid row: " << line << endl;
            continue;
        }

        sheet[rowCount].id = stoi(id);
        sheet[rowCount].name = name;
        sheet[rowCount].status = stoi(status);
        rowCount++;
    }
    file.close();
    cout << "File \"" << fileName << "\" loaded successfully. Rows read: " << rowCount << endl;
}

// ===== DISPLAY =====
void displaySheet(){
    if(rowCount==0){ cout<<"No records.\n"; return; }

    cout << "StudentID, Name, Status\n";
    for(int i=0;i<rowCount;i++)
        cout << sheet[i].id << ", "
             << sheet[i].name << ", "
             << sheet[i].status << endl;
}

// ===== UPDATE =====
void updateRow(){
    string input;
    cout << "Enter StudentID to update: ";
    cin >> input;

    if(!isValidInt(input)){
        cout<<"Error: Invalid integer. Try again.\n";
        return;
    }

    int id = stoi(input);
    for(int i=0;i<rowCount;i++){
        if(sheet[i].id==id){
            cout<<"Enter new status (0/1): ";
            cin>>sheet[i].status;
            cout<<"Row updated successfully.\n";
            return;
        }
    }
    cout<<"Error: StudentID does not exist.\n";
}

// ===== DELETE =====
void deleteRow(){
    int id;
    cout<<"Enter StudentID to delete: ";
    cin>>id;

    for(int i=0;i<rowCount;i++){
        if(sheet[i].id==id){
            for(int j=i;j<rowCount-1;j++)
                sheet[j]=sheet[j+1];
            rowCount--;
            cout<<"Row deleted successfully.\n";
            return;
        }
    }
    cout<<"StudentID not found.\n";
}

// ===== COUNT =====
void countRows(){ cout<<"Number of rows: "<<rowCount<<endl; }

// ===== SAVE =====
void saveFile(){
    ofstream file("Week1_Attendance_Updated.csv");
    for(int i=0;i<rowCount;i++)
        file<<sheet[i].id<<","<<sheet[i].name<<","<<sheet[i].status<<"\n";
    file.close();
    cout<<"Output saved as: Week1_Attendance_Updated.csv\n";
}

// ===== MENU =====
void menu(){
    cout << "\n========== MENU ==========\n";
    cout << "1. Create School Term\n";
    cout << "2. Load Attendance File\n";
    cout << "3. Display Sheet\n";
    cout << "4. Update Attendance\n";
    cout << "5. Delete Attendance\n";
    cout << "6. Count Rows\n";
    cout << "7. Save to File\n";
    cout << "8. Exit\n";
    cout << "==========================\n";
    cout << "Enter choice: ";
}

// ===== MAIN =====
int main(){
    cout << "===========================================\n";
    cout << "   STUDENT ATTENDANCE TRACKER - MILESTONE 2\n";
    cout << "===========================================\n";

    int choice;
    do{
        menu();
        cin>>choice;

        switch(choice){
            case 1: createTerm(); break;
            case 2: readFile(); break;
            case 3: displaySheet(); break;
            case 4: updateRow(); break;
            case 5: deleteRow(); break;
            case 6: countRows(); break;
            case 7: saveFile(); break;
            case 8: cout<<"Exiting program...\n"; break;
            default: cout<<"Invalid choice.\n";
        }

    }while(choice!=8);

    return 0;
}
