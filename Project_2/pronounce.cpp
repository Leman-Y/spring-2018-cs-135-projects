/*
Author: Leman Yan
Course: CSCI-135
Instructor: Genady Maryash
Assignment: Project 2

In this project you are going to implement a linguistic application that uses a pronunciation dictionary for finding words with similar pronunciation.

Lets the user input a word (let’s call the input word W).

If the word is not found in the dictionary, print “Not found”. Otherwise, report:

Pronunciation : the pronunciation of the word W (as given in the dictionary),
Identical : other words from the dictionary with the same pronunciation as W,
Add phoneme : words that can be obtained from W by adding one phoneme,
Remove phoneme : words that can be obtained from W by removing one phoneme,
Replace phoneme : words that can be obtained from W by replacing one phoneme.
When listing words, include all words from the dictionary that meet the criteria, the order of listed words should be the same as they appear in the dictionary.
*/

/*
	1. First we need to check if the input is even a word itself. Word doesn't have to be case sensitive
	Pronounciation returns not found pronounciation not found that does not work so we need to tweak
*/

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

void splitOnSpace(string s, string & before, string & after) {			//Splits the word and the pronounciation apart from each other in the dict list
  // reset strings
  before = ""; 
  after = "";
  // accumulate before space
  int i = 0;
  while (i < s.size() && not isspace(s[i])) { before += s[i]; i++; }
  // skip the space
  i++;
  // accumulate after space
  while (i < s.size()) { after += s[i]; i++; }
}


string pronounciation(string W){			//We are finding if the word is in the dictionary. If it matches with one of the string before

	//Check if the word is even a word. The check if the word is even in the file. If it is then we may proceed if not then "Not found."

	int counter=0;

	if((W.length()==0) || char (W[0]) == ' '){
		return "Not found";
	}	

	//Use ascii code   39 is apostrophe

	for(int i=0 ; i<W.length() ; i++){			//Checks if all the characters are letters or an apostrophe
		if( (char (W[i]) ==39) || ( ((char (W[i]) >= 65) && (char(W[i])<=90)) ) || ( ((char (W[i]) >= 97) && (char(W[i])<=122)) ) ){
			counter+=1;  
		}
		else{
			return "Not found";	
		}
	}

	string upperW;        			//All uppercase Word
	if(counter == W.length() ){		//That means the word inserted is a word
		for(int i=0 ; i<W.length() ; i++)	//Make the word into an uppercase word
		{
			if( (char (W[i]) >= 97) && (char(W[i])<=122) ){
				upperW+= (char ( (char (W[i]))-32 ));
			}
			else{
				upperW+=W[i];
			}
		}
	}

	string line;
	string before;
	string after;
	string pronounciation;

	ifstream fin("cmudict.0.7a");									//Input the lines from the file
	if (fin.fail()) {
	  cerr << "File cannot be opened for reading." <<endl;
	   exit(1); // exit if failed to open the file
	}
	
	for(int i=0 ; i<54 ; i++){									//Skip the first 54 lines, because they are semi colons and do not match with the words we need.
		getline(fin,line);
	}

	while(getline(fin,line)){					//Check every line to see if the word matches a word in the dict
		splitOnSpace(line, before, after);
		if(upperW == before){					//If there is a word that matches with upper
			pronounciation=after;				//Set pronounciation to after
		}
	}
	
	if(pronounciation.length()==0){				//If there is not word that matches the input word then return not found
		return "Not found";
	}

	fin.close();
	

	return pronounciation;							//If not then it is found
}

