/*
Author: Leman Yan
Course: CSCI-135
Instructor: Genady Maryash
Assignment: Project 1 Task A

Adds the integers from a text file and then returns the sum.
*/

#include <iostream>
#include <string> 

using namespace std;

int main() {

    string s;
    int number=0;
    int sum=0; //Add the numbers to the sum


    while(cin >> number) { // While the reading operation is a success

//        cout << number << endl;  // print the read word
	
		sum+=number;  	   //Add the number to the sum
    }

   cout<< sum <<endl; 	//Show the sum of the numbers

	return 0;
}
