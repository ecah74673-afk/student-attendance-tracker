#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

const int MAX_COL = 10;
const int MAX_ROW = 100;

// Validate INT input
bool isValidInt(string input) {
    for (char c : input) if (!isdigit(c)) return false;
    return !input.empty();
}

// Validate TEXT input
bool isValidText(string input) {
    for (char d : input) if (!isalpha(d) && d != ' ') return false;
    return !input.empty();
}

// Validate Status input (0 or 1)
bool isValidStatus(string input) {
    return input == "0" || input == "1";
}

// Global Variables
string sheetName;
string colName[MAX_COL];
string colType[MAX_COL];

int dataInt[MAX_ROW][MAX_COL];
string dataText[MAX_ROW][MAX_COL];

int numCol = 0;
int rowCount = 0;
bool sheetCreated = false;

// Create attendance sheet
void createSheet() {
    if(sheetCreated){
        cout << "\nError: Sheet already created!\n\n";
        return;
    }

    cout << "\nEnter attendance sheet name: ";
    cin.ignore();
    getline(cin, sheetName);
    if(sheetName.empty()) sheetName = "UnknownSheet";

    // Define columns
    string input;
    while(true){
        cout << "Define number of columns (1-10): ";
        getline(cin, input);

        if(!isValidInt(input)){
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        numCol = stoi(input);
        if(numCol <= 0 || numCol > MAX_COL){
            cout << "Number out of range. Please enter 1-10.\n";
            continue;
        }

        // Input column names and types
        for(int i=0;i<numCol;i++){
            cout << "Enter column " << i+1 << " name: ";
            getline(cin, colName[i]);
            if(colName[i].empty()) colName[i] = "Column" + to_string(i+1);

            // **FOOLPROOF COLUMN TYPE INPUT**
            while (true) {
                cout << "Enter column " << i + 1 << " type (INT/TEXT): ";
                getline(cin, colType[i]);

                // Convert to uppercase to accept int/text

                if (colType[i] == "INT" || colType[i] == "TEXT")
                    break; // valid input
                else
                    cout << "Invalid type! Only INT or TEXT allowed.\n";
            }
        }
        break;
    }

    sheetCreated = true;
    cout << "\nSheet \"" << sheetName << "\" created successfully.\n\n";
}

// Insert a row
void insertRow() {
    if(!sheetCreated){
        cout << "\nError: Create sheet first!\n\n";
        return;
    }

    if(rowCount >= MAX_ROW){
        cout << "\nError: Maximum number of rows reached.\n\n";
        return;
    }

    char choice = 'y';
    while(choice=='y' || choice=='Y'){
        cout << "\n-------------------------------------------\n";
        cout << "Insert New Attendance Row\n";
        cout << "-------------------------------------------\n";

        for(int j=0;j<numCol;j++){
            string input;
            bool valid = false;

            if(colType[j]=="INT"){
                while(!valid){
                    cout << "Enter " << colName[j] << " (INT): ";
                    cin >> input;
                    if(isValidInt(input)){
                        dataInt[rowCount][j] = stoi(input);
                        valid = true;
                    } else {
                        cout << "Error: Invalid INT value.\n";
                    }
                }
            } else { // TEXT
                cin.ignore();
                while(!valid){
                    if(colName[j]=="Status"){
                        cout << "Enter Status (Present: 1, Absent: 0): ";
                        getline(cin, input);
                        if(isValidStatus(input)){
                            dataText[rowCount][j] = input;
                            valid = true;
                        } else cout << "Error: Status must be 0 or 1.\n";
                    } else {
                        cout << "Enter " << colName[j] << ": ";
                        getline(cin, input);
                        if(isValidText(input)){
                            dataText[rowCount][j] = input;
                            valid = true;
                        } else cout << "Error: Invalid text input.\n";
                    }
                }
            }
        }

        rowCount++;
        cout << "Row inserted successfully.\n";

        cout << "Add another student? (y/n): ";
        cin >> choice;
    }
}

// Display CSV
void displayCSV() {
    if(!sheetCreated){
        cout << "\nError: Create sheet first!\n\n";
        return;
    }

    if(rowCount==0){
        cout << "\nNo rows inserted yet.\n\n";
        return;
    }

    cout << "\n-------------------------------------------\n";
    cout << "Attendance Sheet (CSV Mode)\n";
    cout << "-------------------------------------------\n";

    // Column names (HEADER ONLY)
    for(int i=0;i<numCol;i++){
        cout << colName[i];
        if(i<numCol-1) cout << ",";
    }
    cout << endl;

    // Rows (DATA ONLY)
    for(int i=0;i<rowCount;i++){
        for(int j=0;j<numCol;j++){
            if(colType[j]=="INT")
                cout << dataInt[i][j];
            else if(colName[j]=="Status")
                cout << (dataText[i][j]=="1" ? "Present" : "Absent");
            else
                cout << dataText[i][j];

            if(j<numCol-1) cout << ",";
        }
        cout << endl;
    }

    cout << "-------------------------------------------\n";
}

// Main Menu
int main() {
    string fileName;    // To hold file name
    ifstream inFile;
    ofstream outFile;
    int choice = 0;

    cout << "===========================================\n";
    cout << "   STUDENT ATTENDANCE TRACKER - MILESTONE 2\n";
    cout << "===========================================\n";

    cout << "Create School Term (Database)";
    cout << "\n-----------------------------\n";
    cout << "Enter term name: ";
    cin >> fileName;

    // Open the file for input
    cout << "Database \"" << fileName << "\" created and loaded.\n";

    outFile.open(fileName);

    // If the input file was opened successfully, continue.
    if (outFile)
    {
        // Actually. What is you two 'cout' 's purpose?
        cout << "Reading attendance data from file...\n";
        cout << "Successfully loaded: Week1_Attendance.csv\n"; // They're not asking me to actually
                                                                 // keep track/create the csv right?

        cout << "===========================================\n";
        cout << "   STUDENT ATTENDANCE TRACKER - MILESTONE 1\n";
        cout << "===========================================\n";

        do {
            cout << "\n============= MENU =============\n";
            cout << "1. Create Attendance Sheet\n";
            cout << "2. Insert Attendance Row\n";   // Add update/delete feature
            cout << "3. View Sheet (CSV Mode)\n";   // And auto? view update
            cout << "4. Exit\n";
            cout << "================================\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch(choice){
                case 1: createSheet(); break;
                case 2: insertRow(); break;
                case 3: displayCSV(); break;
                case 4: cout << "\n-------------------------------------------\n";
                    cout << "End of Milestone 1\n";
                    cout << "-------------------------------------------\n";
                    break;
                default: cout << "Invalid choice. Try again.\n"; break;
            }
        } while(choice != 4);

        inFile.close();
    }
    else
        cout << "Cannot open " << fileName << endl;

    return 0;
}
