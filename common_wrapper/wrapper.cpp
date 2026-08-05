#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

using namespace std;

bool fileExists(const string& filename) {
    ifstream file(filename.c_str());
    return file.good();
}

void handleAssignment01() {
    int choice;
    do {
        cout << "\n-------------------------------------------------\n";
        cout << "              Assignment 01 Menu                 \n";
        cout << "-------------------------------------------------\n";
        cout << "1. Compile Assignment 01\n";
        cout << "2. Run BFS (Breadth-First Search)\n";
        cout << "3. Run DFS (Depth-First Search)\n";
        cout << "4. Run SSSP (Single-Source Shortest Path)\n";
        cout << "0. Back to Main Menu\n";
        cout << "Enter choice (0-4): ";
        cin >> choice;

        if (choice == 1) {
            cout << "\n[System] Compiling Assignment 01...\n";
            if (system("cd ../assignment_01 && mingw32-make") != 0) {
                cout << "[!] Error: Compilation failed. Please check your Makefile.\n";
            } else {
                cout << "[+] Compilation successful!\n";
            }
        } 
        else if (choice >= 2 && choice <= 4) {
            string exePath = "../assignment_01/driver_app.exe"; 
            if (!fileExists(exePath)) {
                cout << "[!] Error: Executable 'driver_app.exe' not found.\n";
                cout << "    Please compile the assignment (Option 1) before running.\n";
                continue;
            }

            int runMode;
            cout << "\n  1. Run one selected test file\n";
            cout << "  2. Run ALL test files\n";
            cout << "  Enter choice (1-2): ";
            cin >> runMode;
            string algoArg = to_string(choice - 1); 
            string command;
            if (runMode == 1) {
                string sizeStr;
                cout << "  Enter test case size (10, 100, 10000, 50000, 100000): ";
                cin >> sizeStr;
                string testFile = (choice == 4) ? "sssp" + sizeStr + ".txt" : "unweighted" + sizeStr + ".txt";
                if (!fileExists("../assignment_01/tests/" + testFile)) {
                    cout << "[!] Error: Test file 'tests/" << testFile << "' is missing or unavailable.\n";
                    continue;
                }
                command = "cd ../assignment_01 && driver_app.exe " + algoArg + " " + sizeStr;
            } 
            else if (runMode == 2) {
                command = "cd ../assignment_01 && driver_app.exe " + algoArg + " ALL";
            } 
            else {
                cout << "[!] Invalid run mode.\n";
                continue;
            }
            cout << "\n[System] Executing Driver...\n\n";
            system(command.c_str());
        }
    } while (choice != 0);
}

int main() {
    int choice;
    do {
        cout << "\n=================================================\n";
        cout << "           CS509 Common Wrapper Menu             \n";
        cout << "=================================================\n";
        cout << "1. Assignment 01 (Graph Algorithms: BFS, DFS, SSSP)\n";
        cout << "9. Compile All Submitted Assignments\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        switch(choice) {
            case 1:
                handleAssignment01();
                break;
            case 9:
                cout << "\n[System] Compiling All Assignments...\n";
                cout << "-> Compiling Assignment 01...\n";
                if (system("cd ../assignment_01 && mingw32-make") != 0) {
                    cout << "   [!] Assignment 01 Compilation failed.\n";
                } else {
                    cout << "   [+] Assignment 01 Compiled successfully.\n";
                }
                break;
            case 0:
                cout << "\nExiting wrapper. Goodbye!\n";
                break;
            default:
                cout << "\n[!] Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
    return 0;
}