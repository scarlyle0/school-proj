/*********************************************************************************
 * * Sean Carlyle, scarlyle
 * * 2022 Winter CSE101 PA5
 * * List.cpp
 * * Holds the List ADT
*********************************************************************************/
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

// Node constructor
List::Node::Node(ListElement x){
   data = x;
   next = nullptr;
   prev = nullptr;
}


// Class Constructors & Destructors -------------------------------------------

// Creates a new List in the empty state.
List::List(){
   frontDummy = new Node(999);
   backDummy = new Node(999);;
   frontDummy->next = backDummy;
   backDummy->prev = frontDummy;
   beforeCursor = frontDummy;
   afterCursor = backDummy;
   pos_cursor = 0;
   num_elements = 0;
}

// Copy Constructor.
List::List(const List& L){
   frontDummy = new Node(999);
   backDummy = new Node(999);;
   frontDummy->next = backDummy;
   backDummy->prev = frontDummy;
   beforeCursor = frontDummy;
   afterCursor = backDummy;
   pos_cursor = 0;
   num_elements = 0;

   Node* N = L.frontDummy->next;
   while( N!= L.backDummy ){
      this->insertBefore(N->data);
      N = N->next;
   }
}

// Destructor
List::~List(){
   while( num_elements>0 ){
      moveFront();
      eraseAfter();
   }
   delete frontDummy;
   delete backDummy;
}

