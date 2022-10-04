/*********************************************************************************
 * * Sean Carlyle, scarlyle
 * * 2022 Winter CSE101 PA8
 * * DictionaryTest.cpp
 * * Tests Dictionary ADT
*********************************************************************************/
#include<iostream>
#include<string>
#include<fstream>
#include"Dictionary.h"

using namespace std;

int main(void){
   Dictionary A;
   int x;
   // Test size and setValue 
   cout << A.size() << endl;
   A.setValue("hi", 1);
   A.setValue("yo", 2);
   A.setValue("hi", 3);
   A.setValue("hehe", 4);
   A.setValue("haha", 5);
   A.setValue("uuuu", 6);

   // Test assignment
   Dictionary B = A;

   // Test remove
   A.remove("yo");

   cout << A << endl;
   cout << B << endl;
   
   // Test contains, getValue, hasCurrent
   x = A.contains("hi");
   printf("%d\n", x);

   x = A.getValue("hi");
   printf("%d\n", x);

   x = A.hasCurrent();
   printf("%d\n", x);

   // Test begin, clear, end, prev, next, and equals
   A.begin();
   cout << A.currentKey() << endl;
   cout << A.currentVal() << endl;

   B.clear();
   cout << B << endl;

   A.end();
   cout << A.currentKey() << endl;
   
   A.prev();
   cout << A.currentKey() << endl;

   A.next();
   cout << A.currentKey() << endl;

   A.clear();
   
   if (A == B){
      printf("it works!");
   }  

   return 0;
}