string identical (string W){
	/*
	So identical wants other words with the same pronounciation. However we do not print the first word along with it. Therefore we need to loop through everything to find the word 			and its pronounciation. Then compare the pronounciation to any other words that have the same pronounciation. We add them to a string then we return the string. It can be empty 			or not empty.
	*/

	//First make the word an uppercase word so it matches with the word in the dictionary

	string line;
	string before;			//Use this solely for the splitonspace function because apparently it is affecting it
	string after;

	string list; //list of words that have identical pronounciation
	string before1;
	string after1;
	string pronounciation;
	string before2;
	string after2;
	string word;

	ifstream fin("cmudict.0.7a");

	if (fin.fail()) {
	  cerr << "File cannot be opened for reading." <<endl;
	   exit(1); // exit if failed to open the file
	}
	
	for(int i=0 ; i<54 ; i++){
		getline(fin,line);
	}

	while(getline(fin,line)){					//Check every line to see if the word matches a word in the dict
		splitOnSpace(line, before, after);
		if(W == before){
			word=W;						//Use this to compare with the next before and after string
			pronounciation=after;				//Use this to compare with the next after string
		}
	}

	fin.close();

	// SECOND TIME READING THE FILE

	ifstream dict("cmudict.0.7a");						//Second time going through the file

	if (dict.fail()) {
	  cerr << "File cannot be opened for reading." <<endl;
	   exit(1); // exit if failed to open the file
	}
	
	for(int i=0 ; i<54 ; i++){
		getline(dict,line);
	}

	while(getline(dict,line)){					//Check every line to see if the word matches a word in the dict
		splitOnSpace(line, before1, after1);
		if(pronounciation == after1){			//Find a word that has the same pronounciation as the inputted word's pronounciation
			if(word != before1){				//If it is not the original word then add it to the list
				list+=before1+" ";
			}
		}
	}

	dict.close();

	return list;
}

int numPhonemes(string pronounciation){
/*
	I mean there has to be a pronounciation otherwise there is no word. Therefore we can assume that every word has at least one phoneme aka a pronounciation.
	Number of spaces are directly related to the number of phomemes
*/

	int count=0;   //Counts the number of spaces so basically number of phomemes
	
	for(int i=0 ; i<pronounciation.length() ; i++){
		
		if(isspace(pronounciation[i]) ){
			count+=1;
		}	
	}

return count;				//Returns number of phonemes
}

string firsthalf (string pronounciation , int index){			//Removes the second half of the string
																//AKA Removes everything at the index and everything after
	/*
    string phonemes=" AA BB CC";
  	cout<<firsthalf(phonemes, 3)<<endl;				Gives you " AA";
	*/
	int counter=0;
		
	string empty="";  					//This string will return the new string that returns the first half of the pronounciation

	for(int i=0 ; i<index; i++){
		empty+=pronounciation[i];		//Just add the characters from the string until i is equal to index
	}

return empty;
}

string cutPhoneme (string pronounciation, int index , int len){		//Removes the phoneme from the string given a the 1st and 2nd position of where you want to cut the string
																	//Index is the starting position where you start to remove the next couple of characters determined by a length
	string empty="";
	int counter=0;
	
	for( int i=0; i<pronounciation.length() ; i++){					//This function does the same thing as erase. 
		if(i == index){												//Keep on adding the characters unless i is equal to the index. Then that means you need to skip over the phoneme by 
			i=i+len;												//	len. And then keep on adding the characters
		}				
		empty+=pronounciation[i];
	}

	return empty;						//Returns the pronounciation without the phoneme
}

string nthPhoneme (string pronounciation, int index){						//Gives you nth phoneme so you can use to compare for replace
	//3 Cases: There is only 1 phoneme, the last phoneme is needed, the middle phoneme that is between spaces
	string empty;

	if(numPhonemes(pronounciation) ==1){
		return cutPhoneme(pronounciation, 0, 1);	//Just cut the beginning space and return the phoneme
	}
	
	int counter=0;   		//For if the num of phonemes equals to the index.  ALWAYS DECLARE THE COUNTER TO ZERO OR ELSE IT WILL BE A BIG NUMBER

	if(numPhonemes(pronounciation) == index) 
	{
		for(int i=0 ; i<pronounciation.length() ; i++)
		{
			if(counter == index)
			{
				empty+=pronounciation[i];					//Add the last phoneme to the empty string only
			}
			if(isspace(pronounciation[i])  )				//You do not want the space "_phoneme". You want "phoneme".		
			{
				counter+=1;
			}
		}
		
		return empty;
	}

	int pos;			//Position of first space
	int pos2;			//Position of second space
	int count=0;		//Count number of spaces. If you know where the first space is then you know where to start adding characters and with the second space you know when to stop

	for(int i=0 ; i<pronounciation.length() ; i++)
	{
		if(isspace(pronounciation[i]) )
		{
			count+=1;
			if(count == index){
				pos=i;
			}
			else if (count == (index+1) ){
				pos2=i;
			}
		}
	}

	for(int i=pos+1 ; i<pos2 ; i++){			//pos+1== the letter after the space and i<pos2== add the characters until you reach the next space
		empty+=pronounciation[i];				//Adds the phoneme to the empty string
	}

	return empty;						//Return the phoneme
}

