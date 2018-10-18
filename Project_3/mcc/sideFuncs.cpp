/*
Action checkThreeByThree( Loc loc, Area &area ) {
	
		Input: Same values as onRobotAction, but checks the 3x3 around the robot
		Output: UP DOWN LEFT RIGHT COLLECT 
	

	int row = loc.r; // current row and column
	int col = loc.c;

		if(area.inspect(row-1, col) == DEBRIS){		//Above
			return UP;
		}
		if(area.inspect(row, col+1) == DEBRIS){		//To the right
			return RIGHT;
		}
		if(area.inspect(row+1, col) == DEBRIS){		//Down
			return DOWN;
		}
		if(area.inspect(row, col-1) == DEBRIS){		//To the left
			return LEFT;
		}
		if(area.inspect(row-1, col-1) == DEBRIS){
			return LEFT;
		}
		if(area.inspect(row-1, col-1) == DEBRIS){
			return UP;
		}

		if(area.inspect(row+1, col-1) == DEBRIS){
			return LEFT;
		}
		if(area.inspect(row+1, col+1) == DEBRIS){
			return RIGHT;
		}

		else{
			switch(rand() % 4) {
			case 0:
				return LEFT;
			case 1:
				return RIGHT;
			case 2:
				return UP;
			default:
				return DOWN;
			}
		}
	}




//Maybe make 3X3 a function?
	// Check 3x3 but it has clockwise priority. UP RIGHT DOWN LEFT

		if(area.inspect(row-1, col) == DEBRIS){		//Above
			return UP;
		}
		if(area.inspect(row, col+1) == DEBRIS){		//To the right
			return RIGHT;
		}
		if(area.inspect(row+1, col) == DEBRIS){		//Down
			return DOWN;
		}
		if(area.inspect(row, col-1) == DEBRIS){		//To the left
			return LEFT;
		}
		if(area.inspect(row-1, col-1) == DEBRIS){
			return LEFT;
		}
		if(area.inspect(row-1, col-1) == DEBRIS){
			return UP;
		}

		if(area.inspect(row+1, col-1) == DEBRIS){
			return LEFT;
		}
		if(area.inspect(row+1, col+1) == DEBRIS){
			return RIGHT;
		}


	else {
		//checkThreeByThree(  loc, area );


		// Check 5x5
			//Checks the 5*1 on top
		for(int c=(col-2); c<col+3 ; c++){  
			if(area.inspect(row-2, c) == DEBRIS){
				return UP;
			}
		}

			//Checks the 5*1 on the right
		for(int r=(row-2) ; r<row+3 ; r++){				
			if(area.inspect(r, col+2) == DEBRIS){
				return RIGHT;
			}

		}
			//Checks the 5*1 on the bottom
		for(int c=(col-2); c<col+3 ; c++){  
			if(area.inspect(row+2, c) == DEBRIS){
				return DOWN;
			}
		}
			//Checks the 5*1 on the left
		for(int r=(row-2) ; r<row+3 ; r++){				// i<row+3 is up to row+2
			if(area.inspect(r, col) == DEBRIS){
				return LEFT;
			}

		}

		// if not at a debris field, move randomly:
		switch(rand() % 4) {
		case 0:
			return LEFT;
		case 1:
			return RIGHT;
		case 2:
			return UP;
		default:
			return DOWN;
		}
	}



*/
