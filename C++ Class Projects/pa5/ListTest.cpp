/*********************************************************************************
 * * Sean Carlyle, scarlyle
 * * 2022 Winter CSE101 PA5
 * * ListTest.cpp
 * * Holds the testing harness for List ADT
 **********************************************************************************/
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

int main(){
    // Test insert
    List A;
    A.insertAfter(77);
    A.insertAfter(55);
    A.insertAfter(1);
    A.insertAfter(34);
    A.insertAfter(1);
    A.insertAfter(77);
    A.insertAfter(77);
    A.insertBefore(34);
    // Test Length,front,back
    cout << "A: " << A << endl;
    cout << "A.length(): " << A.length() << endl;
    cout << "A.front(): " << A.front() << endl;
    cout << "A.back(): " << A.back() << "\n" << endl;
    // Test moveFront and moveBack
    A.moveFront();
    printf("moving front\n");
    printf("moving next\n");
    A.moveNext();
    // Test peeks and clear
    cout << "A.position(): " << A.position() << endl;
    cout << "A.peekNext(): " << A.peekNext() << endl;
    cout << "A.peekPrev(): " << A.peekPrev() << "\n" << endl;
    A.clear();
    printf("clearing\n");
    cout << "A: " << A << endl;
    A.insertAfter(77);
    A.insertAfter(55);
    A.insertAfter(1);
    // Test move back and move prev
    printf("inserting num\n");
    cout << "A: " << A << endl;
    printf("moving back\n");
    printf("moving prev\n\n");
    A.moveBack();
    A.movePrev();
    cout << "A.peekNext(): " << A.peekNext() << endl;
    cout << "A.peekPrev(): " << A.peekPrev() << endl;
    A.insertAfter(2);
    A.insertBefore(5);
    printf("inserting before and after\n");
    cout << "A: " << A << endl;

    // Test setAfter and setBefore
    printf("\nSetting after to 1, before to 9\n");
    A.setAfter(1);
    A.setBefore(9);
    cout << "A: " << A << endl;
   
    // Test erases
    printf("\nErasing after and before\n");
    A.eraseAfter();
    A.eraseBefore();
    cout << "A: " << A << endl;

    // Test findNext and findPrev
    printf("\nMoving Front\n");
    printf("finding next and prev of 1 and 55");
    A.findNext(77);
    cout << "A.position(): " << A.position() << endl;
    A.findPrev(55);
    cout << "A.position(): " << A.position() << endl;

    // Test cleanup
    printf("\nInserting 2 55's and cleanup()\n");
    A.insertBefore(55);
    A.insertBefore(55);
    cout << "A: " << A << endl;
    A.cleanup();
    cout << "cleaned up A: " << A << endl;  
 
    // Test =, ==, and equals()
    List B = A;
    printf("\nCreating a List B with B = A\n"); 
    if (B.equals(A)){
       printf("equals returns equal!\n");
    }
    if (B == A){
       printf("== returns equal!\n");
    }
    // Test concat
    List J = A.concat(B);
    cout << "concated A and B: " << J << endl;
    return 0;
}
