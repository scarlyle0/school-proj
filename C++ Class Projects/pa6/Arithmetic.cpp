/*********************************************************************************
 * * Sean Carlyle, scarlyle
 * * 2022 Winter CSE101 PA6
 * * Arithmetic.cpp
 * * Does Arithmetic on big integers
*********************************************************************************/

#include<iostream>
#include<stdexcept>
#include <fstream>
#include"BigInteger.h"

#define MAX_LEN 300

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
   
   // Get lines from in
   getline(in, line);
   BigInteger A = BigInteger(line);
   getline(in, line);
   getline(in, line);
   BigInteger B = BigInteger(line);
   
   BigInteger C = BigInteger("9");
   BigInteger D = BigInteger("16");
   
   // Print out the different arithmetic
   out << A << "\n" << endl;
   out << B << "\n" << endl;
   out << A+B << "\n" << endl;
   out << A-B << "\n" << endl;
   out << A-A << "\n" << endl;
   out << (A+A+A)-(B+B) << "\n" << endl;
   out << A*B << "\n" << endl;
   BigInteger E = A*A;
   out << E << "\n" << endl;
   BigInteger F = B*B;
   out << F << "\n" << endl;
   out << C*(E*E) + D*((F*F)*B) << "\n" << endl;
   return 0;
}

