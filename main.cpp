#include <iostream>
#include <string>
using namespace std;

int main() {
    string sheetName;

    cout << "Enter attendance sheet name: ";
    getline(cin, sheetName);

    cout << "Attendance sheet \"" << sheetName 
         << "\" created successfully." << endl;

    return 0;
}
