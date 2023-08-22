/*             
    Arjav Patel - USACO Party Lamps
    November 5, 2018
    Task:
        - Given the number of lamps (N), number of button pushes as well as which lights are on and off
        - Lamps are numbers 1, 2, 3 ... N
        - Determine the combination of buttons that is equal to the number of buttons pushed and will produce a lamp configuration consistent with the given on and off lamps
        - On lamps have state 1 and off lamps have state 0
        - Print the possible configurations sorted in binary order

        - Buttons
            - Button 1: All lamps change to opposite state
            - Button 2: All odd numbered lamps change to opposite state
            - Button 3: All even numbered lamps change to opposite state
            - Button 4: All lamps in pattern (3X + 1) change to opposite state. Ex: 1, 4, 7, 10...
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

//Create global varibales, vectors, and input/output files
int numLamps = 0;
int numButtons = 0;
int input = 0;
int num = 0;
int check = 0;
int check2 = 0;
int start = 0;
int inc = 0;
vector <int> numMoves;
vector <int> compare;
vector <bool> curr;
vector <int> test;
vector <string> fin;
ifstream filestreamIn ("lamps.in");

//Add next lamp configuration to answer array
void addAns() {
    check2 = 1;
    fin.push_back("");
    for (int z = 0; z < curr.size(); ++z) {
        fin[fin.size() - 1] += (char) (curr[z] + 48);
    }
}

//Check to see if current combination causes the same lamps to be on and off
void checkCurr() {
        for (int z = 0; z < curr.size(); ++z) {
        if ((compare[z] == 1 && curr[z] == 0) || (compare[z] == 0 && curr[z] == 1)){
            check = 1;
            break;
        }
    }
}

//Go through test array and make necessary changes based on current button combo
void pushButton() {
    for (int m = 0; m < test.size(); ++m) {
        start = 0;
        inc = test[m];
        if (m == 3) {
            start = 1;
        }
        if(m >= 3) {
            --inc;
        }

        for (int z = start; z < curr.size(); z+=inc) {
            curr[z] = !curr[z];
        }
    }
}

//Reset the array and check for each combo
void reset() {
    check = 0;
    for (int m = 0; m < curr.size(); ++m) {
        curr[m] = 1;
    }
}

//Make every combination of buttons, given the size
int makeCombo (int lowest, int highest, int nums) {

  //Add the remaining feed types
  for (int k = lowest; k <= highest+1; ++k) {  

    //Check if combo size is required size   
    if (test.size() == nums) {

        //Call various functions to test if current button combo will result in correct answer
        reset();
        pushButton();
        checkCurr();
    
        //if correct, add to vector
        if (check == 0) {
            addAns();
        }
        return 1;
    }

    //Go to the next combination
    test.push_back(k);
    makeCombo(k + 1, highest, nums);

    //Remove last value
    test.pop_back();
  }
  return 0;
}

int main () {

  //Input the number of lamps the number of buttons pushed
  filestreamIn >> numLamps >> numButtons;

  //Create the compare and test vector by adding junk values
  for (int i = 0; i < numLamps; ++i) {
    compare.push_back(-99);
    curr.push_back(1);
  }

  //Input the lamps that must be on or off and change the value of compare accordingly
  filestreamIn >> input;
  while (input != -1) {
    compare[input - 1] = 1;
    filestreamIn >> input;
  }
  filestreamIn >> input;
  while (input != -1) {
    compare[input - 1] = 0;
    filestreamIn >> input;
  }

  //Figure out the minimum amount of buttons the given numButtons can simplify to and add to vector of potential values
  //O button pushes simplifies to 0, even button bushes can be 0, 2, 4 pushes, and odd button pushes can be 1 or 3 pushes
  if (numButtons == 0) {
      numMoves.push_back(0);
  }
  else if (numButtons % 2 == 0) {
      numMoves.push_back(0);
      numMoves.push_back(2);
      numMoves.push_back(4);
  }
  else {
      numMoves.push_back(1);
      if (numButtons > 1) {
          numMoves.push_back(3);
      }
  }

  //Traverse vector and create button combinations of sizes based on the current vector element
  for (int i = 0; i < numMoves.size(); ++i) {
      test.clear();
      makeCombo(1, 4, numMoves[i]);
  }

  //Sort answer vector and print
  sort(fin.begin(), fin.end());
  for (int i = 0; i < fin.size(); ++i) {
      cout << fin[i] << endl;
  }

  //If no solution, print "IMPOSSIBLE"
  if(check2 == 0) {
      cout << "IMPOSSIBLE" << endl;
  }

  //End program
  return 0;
}