string removePhoneme(string pronounciation, int index){		//Remove the nth phoneme and then returns the string
	/*
		Seems like every word after 54th line has a pronounciation so we dont need to worry about removing all the pronounciations because there will be no pronounciation with nothing
			inside the string
		Here we cover all 3 tests cases: First phoneme, phoneme between spaces, and the last phoneme with more than 1 phoneme
	*/
	string phonemes="";							//Return the phomemes after you removed one							

	if(numPhonemes(pronounciation) ==1  ){				//If there is only one phomeme just return an empty string
		return phonemes;						//Empty string
	}

	int counter=0;								//Number of spaces

  //string.erase( number ) erases everything starting that number and everything after
  
  //string.erase(number1 , number2) erases everything starting at number1 and then erases the chars after it by length number2

	if( numPhonemes(pronounciation) == index){					//If the index equals to the amount of phomemes cut the last phoememe off
		for(int i=0; i<pronounciation.length() ; i++){
			if( isspace(pronounciation[i])  ){
				counter+=1;
				if (counter == index){
					//phonemes=pronounciation.erase(i);				//You cant use erase so use the new function I made
					phonemes=firsthalf(pronounciation ,i);
				}
			} 

		}
		return phonemes;
	}

	int len=1;									//The length of the phomeme from _ab_ so 2
	int pos;									//Index of first space
	int pos2;									//Index of second space
	int difference;
	int count=0;

	for(int i=0; i<pronounciation.length() ; i++){			//Cut the phomeme between two spaces
		if( isspace(pronounciation[i])  ){
			counter+=1;
			if (counter == index){
				pos=i;										//We found the first space
			}
		}
		
	}

	for(int i=0; i<pronounciation.length() ; i++){				//Finds the space after the phoneme. Finds the length by subtracting position of second space by first. Then new string 
		if( isspace(pronounciation[i]) ){						//	will remove that phoneme
			count+=1;
			if (count == (index+1) ){
				pos2=i;
				int difference=pos2-pos;				//Now count how long is the length of the phomeme. Leave the second space
				//phonemes=pronounciation.erase(pos, difference);
				phonemes= cutPhoneme( pronounciation , pos , difference);
				return phonemes;
			}
		}

	}	
	
	return phonemes;
}

