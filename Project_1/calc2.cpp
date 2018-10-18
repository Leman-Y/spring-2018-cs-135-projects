/*
Author: Leman Yan
Course: CSCI-135
Instructor: Genady Maryash
Assignment: Project 1 Task C

the output should evaluate all of the expressions and print them each on its own line:

*/

#include <iostream>
#include <cmath>

using namespace std;

int main() {

	int sum=0;	//initial sum is 0

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
		
		if (math==';'){		//If math is a semicolon then show the sum of the expression, then evaluate the next expression
			cout<<sum<<endl;

			sum=number;	//Reset sum as the next number
					
		}

	}

	cout<<sum<<endl;   		//Since there is no number after the semicolon, the last line's result will not be shown, because the while loop wll be false. Thus, we need to cout the sum.

	return 0;
}
