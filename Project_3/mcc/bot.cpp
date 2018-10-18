/*
Author: Leman Yan
Course: CSCI-135
Instructor: Gennady Maryash
Assignment: Project 3

Program the robots logic so they do their work more efficiently in collecting debris from a predetermined area with a predetermined amount of debris
*/

#include <cstdlib>
#include <iostream>
#include "bot.h"
#include <cmath>

using namespace std;

//Intialize Global Variables right here

const int MAX_ROBOT_NUM = 50;

int NUM;          // to remember number or robots
int ROWS, COLS;   // map dimensions

//This is for robotRepair
int robotStates[50];		//Array with state of robots. Full of 1's because in the beginning all the robots are healthy.1 == Healthy 0 == Broken robot

//This is for finding Debris
int debrisGrid[40][40];		//2D Array thats maps the Grid with 1's and 0's indicating if that spot has a Debris or not. Make everything 0's initially
		
double distances[40][40];		//2D Array that when you look through the debrisGrid and there is a 1. You calculate the distance from that debris to the robot

double distancesOther[40][40]; 		//2D Array used to compare the current robot's distances to all the other Debris with the other robots

double brDistances[40][40];

double brOtherDistances[40][40];


/* Initialization procedure, called when the game starts: */
void onStart(int num, int rows, int cols, double mpr,
             Area &area, ostream &log)
{
	NUM = num;   // save the number of robots and the map dimensions
	ROWS = rows;
	COLS = cols;

	log << "Start!" << endl;

	//Make array size as big as the amount of the robots. It doesnt matter if the amount of robots is 10, because all the numbers after the 10 index are 1's so the purpose of finding a 			0 is not affected.
	for( int i=0 ; i<50 ; i++){		//Puts 1's in all of the indexes of the array for robotStates
		robotStates[i]=1;

	}	

	//Fill up the debrisGrid with all 0's
	for( int r=0 ; r<40 ; r++){
		for( int c=0; c<40 ; c++){
			debrisGrid[r][c]=0;

		}
	}

	//Fill up the distances with 100s just in case we find the minimum and if it went out of bounds it would count the out of bounds row as a viable target
	for( int r=0 ; r<40 ; r++){
		for( int c=0; c<40 ; c++){
			distances[r][c]=100;
		}
	}

	//Fill up the distances with 100s in case we find a minimum and if it went out of bounds
	for( int r=0; r<40 ; r++){
		for( int c=0; c<40 ; c++){
			distancesOther[r][c]=100;
		}		
	}

}

/* Deciding robot's next move */
/*
	-So we know the area of the grid is already predefined and onRobotAction can access that information
	-That means we can avoid wasting a turn going off the map

*/


