/*             
    Arjav Patel - USACO Humble Numbers
    June 30, 2019
    Task:
        - Given a set of prime numebrs and a number x
        - Caluclate the xth humble number that can be formed
        - A humble number is one where all of its prime factors are in the given list
        - The test cases for x can be huge (up to 100,000)
        - Dynamic programming is used to run under 1 second
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <unordered_map>
#include <set>

using namespace std;

long numPrimes;
long target;
long input;
set <long> ans;
vector <long> primes;
set <long>::iterator it;

int main () 
{
    //Input height and number of nodes
    ifstream fin ("humble.in");
    ofstream fout ("humble.out");
    fin >> numPrimes >> target;

    //Insert the prime numbers into a set and a vector
    for (int i = 0; i < numPrimes; ++i) 
    {
        fin >> input;
        ans.insert(input);
        primes.push_back(input);
    }

    //Go through each prime number
    for (int i = 0; i < primes.size(); ++i) 
    {

        //Reset iterator
        it = ans.begin();

        //Keep making new humble numbers
        while (true) 
        {
            //Create a new number from previous numbers
            long next = primes[i] * (*it);

            if (next < 0) 
            {
                break;
            }

            //If too many, delete
            if (ans.size() > target) 
            {
                ans.erase(*(--ans.end()));
                if (next > *(--ans.end())) 
                {
                    break;
                }
            }

            //Make new number
            ans.insert(next);
            ++it;
        }
    }

    //Output
    fout << *(--ans.end()) << endl;

    return 0;
}