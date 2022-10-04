/*********************************************************************************
 * * Sean Carlyle, scarlyle
 * * 2022 Winter CSE101 PA7
 * * Dictionary.cpp
 * * Holds Dictionary ADT
*********************************************************************************/

#include<iostream>
#include<string>
#include"Dictionary.h"
#include <climits>

// global variables
std::string s;

// Class Constructors & Destructors -------------------------------------------

// Node Constructor
Dictionary::Node::Node(keyType k, valType v){
   key = k;
   val = v;
   parent = NULL;
   left = NULL;
   right = NULL;
}

// Dictionary Constructor
Dictionary::Dictionary(){
   nil = new Node("nil", INT_MIN);
   root = nil;
   current = nil;
   num_pairs = 0;
}

// Copy Constructor
Dictionary::Dictionary(const Dictionary& D){
   nil = new Node("nil", INT_MIN);
   root = nil;
   current = nil;
   num_pairs = 0;
   preOrderCopy(D.root, D.nil);
}

// PreOrderCopy helper function
void Dictionary::preOrderCopy(Node* R, Node* N){
   if (R != N){
      setValue(R->key, R->val);
      preOrderCopy(R->left, N);
      preOrderCopy(R->right, N);
   }
   return;
}

// Dictionary Destructor
Dictionary::~Dictionary(){
   clear();
   delete nil;
   nil = NULL;
}

// PostOrdewrDelete helper function
void Dictionary::postOrderDelete(Node* R){
   if (R != nil){
      postOrderDelete(R->left);
      postOrderDelete(R->right);
      delete R;
      R = nil;
   }
}

// Access functions --------------------------------------------------------

// size() returns size of dictionary
int Dictionary::size() const{
   return (num_pairs);
}

// contains() returns true if dictionary contains key
bool Dictionary::contains(keyType k) const{
   if (num_pairs == 0){
      return false;
   }
   Node* temp = root;
   while (temp != nil){
      if (k.compare(temp->key) == 0){
         return true;
      } else if (k.compare(temp->key) < 0){
         temp = temp->left;
      } else {
         temp = temp->right;
      }     
   }
   return false;
}

// getValue() gets a value from dictionary at k key
valType& Dictionary::getValue(keyType k) const{
   if(contains(k)){
      Node* temp  = root;
      while (temp != nil){
         if (k.compare(temp->key) == 0){
            return temp->val;
         } else if (k.compare(temp->key) < 0){
            temp = temp->left;
         } else {
            temp = temp->right;
         }
      }
   }
   throw std::logic_error("Dictionary: getValue(): key does not exist");
   exit(EXIT_FAILURE);
}

// hasCurrent() returns true if current is not null
bool Dictionary::hasCurrent() const{
   if (current != nil){
      return true;
   } else {
      return false;
   }
}

// currentKey() returns the key at current
keyType Dictionary::currentKey() const{
   if (hasCurrent()){
      return current->key;
   }
   throw std::logic_error("Dictionary: currentKey(): current undefined");
   exit(EXIT_FAILURE);
}

// currentVal() returns the value at current
valType& Dictionary::currentVal() const{
   if (hasCurrent()){
      return current->val;
   }
   throw std::logic_error("Dictionary: currentVal(): current undefined");
   exit(EXIT_FAILURE);
}



// Manipulation procedures -------------------------------------------------

// clear() clears the dictionary
void Dictionary::clear(){
   if (num_pairs == 0){
      return;
   }
   postOrderDelete(root);
   root = nil;
   current = nil;
   num_pairs = 0;
}

// setValue() inserts a new value in dictionary or replaces one
void Dictionary::setValue(keyType k, valType v){
   Node *N = new Node(k, v);
   N->right = nil;
   N->left = nil;
   N->parent = nil;
   if (size() == 0){
      num_pairs++;
      root = N;
      return;
   }
   Node *P = nil;
   Node *temp;
   num_pairs++;
   temp = root;
   while (temp != nil){
      P = temp;
      if (k.compare(temp->key) == 0){
         delete N;
         N = nil;
         temp->val = v;
         num_pairs--;
         return;
      } else if (k.compare(temp->key) < 0){
         temp = temp->left;
      } else {
         temp = temp->right;
      }
   }
   N->parent = P;
   if (k.compare(P->key) < 0){
      P->left = N;
   } else {
      P->right = N;
   }  
}

// remove() removes the dictionary pair at k
void Dictionary::remove(keyType k){
   if (!contains(k)){
      throw std::logic_error("Dictionary: remove(): key does not exist");
      exit(EXIT_FAILURE);
   }
   num_pairs--;
   Node* temp = root;
   while (temp != nil){   
      if (k.compare(temp->key) == 0){
         break;
      } else if (k.compare(temp->key) < 0){
         temp = temp->left;
      } else {
         temp = temp->right;
      }
   }
   if (temp == current){
      current = nil;
   }
   if (temp->left == nil){
      transplant(temp, temp->right);
      delete temp;
   }
   else if (temp->right == nil){
      transplant(temp, temp->left);
      delete temp;
   }
   else {
      Node* y = findMin(temp->right);
      if (y->parent != temp){
         transplant(y, y->right);
         y->right = temp->right;
         y->right->parent = y;
      }
      transplant(temp, y);
      y->left = temp->left;
      y->left->parent = y;
      delete temp;
   }
   
}

