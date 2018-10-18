







	//distances[colDebris][rowDebris]=min;
	//^^^^^^^^^^^^^^^^ This is wrong I was expecting min to be distance and it is, but its distances[rowDebris][colDebris] instead
	
	
	/*
	log<<"area "<<area.inspect(rowDebris,colDebris)<<endl;
	log<<"rowDebris "<<rowDebris<<endl;
	log<<"colDebris "<<colDebris<<endl;
	log<<"min "<<min<<endl;
	log<<"distance "<<distances[colDebris][rowDebris]<<endl;
	*/

	
	//We need to implement a way so that if another robot has this distance at this point compared to its coordinate then we need to change the distances[rowDebris][colDebris]=100; and
		//then loop the distances again
		//Variables needed:  rank , id , NUM , colDebris, rowDebris , area.locate(ID).r , area.locate(ID).c
	//double minNew=distances[0][0];
	//log<<"mineNew "<<minNew<<endl;
	//int colDebrisNew;
	//int rowDebrisNew;




/*
^^^^^^^^^^^^^^^^^^^^^ This doesnt count for say: if one robot's nearest and another robot's nearest have the same nearest Debris, but their distance is different. We need to account 
for different distances, so we need to check different arrays looking to see if they have the same min coordinate. colDebris== colOther rowDebris== rowOther
		

*/	



double minNew=distances[0][0];
	
	for( int rank=0 ; rank< NUM	; rank++){				//Loop for checking through all the ids
		if ( rank != id ){ 					//Avoid the robot's own id, because we already computed it
			int xOtherRobot=(colDebris - (area.locate(rank).c)) * (colDebris - (area.locate(rank).c));				//area.locate(ID).r
			int yOtherRobot=(rowDebris - area.locate(rank).r) * (rowDebris - area.locate(rank).r);			//I forgot to subtract the cols and rows of the Debris and the otherRobot's 
																												//location
			
			int beforeSqrtRobot= (xOtherRobot) + (yOtherRobot);
			double otherDistance=sqrt(beforeSqrtRobot); 
			
			//log<<otherDistance<<endl;
			//log<<min<<endl;
				
			if	( otherDistance == min){				//If another robot has the same distance to the same debris then we must find another min value with coordinates
				//log<<"distance "<<distances[colDebris][rowDebris]<<endl;
				
				distances[rowDebris][colDebris]=100;
				//log<<"distance "<<distances[colDebris][rowDebris]<<endl;
				//log<<rank<<endl;
				//log<<otherDistance<<endl;
				//log<<min<<endl;
		
				for ( int r=0; r < ROWS ; r++){
					for( int c=0; c < COLS ; c++){
						if(minNew > distances[r][c]){
							minNew=distances[r][c];
							rowDebris=r;
							colDebris=c;

						}				
					}
				}





			}		
		}

	}

