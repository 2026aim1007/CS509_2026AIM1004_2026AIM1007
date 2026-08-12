#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

void handleAssignment(int assignmentNum, const string& folderName, const string& menuTitle, const string& options) {
    int algoChoice;
    do {
        clearScreen();
        cout << "-------------------------------------------------\n";
        cout << "              " << menuTitle << "                  \n";
        cout << "-------------------------------------------------\n";
        cout << options;
        cout << "0. Go Back\n";
        cout << "Enter choice: ";
        cin >> algoChoice;
        int maxChoice = (assignmentNum == 2) ? 4 : 3;
        if (algoChoice > 0 && algoChoice <= maxChoice) {
            int modeChoice;
            cout << "\nSelect Execution Mode:\n";
            cout << "0 - Run Once (Standard execution)\n";
            cout << "1 - Test Mode (Average of 5 runs)\n";
            cout << "Enter choice (0 or 1): ";
            cin >> modeChoice;

            string command = "cd ../" + folderName + " && .\\driver_app.exe " + to_string(algoChoice) + " ALL";
            if (modeChoice == 1) {
                command += " --test";
            }
            cout << "\n[System] Executing: " << command << "\n\n";
            system(command.c_str());
            pauseScreen();
        } else if (algoChoice != 0) {
            cout << "\n[!] Invalid choice.\n";
            pauseScreen();
        }
    } while (algoChoice != 0);
}

int main() {
    int mainChoice;
    do {
        clearScreen();
        cout << "=================================================\n";
        cout << "           CS509 Common Wrapper Menu             \n";
        cout << "=================================================\n";
        cout << "1. Assignment 01 (BFS, DFS, SSSP)\n";
        cout << "2. Assignment 02 (TC-Unopt, TC-Opt, BC, CC)\n";
        cout << "8. Compile Assignment 01 (Makefile)\n";
        cout << "9. Compile Assignment 02 (Makefile)\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> mainChoice;

        switch (mainChoice) {
            case 1:
                handleAssignment(1, "assignment_01", "Assignment 01 Menu", 
                                 "1. BFS\n2. DFS\n3. SSSP\n");
                break;
            case 2:
                handleAssignment(2, "assignment_02", "Assignment 02 Menu", 
                                 "1. Triangle Counting (Unoptimized)\n2. Triangle Counting (Optimized)\n3. Betweenness Centrality (BC)\n4. Connected Components (CC)\n");
                break;
            case 8:
                cout << "\n[System] Compiling Assignment 01...\n";
                system("cd ../assignment_01 && mingw32-make");
                pauseScreen();
                break;
            case 9:
                cout << "\n[System] Compiling Assignment 02...\n";
                system("cd ../assignment_02 && mingw32-make");
                pauseScreen();
                break;
            case 0:
                cout << "\nExiting wrapper. Goodbye!\n";
                break;
            default:
                cout << "\n[!] Invalid choice. Please try again.\n";
                pauseScreen();
                break;
        }
    } while (mainChoice != 0);
    return 0;
}