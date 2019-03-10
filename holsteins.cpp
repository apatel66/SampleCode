// NAME             :   Arjav Patel
// GROUP            :   Hex
// LAST MODIFIED    :   June 30, 2018
// PROBLEM ID       :   USACO Healthy Holsteins
// DESCRIPTION      :   Find out the minimum number of scoops needed to feed the cows
// SOURCES/HELP     :  

/*
 ID: arjav.p1
 TASK: holstein
 LANG: C++
*/

/*             
    Arjav Patel - USACO Healthy Hosteins
    June 30, 2018
    Task:
        - Given vitamin requirements, number of feeds and the vitamin content of one scoop of each type of feed
        - Figure out minimum number of scoops required to fulfill vitamin requiremnets
        - Can only use one scoop from each feed
        - If a tie, use the combination with the smallest sum
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

//Create global variables, arrays, and vectors
int numVitamins = 0;
int numFeeds = 0;
int numScoops = 9999;
int origSum = 0;
int check = 0;
int input = 0;
int dailyValue[30][30];
vector <int> feedsUsed;
vector <int> test;
vector <int> needed;
vector <int> req;

//Test new feed combination
void testCombo() {
    for (int m = 0; m < test.size(); ++m) {
      for (int n = 0; n < numVitamins; ++n) {
        needed[n] -= dailyValue[test[m] - 1][n];
      }
    }
}

//If new answer is smaller or wins tiebreaker, put the values into an array
void makeAns(int feed, int total) {
    if (check == 0 && (feed < numScoops || (feed == numScoops && total < origSum))) {
      feedsUsed.clear();
      for (int l = 0; l < test.size(); ++l) {
        feedsUsed.push_back(test[l]);
      }
      numScoops = feed;
      origSum = total;
    } 
    check = 100;
}

//Check to see if all vitamin requirements were fulfilled
void checkCombo() {
    for (int g = 0; g < numVitamins; ++g) {
      if(needed[g] > 0) {
        check = 1;
      }
    }
}

//Copy the vitamin requirements into new array for testing
void reset() {
    for (int f = 0; f < req.size(); ++f) {
      needed[f] = req[f];
    }
}

//Given the maximum number of feeds, geenerate every combination of them
int makeCombo (int lowest, int highest, int nums, int sum) {
  //Add the remaining feed types
  for (int k = lowest; k <= highest; ++k) {
    test.push_back(k);
    ++nums;
    sum += k;
    check = 0;

    //Call various functions to test and check current feed combination
    reset();
    testCombo();
    checkCombo();
    makeAns(nums, sum);

    //Go to the next combination
    makeCombo(k + 1, highest, nums, sum);

    //Remove last feed type 
    sum -= test[test.size() - 1];
    test.pop_back();
    --nums;
  }
  return 0;
}

int main () {
  //Opens the input file and makes the output file 
  ifstream fin ("holstein.in");
  ofstream fout ("holstein.out");

  //Input the number of vitamins and feeds and the type of vitamins
  fin >> numVitamins;
  for (int i = 0; i < numVitamins; ++i) {
    fin >> input;
    req.push_back(input);
    needed.push_back(input);
  }
  fin >> numFeeds;

  //Input the cow's requirements
  for (int i = 0; i < numFeeds; ++i) {
    for (int j = 0; j < numVitamins; ++j) {
      fin >> dailyValue[i][j];
    }
  }

  //Make every possible combination of feeds
  makeCombo(1,numFeeds,0,0);

  //Sort the list and output number of feed and the type of feeds in order
  sort (feedsUsed.begin(), feedsUsed.end());
  fout << feedsUsed.size();
  for (int i = 0; i < feedsUsed.size(); ++i) {
    fout << " " << feedsUsed[i];
  }
  fout << endl;

  //Exit program
  return 0;
} 