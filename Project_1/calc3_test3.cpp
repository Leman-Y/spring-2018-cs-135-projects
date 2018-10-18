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

	char math; //The math expression

	char math1; //Another math expression. Set math1 to +, because if the first line is 10; then you will get 10.

	char math2;

	int number=0; //The numbers being inputed

	int number1=0; //Another number

	cin>>number;  //Get the first number

	while(cin >> math){
	
		if(math=='^'){
			number=number*number;
			sum+=number;
			cin>>math1;
			//cin>>number1;

			if(math1=='+'){
				cin>>number1;
				sum+=number1;
			}

			if(math1=='-'){
				cin>>number1;
				sum=sum-number1;
			}
			
			if(math1==';'){
				cout<<sum<<endl;

				
				cin>>number;

				cout<<"number "<<number<<endl;

				cin>>math;
				cout<<"math "<<math<<endl;
			}
		}

		if(math=='+'){

			
			cin>>number1;
			sum=sum+number;
			sum=sum+number1;

		

		//cout<<"number1 "<<number1<<endl;		
		}

		if(math=='-'){
			cin>>number1;
			sum=sum+number;
			sum=sum-number1;

			cin>>math;
			cout<<"math "<<math<<endl;

		}
			
		if(math==';'){
			cout<<sum<<endl;
			cin>>number;
			cin>>math;
			cout<<"number "<<number<<endl;
			cout<<"math "<<math<<endl;
		}
		
		//cin>>number;
	}


	return 0;
}

