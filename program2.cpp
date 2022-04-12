/*
     Title:     Program 2
     Author:    Sean Tyrer
     Date:      4/10/2022
     Purpose:   Traveling Salesman - find the lowest cost
                tour when traveling from US to 8 other countries
                and then back to US.
*/

#include <iostream>
#include <fstream>
#include <cmath>
#include "GraphMatrix.h"
using namespace std;
int tourArray= 0;
const int SIZE = 10;
const string COUNTRY_CODES[SIZE]={"AU", "BR", "CA", "CN", "GL", "IT", "NA", "RU", "US", "US"};

/*
	Use the following structure to store each tour & its cost
	You will create an array of Tour variables in your program
*/
struct Tour
{
	string tour[SIZE];
	int cost;
};

//Function Prototypes
GraphMatrix* readFileMakeMatrix();
void printStringArray(string*, int );
void lexicographic(string *, int, Tour *, GraphMatrix *);
int searchCountryCode(string);
void saveTour(string *, Tour *, GraphMatrix *);
int getWeight(int , int );
void findLowest(Tour *);

int main()
{	
	Tour *tourOptions = new Tour[40320];
	//read in the flight information from the file and then create the weight matrix
	GraphMatrix * matrix = readFileMakeMatrix();
	string * countries = new string[SIZE-2];
	
	cout << "\n\n*************************COUNTRIES*******************\n";
	for(int x=0; x < SIZE-2; x++)
	{
		countries[x] = COUNTRY_CODES[x];
	}
	
	
	//generate all possible tours (starting & ending with "US") using lexicographic permute algorithm
	//you will need to call your lexicographic function, sending the modified countries array with the 8 country codes
	lexicographic(countries, SIZE-2, tourOptions, matrix);
	cout << "\n\n*************************SOLUTION*******************\n";
	//find the lowest cost tour and print it out (including the cost)
	
	
	cout << "\nHappy Traveling!\n";
	findLowest(tourOptions);
	//don't forget to release anything that was dynamically allocated!

	
	return 0;
}
/*
	Function: searchCountryCode
	Parameters: a string with the country code like "BR"
	Returns: an integer representing this country's index in the GraphMatrix.
	For example, if the parameter is "BR", it should return index 1.  If the parameter is "CA", it should return index 3
	It is returning the index value in the COUNTRY_CODES array.	
	Implement this search function with the binary search algorithm!
*/
int searchCountryCode(string x)
{
	int l = 0;
	int h = SIZE - 1;
	int m = 0;

	 while (l <= h) {
        int m = (l+h) / 2;
 
        // Check if x is present at mid
        if (COUNTRY_CODES[m] == x){
            return m;
		}
        // If x greater, ignore left half
        else if (COUNTRY_CODES[m] < x)
		{
            l = m + 1;
		}
        // If x is smaller, ignore right half
        else
		{
		  h = m - 1;
		}
    }
 
    
    return -1;
}

/*
	Title: readFileMakeMatrix
	Purpose:  this function will read the data in flights.txt and create an
	adjacency matrix with the couuntry codes.  The matrix values will be the
	cost of the flights.
*/
GraphMatrix* readFileMakeMatrix()
{
	ifstream inFile;
	GraphMatrix * matrix = new GraphMatrix(SIZE-1);
	cout << "\nCreated the matrix.";
	string country1, country2;
	int price;
	inFile.open("flights.txt");
	cout << "\nReading from flights.txt\n";
	if(inFile)
	{
		while(inFile >> country1)
		{
			inFile >> country2;
			inFile >> price;
			//add price to graph matrix
			matrix->addEdge(searchCountryCode(country1), searchCountryCode(country2), price);
			cout << "\nAdded edge from " << country1 << " to " << country2 << " with cost of $" << price;
		}
	}
	else
		cout << "\nSorry, I am unable to open the file.\n";
	inFile.close();
	cout << "\n\nFLIGHT PRICE GRAPH MATRIX\n";
	matrix->printGraph();
	cout << endl;
	return matrix;
}

/*
	Title: printStringArray
	Purpose:  this function will print the array of strings with a space
		between each string
*/
void printStringArray(string* arr, int size)
{
	for(int x=0; x<size; x++)
	{
		cout << arr[x] << " ";
	}
	cout << endl;
}

/*
	Title: lexicographic
	Purpose:  this function will organize the array.
*/


void lexicographic(string *s, int size, Tour *tourOptions, GraphMatrix *matrix)
{	
	string buffer[size];
	string tempString[size];
	
	for (int i = 0; i < size; i++)
	{
		tempString[i] =s[i];
	}
	bool isDone = false;
	int iterationCount = 1;
	int lowBound = 0;		//The "i" value
	int uppBound = 0;		//The "j" value
	
	//Temporary variables to store values during a swap
	string swapString;
	
	cout << "\nLEXICOGRAPHIC ALGORITHM";
	
	while(!isDone)
	{
		/*
			---PRINT TEMPSTRING---
		*/
		cout << "\nTour : " << iterationCount;
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
		
		buffer[lowBound]= tempString[lowBound];
		tempString[lowBound] = tempString[uppBound];
		tempString[uppBound] = buffer[lowBound];
		/*
			---REVERSE ELEMENTS FROM lowBound+1 TO l-1---
		*/
		
		for(int i = 1;i < size-lowBound;i++)
		{
			buffer[lowBound+i] = tempString[size-i];
		}
		for(int i = 1;i < size-lowBound;i++)
		{
			tempString[lowBound+i] = buffer[lowBound+i];
		}
		/*
			---PRINT lowBound AND uppBound---
		*/
		//cout << "\ti = " << lowBound << "\tj = " << uppBound;

		saveTour(tempString, tourOptions, matrix);
		tourArray++; //Allowing more data to enter the array in saveTour function


	}
	cout << "\nLexicographic Algorithm complete!";
}

void saveTour(string *tempString, Tour *tourOptions, GraphMatrix * matrix)
{
	int cost = 0;
	string buff[10];
	for (int i=0; i<10; i++){
		if (i ==  0 || i == 9){
			buff[i] ="US";
		}

		else{
			buff[i] = tempString[i-1];
		}
	}
	cout << endl;
	printStringArray(buff, 10);
	cout << endl;
	for (int i = 0; i < 9; i++)
	{
		cost += matrix-> getWeight(searchCountryCode(buff[i]), searchCountryCode(buff[i+1]));
	}

	tourOptions[tourArray].cost = cost;
	for (int i = 0; i < 10; i++)
	{
		tourOptions[tourArray].tour[i] == buff[i];
	}
	cout << "Cost:  $" << cost << endl;


}


void findLowest(Tour *tourOptions)
{
	//Findfing the lowest cost among the array elements within tour array.

	int low = 0;
	int saveSpot;
	for (int i = 0; i < 40319; i++)
	{
		if (i == 0)
		{
			low = tourOptions[i].cost;
		}

		else
		{
			if(tourOptions[i].cost < low)
			{
				low = tourOptions[i].cost;
				cout << "New Lowest is: $" << low << endl;
				saveSpot = i;
				
			}	
		}
	}


	cout << "The tour with the lowest cost of $" << low;


}