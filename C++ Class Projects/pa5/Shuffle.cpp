/*********************************************************************************
 * * Sean Carlyle, scarlyle
 * * 2022 Winter CSE101 PA5
 * * Shuffle.cpp
 * * Shuffles hands from an n card deck and displays stats about their order.
 **********************************************************************************/

#include<iostream>
#include<string>
#include <cstdlib>
#include<stdexcept>
#include"List.h"

using namespace std;

void shuffle(List& D);

// Main function that prints shuffles
int main(int argc, char * argv[]){
   
   // Exit is no argument
   if( argc != 2 ){
      cerr << "Usage: " << argv[0] << " <Maximum number of cards in a deck>" << endl;
      return(EXIT_FAILURE);
   }

   cout << "deck size       shuffle count" << endl;
   cout << "------------------------------" << endl;
  
   // Loop through the deck sizes
   // Calling shuffle until they are the same as their original
   // Print the end shuffle count
   List A;
   int n = atoi(argv[1]);
   int shufflecount = 0;
   for (int i=1; i<=n; i++){
      for(int j=0; j<i; j++){
         A.insertBefore(j);
      }
      List H = A;
      shuffle(A);
      shufflecount++;
      while (!A.equals(H)){
         shuffle(A);
         shufflecount++;
      }
      // This check is just for alignment after 10
      if (i < 10){
         cout << " " << i << "               " << shufflecount << endl;
      } else {
         cout << " " << i << "              " << shufflecount << endl;
      }
      A.clear();
      shufflecount = 0;
   }
   return 0;
}

// This function shuffles a list using the perfect shuffle
void shuffle(List& D){
   List C, B;
   int len = D.length();
   // If even
   if (len % 2 == 0){
      int halflen = len / 2;
      for (D.moveFront(); D.position() < halflen; D.moveNext()){
         C.insertBefore(D.peekNext());
      }
      for (; D.position() < D.length(); D.moveNext()){
         B.insertBefore(D.peekNext());
      }
      D.clear();
      C.moveFront();
      B.moveFront();
      for (int i=0; i < halflen; i++){
         D.insertBefore(B.peekNext());
         D.insertBefore(C.peekNext());
         B.moveNext();
         C.moveNext();
      }
   // Else odd
   } else {
      int halflen = len / 2;
      for (D.moveFront(); D.position() < halflen; D.moveNext()){
         C.insertBefore(D.peekNext());
      }
      for (; D.position() < D.length(); D.moveNext()){
         B.insertBefore(D.peekNext());
      }
      D.clear();
      C.moveFront();
      B.moveFront();
      for (int i=0; i < halflen; i++){
         D.insertBefore(B.peekNext());
         D.insertBefore(C.peekNext());
         B.moveNext();
         C.moveNext();
      }
      D.insertBefore(B.peekNext());
   }
}