Action onRobotAction(int id, Loc loc, Area &area, ostream &log) {
	int row = loc.r; // current row and column
	int col = loc.c;

	log << "Bot " << id << "'s turn" << endl;

	//THIS STATEMENT IS IFFY IDK IF THIS WILL WORK
	for(int i=0; i<NUM ; i++){
		if(  (robotStates[i]==0) && (i==id)  ){			//If the robot is a broken robot itself just collect and dont move
			return COLLECT;  
		}
	
	}

	//Implement Robot Repair VER 2.0 aka better. Only send 1 robot to repair 1 broken robot not all of them.

	// robotStates[] 
	// brDistances [] [] 	fill this up with 99. Save distances of the broken robots to this. find the min coordinates
	// brOtherDistances [] [] fill this up with 99. Save distances of the broken robots to this. find the min coordinates
	//brRow
	//brCol
	//brMin				
	//brOtherMin
	//brOtherRow
	//brOtherCol
	// Loop thru again and save the brRow and brCol and if the brMin is 99 then that means all the nearest robots are taken and so do your normal collecting
	//area.locate(id).r  / .c	


	for(int r=0; r<40 ; r++){				//Set everything in brDistances to 99
		for(int c=0 ; c<40 ; c++){
			brDistances[r][c]=99;
		}
	}	

	for	(int i=0 ; i<NUM ; i++ ){
		if( robotStates[i] == 0){	//This means there is one robot that is broken. The index corresponds to the broken robot because we update it in robotMalfunction.
				//Now you must send the robots to this coordinate
			int rowCoord= ( (area.locate(id).r) - (area.locate(i).r ) ) * ( (area.locate(id).r) - (area.locate(i).r ) );
			int colCoord= ( (area.locate(id).c) - (area.locate(i).c ) ) * ( (area.locate(id).c) - (area.locate(i).c ) );
			double sqrtBrDistances= sqrt( rowCoord  + colCoord);			
			
			brDistances[area.locate(i).r][area.locate(i).c]= sqrtBrDistances;			

		}
	}

	//Find the minimum of the distances now
	int brRow=0;		//Coordinates of the closest broken robot
	int brCol=0;	
	int brMin=brDistances[0][0];

	for (int r=0; r < ROWS ; r++){
		for( int c=0 ; c <COLS ; c++){
			if(brMin > brDistances[r][c]){
				brMin=brDistances[r][c];
				brRow=r;
				brCol=c;
			}	
		}
	}

/*
	int numBr;  //Num of broken robots
	
	for( int z=0; z<NUM ; z++){		//Count the number of broken robots
		if( robotStates[z]==0){
			numBr+=1;
		}
	}
*/

//	if( numBr > NUM){

		for( int number=0; number < NUM; number++){		//Calculate the distances and the find the minimum. Save the coordinates of the nearest robot and then compare that to the this 														robot

			if( ( number != id )  && (robotStates[number] == 1) ){							// Just do other robots that are healthy

				for(int r=0; r<40 ; r++){				//Reset the brOtherDistances to 99 after you compare this robot to the original robot
					for( int c=0; c<40 ; c++){
						brOtherDistances[r][c]=99;
					}
				}

				for(int i=0; i<NUM ; i++){				//Loop thru every broken robot and calculate the distance from this other robot to the BR
					if( robotStates[i] == 0 ){			//I was taking into other broken robot's coordinates to other BRs, so I must take that out


				
						int rowOtherCoord= ( (area.locate(number).r) - (area.locate(i).r ) ) * ( (area.locate(number).r) - (area.locate(i).r ) );
						int colOtherCoord= ( (area.locate(number).c) - (area.locate(i).c ) ) * ( (area.locate(number).c) - (area.locate(i).c ) );
				
						double sqrtOtherBrDistances= sqrt( rowOtherCoord + colOtherCoord);    	//Other robot's distances to the other broken robot's				
	
						brOtherDistances[area.locate(i).r][area.locate(i).c]=sqrtOtherBrDistances;
					}
				}
			
				int brOtherMin=brOtherDistances[0][0];
				int brOtherRow=0;
				int brOtherCol=0;
			
				for( int r=0; r < ROWS ; r++){
					for( int c=0 ; c < COLS ; c++){
						if(brOtherMin > brOtherDistances[r][c] ){
							brOtherMin=brOtherDistances[r][c];
							brOtherRow=r;
							brOtherCol=c;
					
						}							
					}	
				}

				//Now we have found the nearest Broken Robot for the other robot's. Now we compare the nearest coordinates for other robot's to this robot's 
			
				if( (brRow == brOtherRow) && (brCol == brOtherCol ) ){		//If the coordinates are the same
					
					if( brMin > brOtherMin){	//If the robot is farther away from that broken robot then ignore it
						brDistances[brRow][brCol]=99;		//Change the distance to the br to 99 aka ignore this broken robot and find another near broken robot
					}		

					brRow=0;
					brCol=0;
					brMin=brDistances[0][0];

					for (int r=0; r < ROWS ; r++){
						for( int c=0 ; c <COLS ; c++){
							if(brMin > brDistances[r][c]){
								brMin=brDistances[r][c];
								brRow=r;
								brCol=c;
							}	
						}
					}				
		
				}

			}
		}

		//Reinitialize these values to find the min aka nearest broken robot
			brRow=0;
			brCol=0;
			brMin=brDistances[0][0];

			//Recalculate the min after you compared with all the other robot's to what the nearest broken robot is
			for (int r=0; r < ROWS ; r++){
				for( int c=0 ; c <COLS ; c++){
					if(brMin > brDistances[r][c]){
						brMin=brDistances[r][c];
						brRow=r;
						brCol=c;
					}	
				}
			}		

			int i; 	//The id of the broken robot you are fixing

			for( int x=0; x < NUM ; x++){
				if( (area.locate(x).r == brRow) && (area.locate(x).c == brCol) ){		//If they have the same coordinates as the broken robot then that must be the id of the broken 																								robot
					i=x;
				}
			}

			//log<<"brMin "<<brMin<<endl;

			if( brMin != 99){				//Execute save robot. Because if all the other robot's are assigned a broken robot, then this robot will not repair and instead will just 													collect
				if( (brCol== col) && (brRow==row+1)  ){

						robotStates[i]=1;						//Remember to update the robotStates broken id back into a 1 if its repaired now
						return REPAIR_DOWN;
					}

					if( (brRow == row) && (brCol==col-1) ){

						robotStates[i]=1;
						return REPAIR_LEFT;
					}
	
					if( (brCol == col) && (brRow==row-1)  ){
		
						robotStates[i]=1;
						return REPAIR_UP;
					}

					if( (brRow == row) && (brCol==col+1)   ){
		
						robotStates[i]=1;
						return REPAIR_RIGHT;
					}
	

					//If the robot is directly on top of the broken robot
					if ( (brCol == col) && (brRow > row) ){	
	
						for( int idOther=0 ; idOther < NUM ; idOther++){
							if( idOther != id){			//Not the id of this robot
								if( ( area.locate(idOther).c == col ) && ( area.locate(idOther).r > row ) && (area.locate(idOther).r < brRow) ){ 
								//If theres another robot in between this robot and its destination then tell it to move somewhere else					
		
									if(COLS-1 == col){		//If we not all the way on the right side aka the right edge
										return LEFT;
									}

									if(0 == col){
										return RIGHT;
									}
									else{
										return RIGHT;
									}
								}
							}

						}	




						return DOWN;
	
					}	

					//If the robot is directly on the right of the broken robot
					if( (brRow==row) && (brCol<col)     ){

						for( int idOther=0 ; idOther < NUM ; idOther++){
							if( idOther != id){			//Not the id of this robot
								if( ( area.locate(idOther).r == row ) && ( area.locate(idOther).c < col ) && (area.locate(idOther).c > brCol) ){ 
								//If theres another robot in between this robot and its destination then tell it to move somewhere else					
		
									if(row == 0){		//If we not all the way on the right side aka the right edge
										return DOWN;
									}

									if(row == ROWS-1){
										return UP;
									}
									else{
										return DOWN;
									}
								}
							}

						}	

						return LEFT;
					}

					//If the robot is directly on the bottom of the broken robot
					if( (brCol == col) && (brRow < row) ){

						for( int idOther=0 ; idOther < NUM ; idOther++){
							if( idOther != id){			//Not the id of this robot
								if( ( area.locate(idOther).c == col ) && ( area.locate(idOther).r < row ) && (area.locate(idOther).r > brRow) ){ 
								//If theres another robot in between this robot and its destination then tell it to move somewhere else					
		
									if(COLS-1 == col){		//If we not all the way on the right side aka the right edge
										return LEFT;
									}

									if(col == 0){
										return RIGHT;
									}
									else{
										return LEFT;
									}
								}
							}

						}


						return UP;
					}

					//If the robot is directly on the left of the broken robot
					if( (brRow == row) && (brCol> col)   ){

						for( int idOther=0 ; idOther < NUM ; idOther++){
							if( idOther != id){			//Not the id of this robot
								if( ( area.locate(idOther).r == row ) && ( area.locate(idOther).c < col ) && (area.locate(idOther).c > brCol) ){ 
								//If theres another robot in between this robot and its destination then tell it to move somewhere else					
	
									if(row == 0){		//If we not all the way on the right side aka the right edge
										return DOWN;
									}

									if(row == ROWS-1){
										return RIGHT;
									}
									else{
										return UP;
									}
								}
							}

						}

						return RIGHT;
					}


					//^^^^^^^^^^^^^^^^^^^^ Now since we have these pre conditions if a robot is in quadrant 1,2,3,4 just tell it to go down until the broken robot and the robot are on 												the same row or column. 

					//If the robot is in Quadrant 1  Tell the robot to go down
					if ( (brRow > row) && (brCol < col)  ){
						return DOWN;
			
					}

					//If the robot is in Quadrant 4 Tell the robot to go left
					if( (brRow < row) && (brCol < col)  ){

						return LEFT;

					}

					//If the robot is in Quadrant 3 Tell the robot to go up
					if(  (brRow < row) && (brCol > col)  ){

						return UP;
					}

					//If the robot is in Quadrant 2 tell the robot to go right
					if(  (brRow > row) && (brCol > col) ){
						return RIGHT;

					}		
			}


//	}


	


	//IMPLEMENT GET DEBRIS
	
	//debrisGrid[][]
	//distances[][]
	//ROWS AND COLS 
	//row and loc current row and column
		
	
	

	//Reset debrisGrid[][] Everytime so you dont use old values
	for( int r=0 ; r<40 ; r++){
		for( int c=0; c<40 ; c++){
			debrisGrid[r][c]=0;

		}
	}
			
	//If theres a Debris at a spot make the value into a 1 from a 0
	for( int r=0 ; r< ROWS ; r++){
		for( int c=0; c< COLS ; c++){
			if( (area.inspect(r,c)) == DEBRIS){
				//log<<debrisGrid[r][c]<<endl;
				debrisGrid[r][c]=1;
				//log<<debrisGrid[r][c]<<endl;
			}
		}
	}

	//Reset the values for distances so you dont use old values
	for( int r=0 ; r<40 ; r++){
		for( int c=0; c<40 ; c++){
			distances[r][c]=100;
		}
	}

	//If theres a 1 at the debrisGrid then calculate the distance formula
	//That means there is a Debris at that point so now you calculate the distance formula and add that value to the distances. Now you go 
			//throught the distances and then see which value is the lowest. Then you go to that point, but this will cause the robots to go up if 
			//all the nearest are up and one is at the bottom. We can use modular to avoid this or have a way that each robot is assigned to its own 
			//coordinate
	//COUNTER FOR HOW MANY DEBRIS THERE ARE
	int numDebris=0;
	for( int r=0 ; r< 40 ; r++){
		for( int c=0; c< 40 ; c++){
			if( debrisGrid[r][c]==1){	
				numDebris+=1;	
				int xDistance=(c-col)*(c-col);									//x in this case would be the col
				int yDistance=(r-row)*(r-row);									//y is the row
				int beforeSqrt=xDistance+yDistance;
				double theDistance=sqrt(beforeSqrt);								
				distances[r][c]=theDistance;

			}


		}
	}
	
	//For loop find the lowest value in distances[][] and then now the robot will go to this location
	double min=distances[0][0];		//Update the min when we find a lower value for it
	int colDebris=0;							//Update the x coordinate when u find a distance that is smaller
	int rowDebris=0;							//Update the y coordinate when u find a distance that is smaller
	for( int r=0 ; r < ROWS ; r++){
		for( int c=0 ; c < COLS ; c++){
			if(min>distances[r][c]){
				min=distances[r][c];
				rowDebris=r;
				colDebris=c;
			}
		}
	
	}


	//We are using distancesOther[][]  ROWS COLS NUM
	//We are also using area.locate(ID).r

	//int colDebrisOther;
	//int rowDebrisOther;
	//double minOther=distancesOther[0][0];	//We might need to declare this in the for loop and reset it


	//if( numDebris > NUM){					//So we have every robot assigned to a DEBRIS, otherwise just follow each other around b/c there isnt enough DEBRIS
		for(int rank=0 ; rank < NUM ; rank++ ){	//Check the other robots distances and then find the min and for that min check if the coordinates are the same as this current robot's
			//log<<rank<<endl;
			if( rank != id){					//Check other robots not itself

				for(int r=0 ; r < 40 ; r++){		//Reset the distancesOther with every comparison
					for(int c=0 ; c < 40 ; c++){
						distancesOther[r][c]=100;
					}
				}

				//row and col are already declared for this robot coordinates so we need to declare our own
				int rowOther=area.locate(rank).r;
				int colOther=area.locate(rank).c;

				for(int r=0; r < ROWS ; r++){
					for(int c=0; c < COLS ; c++){
						if(debrisGrid[r][c]==1){
							int xDistanceOther=(c-colOther)*(c-colOther);			//x is the col
							int yDistanceOther=(r-rowOther)*(r-rowOther);			//y is the row
							int beforeSqrtOther=xDistanceOther+yDistanceOther;
							double theDistanceOther=sqrt(beforeSqrtOther);	
							distancesOther[r][c]=theDistanceOther;				//Calculate the distance of other Debris to the other robot coordinates and save it
							

						}
					}
				}

				double minOther=distancesOther[0][0];	//If there are no distances greater then minOther than minOther is [0][0]

				int colDebrisOther=0;
				int rowDebrisOther=0;
				
				for(int r=0 ; r < ROWS ; r++){							//Find the min value of the other robot's and the coordinates
					for(int c=0 ; c < COLS ; c++){
						if(minOther > distancesOther[r][c]){		//Find the minimum. If minOther is greater than a number then make that number the min, because it is less
							minOther=distancesOther[r][c];
							colDebrisOther=c;
							rowDebrisOther=r;
						}

					}
				}

				if( (colDebris==colDebrisOther) && (rowDebris == rowDebrisOther)  ){
					//Whoa whoa whoa we decided that the mins can be the same or they can be different but the nearest Debris can be the same to two or more robots
					//If two robot's have the same nearest then we need to change our robot's min to 100 because you want it to find another DEBRIS and find a new min
					
					//Set that coordinate to a 100 aka ignore this debris		

					if( min > minOther ){
						distances[rowDebris][colDebris]=100;
					}
		
					//WE FORGOT TO RESET MINNNNNNNNNNNNNNN
					min=distances[0][0];
					rowDebris=0;
					colDebris=0;
					for(int r=0 ; r< ROWS ; r++){					//Now find the new min for this robot aka find another coordinate (DEBRIS) for the robot to go to
						for(int c=0 ; c < COLS ; c++){

							if(min > distances[r][c]){
								min=distances[r][c];
								rowDebris=r;
								colDebris=c;
							}
						}
					}

				}				

			}
		}
	//}


	if (area.inspect(row, col) == DEBRIS){	//If the robot is on a debris then collect it
		return COLLECT;
	}

	//Now you know the coordinate of the nearest DEBRIS so just go for it now
	//We know the MINIMUM DISTANCE, COLDEBRIS, ROWDEBRIS and the ROBOT'S OWN COORDIANTES AKA row and col

	if( (colDebris== col) && (rowDebris==row+1)  ){

				return DOWN;
	}

	if( (rowDebris == row) && (colDebris==col-1) ){

		return LEFT;
	}
	
	if( (colDebris == col) && (rowDebris==row-1)  ){

		return UP;
	}

	if( (rowDebris == row) && (colDebris==col+1)   ){

		return RIGHT;
	}
	

	//If the robot is directly on top of the broken robot
	if ( (colDebris == col) && (rowDebris > row) ){
		return DOWN;
	
	}	

	//If the robot is directly on the right of the broken robot
	if( (rowDebris==row) && (colDebris<col)     ){
		return LEFT;
	}

	//If the robot is directly on the bottom of the broken robot
	if( (colDebris == col) && (rowDebris < row) ){
		return UP;
	}

	//If the robot is directly on the left of the broken robot
	if( (rowDebris == row) && (colDebris> col)   ){
		return RIGHT;
	}


	//^^^^^^^^^^^^^^^^^^^^ Now since we have these pre conditions if a robot is in quadrant 1,2,3,4 just tell it to go down until the broken robot and the robot are on the same 											row or column. 

	//If the robot is in Quadrant 1  Tell the robot to go down
	if ( (rowDebris > row) && (colDebris < col)  ){
		return DOWN;
			
	}

	//If the robot is in Quadrant 3 Tell the robot to go left
	if( (rowDebris < row) && (colDebris < col)  ){

		return LEFT;

	}

	//If the robot is in Quadrant 4 Tell the robot to go up
	if(  (rowDebris < row) && (colDebris > col)  ){

		return UP;
	}

	//If the robot is in Quadrant 2 tell the robot to go right
	if(  (rowDebris > row) && (colDebris > col) ){
		return RIGHT;

	}



	
}

void onRobotMalfunction(int id, Loc loc, Area &area, ostream &log) {
	int row = loc.r; // current row and column
	int col = loc.c;

	//Update Array robotStates for this broken robot's index to a 0 not a 1. And when it is repaired you turn that 0 into a 1.
	robotStates[id]=0;


	log << "Robot " << id << " is damaged." << row << ' ' << col <<  endl;

}

void onClockTick(int time, ostream &log) {
	if (time % 100 == 0) log << time << " ";
}
