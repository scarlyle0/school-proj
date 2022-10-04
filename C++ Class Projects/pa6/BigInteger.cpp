/*********************************************************************************
 * * Sean Carlyle, scarlyle
 * * 2022 Winter CSE101 PA6
 * * BigInteger.cpp
 * * BigInteger ADT
*********************************************************************************/

#include<iostream>
#include<string>
#include<stdexcept>
#include<algorithm>
#include"List.h"
#include"BigInteger.h"
#include <cstring>

void negateList(List& L);
void sumList(List& S, List A, List B, int sgn);
int normalizeList(List& L);
void shiftList(List& L, int p);
void scalarMultList(List& L, ListElement m);

long base = 1000000000;

long power = 9;

// BigInteger()
// Constructor that creates a new BigInteger in the zero state: 
// signum=0, digits=().
BigInteger::BigInteger(){
   signum = 0;
}


// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s){
   if (s.length() == 0){
      throw std::invalid_argument("BigInteger: Constructor: empty string");
      exit(EXIT_FAILURE);
   }
   signum = 0;
   std::string temp;
   int strsize = s.length();
   // Remove + or -
   if (s[0] == 45){
      signum = -1;
      for (int k = 1; k < strsize; k++){
         temp += s[k];
      }
      s = temp;
      temp.clear();
      strsize--;
   if (s[0] == 43){
      signum = 1;
      for (int k = 1; k < strsize; k++){
         temp += s[k];
      }
      s = temp;
      temp.clear();
      strsize--;
   }
   } else {
      signum = 1;
   }
   //if(!(s.find_first_not_of("0123456789") == std::string::npos)){
   //   throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
   //   exit(EXIT_FAILURE);
   //}
   //Change string to int and enter
   reverse(s.begin(),s.end());
   for (int i = 0; i < strsize; i++) {
      temp += s[i];
      if (((i + 1) % power) == 0){
         reverse(temp.begin(), temp.end());
         digits.insertAfter(std::stoi(temp));
         temp.clear();
      }
   }
   if (strsize % power != 0){
      reverse(temp.begin(), temp.end());
      digits.insertAfter(std::stoi(temp)); 
      temp.clear();
   }
   normalizeList(digits);
}


// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N){
   signum = N.signum;
   digits = N.digits;
}


// OPTIONAL DECONSTRUCTOR;

// Access functions --------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive, 
// negative or 0, respectively.
int BigInteger::sign() const{
   return(signum);
}


// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const{
   BigInteger A;
   A.digits = digits;
   A.signum = signum;
   // Use subtraction / knowing signs to compare
   if (signum == -1 && N.signum == 1){
      return -1;
   } else if (signum == 1 && N.signum == -1){
      return 1;
   } else if (signum == 1 && N.signum == 1){
      A = A.sub(N);
   } else if (signum == -1 && N.signum == -1){     
     BigInteger L = N;
     negateList(L.digits);
     A = A.add(L);
   }
   if (A.signum == 0){
      return 0;
   }
   if (A.signum == -1){
      return -1;
   } else {
      return 1;
   }
   
}

// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero(){
   List L;
   signum = 0;
   digits = L;
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::negate(){
   if (signum != 0){
      signum = -signum;
   }
}

// BigInteger Arithmetic operations ----------------------------------------

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const{
   List L;
   BigInteger A;
   L = digits;
   if (signum == -1){
      negateList(L);
   }
   sumList(L, L, N.digits, N.signum);
   A.signum = normalizeList(L);
   A.digits = L;
   return A;
}


// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const{
   List L;
   BigInteger A;
   L = digits;
   if (signum == -1){
      negateList(L);
   }
   sumList(L, L, N.digits, -N.signum);
   A.signum = normalizeList(L);
   A.digits = L;
   return A;
}


// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const{
   BigInteger P;
   List L = digits;
   List X = N.digits;
   BigInteger A;
   A.signum = 1;
   long num = 0;
   int counter = 0;
   for (X.moveBack(); X.position() > 0; X.movePrev()){
      L = digits;
      num = X.peekPrev();
      shiftList(L, counter);
      scalarMultList(L, num);
      A.digits = L;
      P = P.add(A);
      counter++;
   }
   if ((signum == 1 && N.signum == -1) || (signum == -1 && N.signum == 1)){
      P.signum = -1;
   } 
   return P;
}


// Other Functions ---------------------------------------------------------


// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string(){
   std::string s;
   if (signum == -1){
      s += "-";
   }
   bool first = true;
   for (digits.moveFront(); digits.position() < digits.length(); digits.moveNext()){
      if (digits.peekNext() == 0 && digits.length() == 1){
         s += "0";
         return s;
      }
      if (digits.peekNext() == 0){
         for (int i = 0; i < power; i++){
            s += std::to_string(digits.peekNext());
         }
      } else if (!first && digits.peekNext() < (base / 10)){
         long n = digits.peekNext();
         int counter = 0;
         while (n != 0){
            counter++;
            n = n / 10;
         }
         for (int i = 0; i < (power - counter); i++){
            s += "0";
         }
         s += std::to_string(digits.peekNext());
      } else {
         s += std::to_string(digits.peekNext());
      }
      first = false;
   }
   return s;
}

// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ){
   return stream << N.BigInteger::to_string();
}

// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ){
   int x = A.compare(B);
   if (x == 0){
      return true;
   } else {
      return false;
   }
}

