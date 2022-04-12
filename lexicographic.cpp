/*
	Author: 		April Crockett
	File: 			lexicographic.cpp
	Date Created: 	Fall 2019
	Date Updated: 	Fall 2022
	Purpose: Use the Lexicographic Permutation algorithm to generate all permutations 
		of a given string of n length
	Assumptions: Assume that the input will already be sorted 
		and that no input checking is needed
*/
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

void lexicographic(string *s,int);

int main()
{
	string inputString;
	int inputLength;
	
	cout << "\nEnter a string to find its permutations: ";
	cin >> inputString;
	inputLength = inputString.length();
	
	lexicographic(inputString,inputLength);
	
	cout << "\n\nAll done!";
	
	return 0;
}

void lexicographic(string *s, int size)
{
	string tempString = s;
	bool isDone = false;
	int iterationCount = 1;
	int lowBound = 0;		//The "i" value
	int uppBound = 0;		//The "j" value
	
	//Temporary variables to store values during a swap
	char tempChar;
	string swapString;
	
	cout << "\nLEXICOGRAPHIC ALGORITHM";
	
	while(!isDone)
	{
		/*
			---PRINT TEMPSTRING---
		*/
		cout << "\n" << iterationCount << ":\t" << tempString;
		iterationCount++;
		/*
			---FIND lowBound OR DETERMINE IF DONE---
		*/
		isDone = true;
		for(int i = 0; i < size-1; i++)
		{
			if(tempString[i]<tempString[i+1])
			{
				isDone = false;
				lowBound = i;
			}
		}
		if(isDone)
			continue;
		/*
			---FIND uppBound---
		*/
		for(int j = size-1; j>0; j--)
		{
			if(tempString[j] > tempString[lowBound])
			{
				uppBound = j;
				break;
			}
		}
		/*
			---SWAP ELEMENTS---
		*/
		tempChar = tempString[lowBound];
		tempString[lowBound] = tempString[uppBound];
		tempString[uppBound] = tempChar;
		/*
			---REVERSE ELEMENTS FROM lowBound+1 TO l-1---
		*/
		swapString = tempString;
		for(int i = 1;i < size-lowBound;i++)
		{
			swapString[lowBound+i] = tempString[size-i];
		}
		for(int i = 1;i < size-lowBound;i++)
		{
			tempString[lowBound+i] = swapString[lowBound+i];
		}
		/*
			---PRINT lowBound AND uppBound---
		*/
		cout << "\ti = " << lowBound << "\tj = " << uppBound;
	}
	cout << "\nLexicographic Algorithm complete!";
}