string add(string upperW){
	/*
		Read the file twice. Check if the word is in the dict. If it is then save word and its pronounciation. Loop through and remove only one phoneme from the pronounciation of the 
		words and their pronounciations. This is, because the add phoneme word is one phoneme away from the original pronounciation. Therefore you just check every word and remove one 
		phoneme and check if that is the same as your pronounciation. If it is then you found a word that is one phoneme + original pronounciation. Then you need to check if the word 
		is an actual world. ANCHORMAN(1) is not a word
	*/
	string line;
	string before;
	string after;
	string before1;
	string after1;
	string word;
	string pronounciation;

	ifstream fin("cmudict.0.7a");

	if (fin.fail()) {
	  cerr << "File cannot be opened for reading." <<endl;
	   exit(1); // exit if failed to open the file
	}
	
	for(int i=0 ; i<54 ; i++){
		getline(fin,line);
	}

	while(getline(fin,line)){					//Check every line to see if the word matches a word in the dict
		splitOnSpace(line, before, after);
		if(upperW == before){
			word=upperW;						//Use this to compare with the next before and after string
			pronounciation=after;				//Use this to compare with the next after string
		}
	}

	fin.close();

	// SECOND TIME READING THE FILE

	string list; 							//List of words that you get by removing a phoneme from the pronounciation

	ifstream dict("cmudict.0.7a");				//Second time trying to do this doesnt work as ifstream fin but if you change fin to dict it works

	if (dict.fail()) {
	  cerr << "File cannot be opened for reading." <<endl;
	   exit(1); // exit if failed to open the file
	}
	
	for(int i=0 ; i<54 ; i++){
		getline(dict,line);
	}
	
	int counter=0;

	while(getline(dict,line)){					//Check every line to see if the word matches a word in the dict
		splitOnSpace(line, before1, after1);
		for(int i=1 ; i< (numPhonemes(after1)+1); i++  ){
			if(pronounciation == removePhoneme(after1, i)  ){
				if(pronounciation != before1){
/* 
	This chunk of code reassures that the word that is one phoneme away from the original word's pronounciation is actually a word itself. ANCHORMAN(1) is not a word
*/
					for(int i=0 ; i<before1.length() ; i++){						
						if( (char (before1[i]) ==39) || ( ((char (before1[i]) >= 65) && (char(before1[i])<=90)) ) || ( ((char (before1[i]) >= 97) && (char(before1[i])<=122)) ) ){
							counter+=1;  
						}
					}
					if(counter == before1.length()  ){
						list+=before1+' ';
					}
						counter=0;						//Reset counter
				}
			}
		}
	}

	dict.close();

return list;

}

string remove(string upperW){
	/*
	You basically just make a loop that goes to how many phonemes the word's pronounciation has. Then you remove the 1st, 2nd, nth phoneme depending on how many phonemes there are.
	You only remove one phoneme from the pronounciation, because the remove word is the same as the word; but just one phoneme away. By doing this you get the removed words.
	*/
	string line;
	string before;
	string after;
	string before1;
	string after1;
	string word;
	string pronounciation;

	ifstream fin("cmudict.0.7a");

	if (fin.fail()) {
	  cerr << "File cannot be opened for reading." <<endl;
	   exit(1); // exit if failed to open the file
	}
	
	for(int i=0 ; i<54 ; i++){
		getline(fin,line);
	}

	while(getline(fin,line)){					//Check every line to see if the word matches a word in the dict
		splitOnSpace(line, before, after);
		if(upperW == before){
			word=upperW;						//Use this to compare with the next before and after string
			pronounciation=after;				//Use this to compare with the next after string
		}
	}

	fin.close();

	// SECOND TIME READING THE FILE

	string list; 							//List of words that you get by removing a phoneme from the pronounciation

	ifstream dict("cmudict.0.7a");				//Second time trying to do this doesnt work as ifstream fin but if you change fin to dict it works

	if (dict.fail()) {
	  cerr << "File cannot be opened for reading." <<endl;
	   exit(1); // exit if failed to open the file
	}
	
	for(int i=0 ; i<54 ; i++){
		getline(dict,line);
	}

	while(getline(dict,line)){					//Check every line to see if the word matches a word in the dict
		splitOnSpace(line, before1, after1);
		for(int i=1 ; i< (numPhonemes(pronounciation)+1); i++  ){
			if(after1 == removePhoneme(pronounciation, i)  ){
				list+=before1+' ';
			}
		}
	}

	dict.close();

return list;
} 