// Transplant helper function to switch parent/child nodes
void Dictionary::transplant(Node* u, Node* v){
   if (u->parent == nil){
      root = v;
   }
   else if (u == u->parent->left){
      u->parent->left = v;
   }
   else {
      u->parent->right = v;
   }
   if (v != nil){
      v->parent = u->parent;
   }
}

// begin() sets current at beginning of inorder tree 
void Dictionary::begin(){
   if (num_pairs > 0){
      current = findMin(root);
   }
}

// end() sets current at end of inorder tree
void Dictionary::end(){
   if (num_pairs > 0){
      current = findMax(root);
   }
}

// next() sets current at next in inorder tree
void Dictionary::next(){
   if (hasCurrent()){
      current = findNext(current);
   } else {
      throw std::logic_error("Dictionary: next(): current not defined");
      exit(EXIT_FAILURE);
   }
}

// findNext is a helper function to find next inorder pair
Dictionary::Node* Dictionary::findNext(Node* N){
   if (N == findMax(root)){
      return nil;
   }
   if (N->right != nil){
      return findMin(N->right);
   }
   Node* temp = N->parent;
   while ((temp != nil) && (N == temp->right)){
      N = temp;
      temp = temp->parent; 
   }
   return temp;
}

// prev() sets current at prev in inorder tree
void Dictionary::prev(){
   if (hasCurrent()){
      current = findPrev(current);
   } else {
      throw std::logic_error("Dictionary: prev(): current not defined");
      exit(EXIT_FAILURE);
   }
}

// findPrev is a helper function to find the prev inorder pair
Dictionary::Node* Dictionary::findPrev(Node* N){
   if (N == findMin(root)){
      return nil;
   }
   if (N->left != nil){
      return findMax(N->left);
   }
   Node* temp = N->parent;
   while ((temp != nil) && (N == temp->left)){
      N = temp;
      temp = temp->parent;
   }
   return temp;
}


// findMin() finds the smallest value in tree
Dictionary::Node* Dictionary::findMin(Node* R){
   while(R->left != nil){
      R = R->left;
   }
   return R;
}

// findMax() finds largest value in tree
Dictionary::Node* Dictionary::findMax(Node* R){
   while(R->right != nil){
      R = R->right;
   }
   return R;
}
// Other Functions ---------------------------------------------------------

// Turns the dictionary into a string
std::string Dictionary::to_string() const{
   stringhelper(root);
   std::string temp = s;
   s.clear();
   return temp;
}

// Helper string function
void Dictionary::stringhelper(Node *root) const{
   if (root == nil){
      return; 
   }
   stringhelper(root->left);
   s += root->key+" : ";
   s += std::to_string(root->val)+"\n";
   stringhelper(root->right);  
}

// Pre-string prints out dictionary in pre-order
std::string Dictionary::pre_string() const{
   std::string prestring;
   preOrderString(prestring, root);
   return prestring;
}

// preOrderString is a helper function for pre_string
void Dictionary::preOrderString(std::string& s, Node* R) const{
   if (R != nil){
      s += R->key+"\n";
      preOrderString(s, R->left);
      preOrderString(s, R->right);
   }
}

// equals() returns true if dictionaries are equal
bool Dictionary::equals(const Dictionary& D) const{
   return equalshelper(root, D.root, D);      
}

// helper function to determine if dictionaries are equal
bool Dictionary::equalshelper(Node* roota, Node* rootb, const Dictionary& D) const{
   if (roota == nil && rootb == D.nil){
      return true;
   } else if (roota == nil && rootb != D.nil){
      return false;
   } else if (roota != nil && rootb == D.nil){
      return false;
   } else {
      if (roota->val == rootb->val && roota->key == rootb->key && equalshelper(roota->left, rootb->left, D) && equalshelper(roota->right, rootb->right, D)){
         return true;
      } else {
         return false;
      }
   }
   exit(EXIT_FAILURE);
}


// Overloaded Operators ----------------------------------------------------

// operator<<() inserts string representation of D into stream
std::ostream& operator<<( std::ostream& stream, Dictionary& D ){
   return stream << D.Dictionary::to_string();
}

// operator==() returns true if they are equal, else false
bool operator==( const Dictionary& A, const Dictionary& B ){
   return A.equals(B);
}

// operator=() overwrites state of one dictionary with another
Dictionary& Dictionary::operator=( const Dictionary& D ){
   if( this != &D ){ // not self assignment
      Dictionary temp = D;

      std::swap(nil, temp.nil);
      std::swap(num_pairs, temp.num_pairs);
      std::swap(current, temp.current);
      std::swap(root, temp.root);
   }
   return *this;
}
