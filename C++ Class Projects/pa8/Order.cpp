/*********************************************************************************
 * * Sean Carlyle, scarlyle
 * * 2022 Winter CSE101 PA8
 * * Order.cpp
 * * Prints out infile in two different BST orders
*********************************************************************************/
#include<iostream>
#include<string>
#include <fstream>
#include"Dictionary.h"

using namespace std;

int main(int argc, char * argv[]){

   ifstream in;
   ofstream out;
   string line;
   // Read in command line arguments
   if( argc != 3 ){
      cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
      return(EXIT_FAILURE);
   }

   // Open files
   in.open(argv[1]);
   if( !in.is_open() ){
      cerr << "Unable to open file " << argv[1] << " for reading" << endl;
      return(EXIT_FAILURE);
   }

   out.open(argv[2]);
   if( !out.is_open() ){
      cerr << "Unable to open file " << argv[2] << " for writing" << endl;
      return(EXIT_FAILURE);
   }

   // Place inside dictionary and print out in two different orders
   Dictionary A;
   int counter = 0;
   while(getline(in, line)){
      counter++;
      A.setValue(line, counter);
   }
   out << A << endl;
   
   out << A.pre_string() << endl;

    return 0;
}
