#include <iostream>
#include <string>
#include <cctype>
using namespace std;

const int MAX_COL = 10;
const int MAX_ROW = 100;

// Validate INT input
bool isValidInt(string input) {
    for (char c : input) {
        if (!isdigit(c))
            return false;
    }
    return true;
}

//Validate TEXT input
bool isValidText (string input)
{
    for (char d : input)
    {
        if (!isalpha(d) && d != ' ')
            return false;
    }
    return true;
}

// Validate Status column input
bool isValidStatus (string input)
{
    for (char e : input)
    {
        if (!isalnum(e) && e != ' ')
            return false;
    }
    return true;
}

int main() {
    string sheetName;
    string colName[MAX_COL];
    string colType[MAX_COL];

    int dataInt[MAX_ROW][MAX_COL];
    string dataText[MAX_ROW][MAX_COL];

    int numCol = 0;
    int addCol = 0;
    int rowCount = 0;
    char choice = 'y';

    cout << "===========================================\n";
    cout << "   STUDENT ATTENDANCE TRACKER - MILESTONE 1\n";
    cout << "===========================================\n\n";

    // STEP 1: Create attendance sheet
    cout << "Enter attendance sheet name: ";
    getline(cin, sheetName);
    cout << "Attendance sheet \"" << sheetName << "\" created successfully.\n\n" << endl;;

    // STEP 2: Define columns
    string input;

    while (true)
    {
        cout << "Define number of columns (max 10): ";
        getline(cin, input);

        //Check if input is integer
        if (!isValidInt(input))
        {
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        numCol = stoi(input);

        //Check range
        if (numCol <= 0 || numCol > 10)
        {
            cout << "You have entered a number outside of our limit. Please enter another number." << endl;
            continue;
        }

        if (numCol > 0 && numCol <= 10)
        {
            for (int i = 0; i < numCol; i++)
                {
                    //Name the created column/s
                    cout << "Enter column " << i + 1 << " name: ";
                    getline(cin, colName[i]);

                    //Check if colType is INT or TEXT only
                    while (true)
                        {
                            cout << "Enter column " << i + 1 << " type (INT/TEXT): ";
                            getline(cin, colType[i]);

                            if (colType[i] == "INT" || colType[i] == "TEXT")
                                    break;
                            else
                            {
                                cout << "Invalid type. Please enter INT or TEXT only.\n";
                            }
                        }
                }
        }
        break;
    }
    cout << "\nSheet structure created successfully.\n\n";

    // STEP 3 + 5: Insert multiple students
    while (choice == 'y' || choice == 'Y') {

        cout << "-------------------------------------------\n";
        cout << "Insert New Attendance Row\n";
        cout << "-------------------------------------------\n";

        for (int j = 0; j < numCol; j++) {

            // INT columns
            if (colType[j] == "INT") {
                string input;
                cout << "Enter " << colName[j] << ": ";
                cin >> input;

                // Error handling for INT columns
                if (!isValidInt(input)) {
                    cout << "Error: Invalid INT value. Please enter a number.\n";
                    j--;
                } else {
                    dataInt[rowCount][j] = stoi(input);
                }
            }

            // TEXT columns
            else if (colType[j] == "TEXT")
            {
                string input;
                bool valid;

                //Check if column is called Status and implement specialty
                if (colName[j] == "Status")
                {
                    cout << "Enter Status (Present: 1, Absent: 0): ";
                    cin >> ws;  // FIX
                    getline(cin, input);

                    valid = (input == "0" || input == "1");
                }
                //For all other TEXT type columns
                else
                {
                    cout << "Enter " << colName[j] <<": ";
                    cin >> ws;  //FIX
                    getline(cin, input);

                    valid = isValidText(input);
                }

                //Error handling for TEXT columns
                if(!valid){
                        cout << "Error: Invalid input for " << colName[j] << ".\n";
                        j--;
                }
                else {
                        dataText[rowCount][j] = input;
                }
            }
        }

        rowCount++;
        cout << "Row inserted successfully.\n\n";

        cout << "Add another student? (y/n): ";
        cin >> choice;
        cin.ignore();
    }

    // STEP 4: Display CSV
    cout << "-------------------------------------------\n";
    cout << "View Attendance Sheet (CSV Mode)\n";
    cout << "-------------------------------------------\n";

    // Print headers
    for (int i = 0; i < numCol; i++) {
        cout << colName[i];
        if (i < numCol - 1) cout << ", ";
    }
    cout << endl;

    // Print rows
    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < numCol; j++) {
            if (colType[j] == "INT")
                cout << dataInt[i][j];
            else
                cout << dataText[i][j];

            if (j < numCol - 1) cout << ", ";
        }
        cout << endl;
    }

    cout << "-------------------------------------------\n";
    cout << "End of Milestone 1 Output\n";
    cout << "-------------------------------------------\n";

    return 0;
}
