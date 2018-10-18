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
	
	char math1;  //Another math expression

	int number; //The numbers being inputed

//	cin>>number;
	
//	sum=number;  //First number gets added to the sum

	while(cin>>number){
		//cout<<number<<endl;
		
		sum+=number;

		if (cin>>math>>number){

			if (math=='+'){         //If the operator is add then add the number to the sum
				sum+=number;
			}

			if (math=='-'){		//If the operator is subtract then subtract the number from the sum 
				sum-=number;
			}
		
			if (math==';'){		//If math is a semicolon then show the sum of the expression, then evaluate the next expression
				//cout<<sum<<endl;

				sum=number;	//Reset sum as the next number

				cout<<sum<<endl;
			}


		}

		if (cin>>math){
			
			//cout<<math<<endl;

			if(math==';'){
				cout<<sum<<endl;
				
				cin>>number;

				sum=number;
			}

			else if(math=='^'){
				
				sum=sum*sum;
			}

			else if(math=='+'){
				
				sum+=number;
			}

			else if(math=='-'){
				sum-=number;
			}
			
			if (cin>>math1){

				//cout<<math<<endl;

				if(math=='+'){
					
					sum+=number;
				}

				if(math=='-'){
					sum-=number;
				}

			}
		}
			//cout<<sum<<endl;


		if (cin>>number){
			
			//cout<<math<<endl;

			if(math==';'){
				cout<<sum<<endl;
				
				cin>>number;

				sum=number;
			}

			else if(math=='^'){
				
				sum=sum*sum;
			}

			else if(math=='+'){
				
				sum+=number;
			}

			else if(math=='-'){
				sum-=number;
			}
			
			if (cin>>math1){

				//cout<<math<<endl;

				if(math=='+'){
					
					sum+=number;
				}

				if(math=='-'){
					sum-=number;
				}

			}
		}


			
	}	

	//cout<<sum<<endl;

	cout<<sum<<endl;


}



/*

5^;
10 ;
1000 + 6^ - 5^ + 1;

*/









