/*************************************************************
 * 1. Name:
 *      Mark Van Horn & Taden Marston
 * 2. Assignment Name:
 *      W05 Problem Set: C++ Files
 * 3. Assignment Description:
 *      A simple program to read/write to a file
 * 4. What was the hardest part? Be as specific as possible.
 *      -a paragraph or two about how the assignment went for you-
 * 5. How long did it take for you to complete the assignment?
 *      -total time in hours: reading the assignment, submitting, and writing code-
 *****************************************************************/

#include <iostream>
#include <fstream>

using namespace std;

/*******************************************
 * READ BALANCE
 * Reads the balance out of a data.txt file
 *******************************************/
double readBalance() {
   ifstream fin("./data.txt");  // Open the file for reading
   double balance = 0.00;       // Default balance if file read fails

   // Attempt to read balance; print error if unsuccessful
   if (!(fin >> balance))
      cerr << "Unable to open data.txt" << endl;

   fin.close(); // Close the file
   return balance; // Return the balance read from the file
}

/***************************************
 * DISPLAY BALANCE
 * Displays the current account balance
 ***************************************/
void displayBalance(double balance) {
   cout << "Account balance: $" << balance << endl;
}

/*******************************************
 * UPDATE BALANCE
 * Updates the balance based on user input
 *******************************************/
void updateBalance(double &balance) {
   double change;
   cout << "Change: $";
   cin >> change;
   balance += change; // Update balance with the entered change
}

/***********************************************
 * WRITE BALANCE
 * Writes the updated balance back to "data.txt"
 ***********************************************/
void writeBalance(double balance) {
    ofstream fout("./data.txt");  // Open file for writing
    if (!fout) {  // Check if file opened successfully
        cerr << "Unable to write balance to data.txt" << endl;
        return;
    }

    fout << balance; // Write the balance to the file
    cout << "Balance successfully written to data.txt" << endl;
}

/**********************************************
 * MAIN
 * Runs the functions to read/write from a file
 **********************************************/
int main() {
   double balance = readBalance(); // Read the initial balance from file
   displayBalance(balance); // Display the balance

   updateBalance(balance); // Modify the balance based on user input
   displayBalance(balance); // Display updated balance

   writeBalance(balance); // Save the updated balance to file

   return 0;
}