// Access functions --------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const{
   return(num_elements);
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const{
   if(length()>0){
      return(frontDummy->next->data);
   }
   throw std::length_error("List: front(): empty list");
   exit(EXIT_FAILURE);
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const{
   if(length()>0){
      return(backDummy->prev->data);
   }
   throw std::length_error("List: back(): empty list");
   exit(EXIT_FAILURE);
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const{
   if (0 <= pos_cursor && pos_cursor <= length()){
      return(pos_cursor);
   }
   throw std::range_error("List: position(): cursor past front or back");
   exit(EXIT_FAILURE);
}


// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const{
   if (position() < length()){
      return(afterCursor->data);
   }
   throw std::range_error("List: peekNext(): cursor at back");
   exit(EXIT_FAILURE);
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const{
   if (position() > 0){
      return(beforeCursor->data);
   }
   throw std::range_error("List: peekPrev(): cursor at front");
   exit(EXIT_FAILURE);
}

// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state
void List::clear(){
   while( num_elements>0 ){
      moveFront();
      eraseAfter();
   }
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront(){
   pos_cursor = 0;
   afterCursor = frontDummy->next;
   beforeCursor = frontDummy;
}


// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack(){
   pos_cursor = length();  
   beforeCursor = backDummy->prev;
   afterCursor = backDummy;
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position()<length() 
ListElement List::moveNext(){
   if (position() < length()){
      pos_cursor++;
      beforeCursor = beforeCursor->next;
      afterCursor = afterCursor->next;
      return(beforeCursor->data);
   }
   throw std::range_error("List: moveNext(): cursor at back");
   exit(EXIT_FAILURE);
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0
ListElement List::movePrev(){
   if (position() > 0){
      pos_cursor--;
      beforeCursor = beforeCursor->prev;
      afterCursor = afterCursor->prev;
      return(afterCursor->data);
   }
   throw std::range_error("List: movePrev(): cursor at front");
   exit(EXIT_FAILURE);
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x){
   Node* N = new Node(x);
   afterCursor->prev = N;
   beforeCursor->next = N;
   N->next = afterCursor;
   N->prev = beforeCursor;
   afterCursor = N;
   num_elements++;
}


// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x){
   Node* N = new Node(x);
   afterCursor->prev = N;
   beforeCursor->next = N;
   N->next = afterCursor;
   N->prev = beforeCursor;
   beforeCursor = N;
   num_elements++;
   pos_cursor++;
}


// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x){
   if (position() < length()){
      afterCursor->data = x;
      return;
   }
   throw std::range_error("List: setAfter(): cursor at back");
   exit(EXIT_FAILURE);
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x){
   if (position() > 0){
      beforeCursor->data = x;
      return;
   }
   throw std::range_error("List: setBefore(): cursor at front");
   exit(EXIT_FAILURE);
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter(){
   if (position() < length()){
      num_elements--;
      afterCursor = afterCursor->next;
      delete afterCursor->prev;
      afterCursor->prev = beforeCursor;
      beforeCursor->next = afterCursor;
      return;
   }
   throw std::range_error("List: eraseAfter(): cursor at back");
   exit(EXIT_FAILURE);
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore(){
   if (position() > 0){
      num_elements--;
      pos_cursor--;
      beforeCursor = beforeCursor->prev;
      delete beforeCursor->next;
      beforeCursor->next = afterCursor;
      afterCursor->prev = beforeCursor;
      return;     
   }
   throw std::range_error("List: eraseBefore(): cursor at front");
   exit(EXIT_FAILURE);
}

// Other Functions ---------------------------------------------------------

// findNext() 
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then 
// returns the final cursor position. If x is not found, places the cursor 
// at position length(), and returns -1. 
int List::findNext(ListElement x){
   for (; position() < length(); moveNext()){
      if (x == peekNext()){
         moveNext();
         return(position());
      }
   }
   moveBack();
   return (-1);
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor 
// at position 0, and returns -1. 
int List::findPrev(ListElement x){
   for (; position() > 0; movePrev()){
      if (x == peekPrev()){
         movePrev();
         return(position());
      }
   }
   moveFront();
   return (-1);
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.
void List::cleanup(){
   bool isin = false;
   int temppos = position();
   List C;
   for (moveFront(); position() < length(); moveNext()){
      isin = false;
      for (C.moveFront(); C.position() < C.length(); C.moveNext()){
         //printf("peekNext: %d\n", peekNext());
         //printf("C.peekNExt: %d\n", C.peekNext());
         if (peekNext() == C.peekNext()){
            if (position() < temppos){
               //printf("yo\n");
               temppos--;
            }
            isin = true;
            eraseAfter();
            movePrev();
            break;
         }
      }
      if (isin == false){
         C.insertBefore(peekNext());
      }
   }
   moveFront();  
   for (; temppos > 0; temppos--){
      moveNext();
   }
}

// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const{
   List J;
   Node* N = this->frontDummy->next;
   Node* M = L.frontDummy->next;
   //printf("yo\n");
   while( N!=this->backDummy ){
      J.insertBefore(N->data);
      N = N->next;
   }
   while( M!=L.backDummy ){
      J.insertBefore(M->data);
      M = M->next;
   }
   J.moveFront();
   return J;
}


// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const{
   Node* N = nullptr;
   std::string s = "(";
   int counter = 0;

   for(N=frontDummy->next; N!=backDummy; N=N->next){
      counter++;
      if (counter != length()){  
         s += std::to_string(N->data)+", ";
      } else {
         s += std::to_string(N->data);
      }
   }
   s += ")";
   return s;
}


// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const{
   bool eq = false;
   Node* N = nullptr;
   Node* M = nullptr;

   eq = ( this->num_elements == R.length() );
   N = this->frontDummy;
   M = R.frontDummy;
   while( eq && N!=nullptr){
      eq = (N->data==M->data);
      N = N->next;
      M = M->next;
   }
   return eq;
}

// Other Functions ------------------------------------------------------------

// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<< ( std::ostream& stream,  const List& L ) {
   return stream << L.List::to_string();
}


// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged.
bool operator== (const List& A, const List& B){
   return A.List::equals(B);
}


// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ) {
   if( this != &L ){ // not self assignment
      List temp = L;

      std::swap(frontDummy, temp.frontDummy);
      std::swap(backDummy, temp.backDummy);
      std::swap(beforeCursor, temp.beforeCursor);
      std::swap(afterCursor, temp.afterCursor);
      std::swap(pos_cursor, temp.pos_cursor);
      std::swap(num_elements, temp.num_elements);
   }
   return *this;
}
