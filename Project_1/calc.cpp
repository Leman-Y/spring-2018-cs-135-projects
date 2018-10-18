/*
Author: Leman Yan
Course: CSCI-135
Instructor: Genady Maryash
Assignment: Project 1 Task B

Finishes the equation from the formula.txt file

*/

#include <iostream>
#include <cmath>

using namespace std;

int main() {

	int sum=0;	//initial sum is 0
	char add='+';    //operators
	char subtract='-';

	char math;       //We are going to get the operators from the txt file

	int number;      //Number in the file

	cin >> sum;    //Get the first number

	while(cin >> math>> number ) { // While the reading operation is a success

		if (math=='+'){         //If the operator is add then add the number to the sum
			sum+=number;
		}

		if (math=='-'){		//If the operator is subtract then subtract the number from the sum 
			sum-=number;
		}

	}

	cout<<sum<<endl;      		//Show the result of the equation

	return 0;
}