// operator<()
// Returns true if and only if A is less than B.
bool operator<( const BigInteger& A, const BigInteger& B ){
   int x = A.compare(B);
   if (x == -1){
      return true;
   } else {
      return false;
   }
}


// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ){
   int x = A.compare(B);
   if (x == -1 || x == 0){
      return true;
   } else {
      return false;
   }
}


// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ){
   int x = A.compare(B);
   if (x == 1){
      return true;
   } else {
      return false;
   }
}


// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ){
   int x = A.compare(B);
   if (x == 1 || x == 0){
      return true;
   } else {
      return false;
   }
}

// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ){
   BigInteger C;
   C = A.add(B);
   return C;
}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ){
   A = A.add(B);
   return A;
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ){
   BigInteger C;
   C = A.sub(B);
   return C;
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ){
   A = A.sub(B);
   return A;
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ){
   BigInteger C;
   C = A.mult(B);
   return C;
}
 
// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ){
   A = A.mult(B);
   return A;
}

// List Functions ----------------------------------------------------------

// negateList()
// Changes the sign of each integer in List L. Used by sub().
void negateList(List& L){
   for (L.moveFront(); L.position() < L.length(); L.moveNext()){
      long temp;
      temp = L.peekNext();
      temp = -temp;
      L.setAfter(temp);
   }
}

// sumList()
// Overwrites the state of S with A + sgn*B (considered as vectors).
// Used by both sum() and sub().
void sumList(List& S, List A, List B, int sgn){
   if (sgn == -1){
      negateList(B);
   }
   bool asmall = false;
   List C, D;
   if (A.length() < B.length()){
      S = B;
      asmall = true;
   } else {
      S = A;  
   }
   if (asmall){
      S.moveBack();
      for (A.moveBack(); A.position() > 0; A.movePrev()){
         S.setBefore(S.peekPrev() + A.peekPrev());
         S.movePrev();
      }
   } else {
      S.moveBack();
      for (B.moveBack(); B.position() > 0; B.movePrev()){
         S.setBefore(S.peekPrev() + B.peekPrev());
         S.movePrev();
      }
   }
}

// normalizeList()
// Performs carries from right to left (least to most significant
// digits), then returns the sign of the resulting integer. Used
// by add(), sub() and mult().
int normalizeList(List& L){
   bool onepositive = false;
   bool firstnegative = false;
   bool first = false;
   bool allzeros = true;
   for (L.moveFront(); L.position() < L.length(); L.moveNext()){
      if (first == false){
         if (L.peekNext() < 0){
            firstnegative = true;
         }
         first = true;
      }
      if (L.peekNext() > 0){
         onepositive = true;
      }
      if (L.peekNext() != 0){
         allzeros = false;
      }               
   }
   if (allzeros){
      L.moveFront();
      while (L.length() > 1 && L.peekNext() == 0){
         L.eraseAfter();
      }
      return 0;
   }
   // All negative
   if (!onepositive){
      L.moveFront();
      while (L.peekNext() == 0){
         L.eraseAfter();
      }
      negateList(L);
      return -1;
   }
   // First negative some positive
   if (firstnegative){
      long carry = 0;
      long nextcarry = 0;
      long temp = 0;
      for (L.moveBack(); L.position() > 0; L.movePrev()){
         carry = nextcarry;
         temp = L.peekPrev();
         if (temp <= 0){
            nextcarry = 0;
            temp = temp + carry;
            L.setBefore(temp);
         }
         if (temp > 0){
            nextcarry = 1;
            temp = temp - base + carry;
            L.setBefore(temp);
         }
      }
      // get rid of any leading 0's
      L.moveFront();
      if (L.peekNext() == 0){
         L.eraseAfter();
      }
      negateList(L);
      return -1;
   }
   // Positive / Some negative but not first
   long temp = 0;
   long carry = 0;
   long nextcarry = 0;
   long digitsnum = 0;
   long n = 0;
   for (L.moveBack(); L.position() > 0; L.movePrev()){
      carry = nextcarry;
      temp = L.peekPrev();
      n = temp;
      while (n != 0){
         n = n / 10;
         digitsnum++;
      }
      if (temp < 0){
         nextcarry = -1;
         temp = base + temp + carry;
         L.setBefore(temp);
      } else if (digitsnum > power){
         temp = temp + carry;
         long carrycounter = temp / base;
         nextcarry = carrycounter;
         temp = temp - (base*carrycounter);
         L.setBefore(temp);
         if (L.position() == 1){
            L.movePrev();
            L.insertBefore(nextcarry);
         }
      } else {
         nextcarry = 0;
         temp = temp + carry;
         L.setBefore(temp);
      }
      digitsnum = 0;
   }
   // Remove 0's infront of List
   L.moveFront();
   if (L.peekNext() == 0){
      while (L.length() > 1 && L.peekNext() == 0){
         L.eraseAfter();
      }
   }
   return 1;
}

// shiftList()
// Prepends p zero digits to L, multiplying L by base^p. Used by mult().
void shiftList(List& L, int p){
   for (int i = 0; i < p; i++){
      L.moveBack();
      L.insertAfter(0);
   }
}

// scalarMultList()
// Multiplies L (considered as a vector) by m. Used by mult().
void scalarMultList(List& L, ListElement m){
   long temp;
   for (L.moveBack(); L.position() > 0; L.movePrev()){
      temp = L.peekPrev();
      L.setBefore(m*temp);
   }
}
