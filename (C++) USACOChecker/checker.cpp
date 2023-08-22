/*             
    Arjav Patel - USACO Checker Challenge
    February 18, 2018
    Task:
        - Very similar to the N-queens problem
        - Given a a board size N
        - Find the number of unique queen placements so that the N-queens do not cross each other's paths (horizontally, vertically, and diagonally)
        - Also print the first three solutions found
*/

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

//Create global variables and arrays
int size = 0;
int solutions = 0;
string ans = "";
int col [14];
int column [14];
int rightDiag [27];
int leftDiag [27];

//Function to create a string that contains valid placements of a queen
void makeAns() {

    //Increment solution counter
    ++solutions;

    //Print out the first three solutions by turing into a string
    //And adding onto each other
    for (int i = 1; i <= size; ++i) {
        stringstream y;
        y << col[i];
        ans += y.str();
        if (i != size) {
            ans += " ";
        }
    }
    ans += "\n";
}

//Function to try all the possible placements of a queen
int place (int line) {
   
    //If past the last row, call the function to make an answer
    if (line == size+1 && solutions < 3) {
        makeAns();
    }

    //Else finish the placements
    else {

        //Go through wach position in the row
        for (int j = 1; j <= size; ++j) {

            //Place queen if the column, right diag and left diag allow you to place a queen
            //For right diags, the column + row is always the same
            //For left diags, the row - colum is always the same
            if (rightDiag[line+j] == 0 && column[j] == 0 && leftDiag[line-j+13] == 0) {

                //Set them equal to one so other queens can't be placed there
                column[j] = 1;
                rightDiag[line+j] = 1;
                leftDiag[line-j+13] = 1;

                //Set the row element to the column num
                col[line] = j;

                //Recurse to the next row
                place(line+1);

                //Set them back to 0 so it can test the other positions
                column[j] = 0;
                rightDiag[line+j] = 0;
                leftDiag[line-j+13] = 0;
            }
        }
    }

    //Exit function
    return 0;
}

int main () {
    //Create input and output files and input the size of array
    ifstream fin ("checker.in");
    fin >> size;

    //Go to the function, start at row one
    place (1);

    //Output answer and number of solutions
    cout << ans << solutions << endl;
 
    //Exit program
    return 0;
}
