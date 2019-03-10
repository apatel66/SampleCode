/*             
    Arjav Patel - USACO Controlling Companies
    January 1, 2019
    Task:
        - Input is several lines of what percentage of one company does another comppany own
        - Company names are integers
        - If a company X owns >= 50% of company Y, X owns Y
        - If W owns X and Y, X owns 25% of Z, and Y owns 30% of Z, W owns company Z (25% + 30% >= 50%)
        - If X owns Y, X also owns all the companies and percentage of companies that Y owns
        - Output which companies own which other companies in a sorted list
        - A company cannot own itself
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

//Create global arrays, vectors, variables, and fuctions
int coms[101][101];
int checked[101];
int visited[101];
int num = 0;
int ownerInput = 0;
int ownedInput = 0;
int percentInput = 0;
vector <int> names;
vector < pair<int, int> > ans;
void control(int owner, int curr);

//See which companies own what other companies
void checkControl(int ownerCompany, int currCompany, int inc) {

    //If the a comapny owns >= 50% of a company, input it into answer vector
    //Check to see what other comanies it owns
    if (coms[currCompany][names[inc]] > 50 && checked[names[inc]] == 0) {
        checked[names[inc]] = 1;
        ans.push_back(make_pair(ownerCompany, names[inc]));
        control(ownerCompany, names[inc]);
    }

    //If the company owns < 50% of a company, add the amount that a company owns to the top owner company
    else if (coms[currCompany][names[inc]] <= 50 && currCompany != ownerCompany && visited[names[inc]] == 0) {
        visited[names[inc]] = 1;
        coms[ownerCompany][names[inc]] += coms[currCompany][names[inc]];
    }
}

//Goes through each company and calls functions to check ownership
void control(int owner, int curr) {

    //Reset array
    for (int j = 0; j < 101; ++j) {
        visited[j] = 0;
    }

    //Go through all the other comapnies
    for (int j = 0; j < names.size(); ++j) {
        checkControl(owner, curr, j);

        //Go back and repeat for the previous companies
        for (int k = 0; k < j; ++k) {
           checkControl(owner, curr, k);
        }
    }
}

int main () {
    //Create input/output files
	//Input the number of instances of controls
	ifstream fin ("concom.in");
    ofstream fout ("concom.out");
    fin >> num;

    //Input the owner company, owned company and percentage on control into vectors and arrays
    for (int i = 0; i < num; ++i) {
        fin >> ownerInput >> ownedInput >> percentInput;
        coms[ownerInput][ownedInput] = percentInput;
        names.push_back(ownerInput);
        names.push_back(ownedInput);
    }

    //Sort, then delete duplicate companies
    sort(names.begin(), names.end());
    names.erase( unique( names.begin(), names.end() ), names.end() );

    //Check what each company owns by calling function
    for (int i = 0; i < names.size(); ++i) {  

        //Reset array
        for (int j = 0; j < names.size(); ++j) {
            checked[names[j]] = 0;
        }
        control(names[i], names[i]);
    }


    //Sort answer and remove duplicates
    sort(ans.begin(), ans.end());
    ans.erase( unique( ans.begin(), ans.end() ), ans.end() );

    //Output the ownership only if the compny owns a company other than itself
    for (int i = 0; i < ans.size(); ++i) {
        if (ans[i].first != ans[i].second) {
            fout << ans[i].first << " " << ans[i].second << endl;
        }
    }
    
    return 0;
}
