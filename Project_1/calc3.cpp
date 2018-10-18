/*
Author: Leman Yan
Course: CSCI-135
Instructor: Genady Maryash
Assignment: Project 1 Task D

Program: A calculator program that can understand squared numbers

*/

#include <iostream>
#include <cmath>

using namespace std;

int main(){

	int sum=0; //Initial sum
	char math='+'; //Set math expression to +. Assume the first integer is positive.
	char math1; //Another math expression
	int number=0; //The numbers being inputed
	int number1=0; //Another number

	cin>>number;			// We know the first thing in the expression is a number

	while(cin>>math1){		//We know after a number there is an operation after.

		if(math1=='^'){				//If the symbol is ^ then times the number by itself
			number=number*number;
			cin>>math1;				//Get the next operatorion because we know after number^ is another operation.
		}
		
		if(math=='+'){				//If there is math1 doesnt equal to ^ then just add the number.
			sum+=number;
		
		}

		if(math=='-'){
			sum-=number;
		}

		math=math1;					//Math is equal to math1. 
		cin>>number;				//We get the next number.
									//In the case of 10-10. Number=10. Default math is + so we add 10 to the sum. The next number is 10, but math is -, so 10-10=0. Then math gets changed to semi colon, so 											the sum is sent out.

		if(math==';'){				//If the the math symbol is a semicolon
			cout<<sum<<endl;		//Send out the sum
			sum=0;					//The sum is zero now
			math='+';				//Math is back to +
		}
		
	}		


return 0;	
}