string replace(string upperW){
	/*
	You basically need to loop through the original pronounciation and remove the only one phonemes one by one. These strings with n-1 phonemes (n is how many phonemes the string has) 	will be compared with the dict words and they will hae a loop that makes it so they have n-1 phonemes as well. If there is pronounciation match between these two words that means 		they have the same n-1 pronounciation. Now we need to make sure their removed phonemes are different, if it is different then that is a word that can be obtained from W by
	replacing one phoneme. Then finally we need to check if the word is actually a word itself.
	*/
	string line;
	string before;
	string after;
	string before1;
	string after1;
	string word;
	string pronounciation;

	ifstream fin("cmudict.0.7a");

	if (fin.fail()) {
	  cerr << "File cannot be opened for reading." <<endl;
	   exit(1); // exit if failed to open the file
	}
	
	for(int i=0 ; i<54 ; i++){
		getline(fin,line);
		//cout<<line<<endl;
	}

	while(getline(fin,line)){					//Check every line to see if the word matches a word in the dict
		splitOnSpace(line, before, after);
		if(upperW == before){
			word=upperW;						//Use this to compare with the next before and after string
			pronounciation=after;				//Use this to compare with the next after string
		}
	}

	fin.close();

	// SECOND TIME READING THE FILE

	string list=""; 							//List of words that you get by removing a phoneme from the pronounciation

	ifstream dict("cmudict.0.7a");				//Second time trying to do this doesnt work as ifstream fin but if you change fin to dict it works

	if (dict.fail()) {
	  cerr << "File cannot be opened for reading." <<endl;
	   exit(1); // exit if failed to open the file
	}
	
	for(int i=0 ; i<54 ; i++){
		getline(dict,line);

	}

	/*
	This chunk of code will loop through the original pronounciaiton and remove a phoneme one at a time. Then we will loop through this line's pronounciation and remove a phoneme 
		one at a time. If they match up, then that means these two pronounciations are one phoneme away from each other. However other words can have the same pronounciation even
		if the phoneme is removed, therefore we need to check that the removed phonemes are not the same.
	*/

	int counter=0;

	while(getline(dict,line))
	{
		splitOnSpace(line, before1, after1);
		for(int i=1; i<(numPhonemes(pronounciation)+1); i++ )
		{
			if(numPhonemes(pronounciation) == numPhonemes(after1) ){
				if(removePhoneme(pronounciation, i) == removePhoneme(after1, i) )
				{
					if(nthPhoneme(pronounciation,i) != nthPhoneme(after1, i) )	//If the pronounciation goes to here then the word is a replaced phoneme away from the original word
					{															//Now we just gotta check if the word is even a word itself
						for(int i=0 ; i<before1.length() ; i++)
						{						
							if( (char (before1[i]) ==39) || ( ((char (before1[i]) >= 65) && (char(before1[i])<=90)) ) || ( ((char (before1[i]) >= 97) && (char(before1[i])<=122)) ) ){
								counter+=1;  
							}
						}
						if(counter == before1.length()  )
						{
							list+=before1+' ';
						}
							counter=0;
					}					
				}

			}		
		}
	}

	dict.close();

	return list;
}


int main(){

string W;

cin>>W;								//Cin just gets the first word so "app bap" works because it takes in "app" not "app bap". This solves the problem if gradescope enters two words.

	int counter=0;
	string upperW;        			//All uppercase Word
										//Make the input word into an uppercase word, because all the words in the dict list are uppercase words.
	for(int i=0 ; i<W.length() ; i++)
	{

		if( (char (W[i]) >= 97) && (char(W[i])<=122) ){
			upperW+= (char ( (char (W[i]))-32 ));
		}

		else{
			upperW+=W[i];
		}

	}
	
if(pronounciation(upperW) != "Not found")		//Now we know it is a word if it doesnt equal to not found. So execute the smaller programs
{		
	cout<<"Pronunciation    :"<<pronounciation(upperW)<<endl;		
	cout<<endl;
	cout<<"Identical        : "<<identical(upperW)<<endl;
	cout<<"Add phoneme      : "<<add(upperW)<<endl;
	cout<<"Remove phoneme   : "<<remove(upperW)<<endl;
	cout<<"Replace phoneme  : "<<replace(upperW)<<endl;


}
else							//If the word is not even a word
{
	cout<<"Not found"<<endl;
}

}



