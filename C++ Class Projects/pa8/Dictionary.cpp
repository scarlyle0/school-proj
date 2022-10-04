/*********************************************************************************
 * * Sean Carlyle, scarlyle
 * * 2022 Winter CSE101 PA8
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
   color = 3;
}

// Dictionary Constructor
Dictionary::Dictionary(){
   nil = new Node("nil", INT_MIN);
   nil->color = BLACK;
   root = nil;
   current = nil;
   num_pairs = 0;
   //nil->color = BLACK;
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
   throw std::logic_error("Dictionary: getValue(): key 'blah' does not exist");
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
   if (contains(k)){
      Node* temp = root;
      while (temp != nil){
         if (k.compare(temp->key) == 0){
            temp->val = v;
            return;
         } else if (k.compare(temp->key) < 0){
            temp = temp->left;
         } else {
            temp = temp->right;
         }
      }      
   }
   Node *z = new Node(k, v);
   //if (size() == 0){
   //   num_pairs++;
   //   root = z;
   //   return;
   //}
   num_pairs++;
   Node *y = nil;
   Node *x = root;
   while (x != nil){
      y = x;
      if (z->key < x->key)
         x = x->left;
      else 
         x = x->right;
   }
   z->parent = y;
   if (y == nil)
      root = z;
   else if (z->key < y->key){
      y->left = z;
   }
   else {
      y->right = z;
   }
   z->left = nil;
   z->right = nil;
   z->color = RED;
   RB_InsertFixUp(z);
}

// remove() removes the dictionary pair at k
void Dictionary::remove(keyType k){
   if (!contains(k)){
      throw std::logic_error("Dictionary: remove(): key 'blah' does not exist");
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
   RB_Delete(temp);
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
      throw std::logic_error("Dictionary: next(): current undefined");
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
      throw std::logic_error("Dictionary: prev(): current undefined");
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

// RBT Helper Functions ---------------------------------------------------

// LeftRotate()
void Dictionary::LeftRotate(Node* x){
   // set y
   Node *y = x->right;
   
   // turn y's left subtree into x's right subtree
   x->right = y->left;
   if (y->left != nil){     // not necessary if using sentinal nil node
      y->left->parent = x;
   }
   // link y's parent to x
   y->parent = x->parent;
   if (x->parent == nil){
      root = y;
   }
   else if (x == x->parent->left){
      x->parent->left = y;
   }
   else{ 
      x->parent->right = y;
   }
   // put x on y's left
   y->left = x;
   x->parent = y;
}

// RightRotate()
void Dictionary::RightRotate(Node* x){
   // set y
   Node *y = x->left;
   
   // turn y's right subtree into x's left subtree
   x->left = y->right;
   if (y->right != nil){  // not necessary if using sentinal nil node
      y->right->parent = x;
   }
   
   // link y's parent to x
   y->parent = x->parent; 
   if (x->parent == nil){
      root = y;
   }
   else if (x == x->parent->right){
      x->parent->right = y;
   }
   else{ 
      x->parent->left = y;
   }
   // put x on y's right
   y->right = x;
   x->parent = y;
}
// RB_InsertFixUP()
void Dictionary::RB_InsertFixUp(Node* z){
   Node *y;
   while (z->parent->color == RED){
      if (z->parent == z->parent->parent->left){
         y = z->parent->parent->right;
         if (y->color == RED){
            z->parent->color = BLACK;            // case 1
            y->color = BLACK;                     // case 1
            z->parent->parent->color = RED;        // case 1
            z = z->parent->parent;                 // case 1
         }
         else{
            if (z == z->parent->right){
               z = z->parent;                     // case 2
               LeftRotate(z);                 // case 2
            }
            z->parent->color = BLACK;              // case 3
            z->parent->parent->color = RED;         // case 3
            RightRotate(z->parent->parent);     // case 3   
         }
      }
      else{ 
         y = z->parent->parent->left;
         if (y->color == RED){
            z->parent->color = BLACK;              // case 4
            y->color = BLACK;                     // case 4
            z->parent->parent->color = RED;         // case 4
            z = z->parent->parent;                 // case 4
         }
         else{ 
            if (z == z->parent->left){
               z = z->parent;                     // case 5
               RightRotate(z);                // case 5
            }
            z->parent->color = BLACK;              // case 6
            z->parent->parent->color = RED;         // case 6
            LeftRotate(z->parent->parent);      // case 6
         }
      }
   }
   root->color = BLACK;
}

// RB_Transplant()
void Dictionary::RB_Transplant(Node* u, Node* v){
   if (u->parent == nil)
      root = v;
   else if (u == u->parent->left)
      u->parent->left = v;
   else 
      u->parent->right = v;
   if (v != nil)
      v->parent = u->parent;
}

// RB_DeleteFixUp()
void Dictionary::RB_DeleteFixUp(Node* x){
   std::cout << x->key << std::endl;
   Node *w;
   while (x != root and x->color == BLACK){
      if (x == x->parent->left){
         w = x->parent->right;
         if (w->color == RED){
            w->color = BLACK;                        // case 1
            x->parent->color = RED;                   // case 1
            LeftRotate(x->parent);                // case 1
            w = x->parent->right;                     // case 1
         }
         if (w->left->color == BLACK and w->right->color == BLACK){
            w->color = RED;                          // case 2
            x = x->parent;                           // case 2
         }
         else{ 
            if (w->right->color == BLACK){
               w->left->color = BLACK;                // case 3
               w->color = RED;                       // case 3
               RightRotate(w);                   // case 3
               w = w->parent->right;                  // case 3
            }
            w->color = x->parent->color;               // case 4
            x->parent->color = BLACK;                 // case 4
            w->right->color = BLACK;                  // case 4
            LeftRotate(x->parent);                // case 4
            x = root;                             // case 4
         }
      }
      else {
         w = x->parent->left;
         if (w->color == RED){
            w->color = BLACK;                        // case 5
            x->parent->color = RED;                   // case 5
            RightRotate(x->parent);               // case 5
            w = x->parent->left;                      // case 5
         }
         if (w->right->color == BLACK and w->left->color == BLACK){
            w->color = RED;                          // case 6
            x = x->parent;                           // case 6
         }
         else{ 
            if (w->left->color == BLACK){
               w->right->color = BLACK;               // case 7
               w->color = RED;                       // case 7
               LeftRotate(w);                    // case 7
               w = x->parent->left;                   // case 7
            }
            w->color = x->parent->color;               // case 8
            x->parent->color = BLACK;                 // case 8
            w->left->color = BLACK;                   // case 8
            RightRotate(x->parent);               // case 8
            x = root;                             // case 8
         }
      }
   }
   x->color = BLACK;
}

// RB_Delete()
void Dictionary::RB_Delete(Node* z){
   Node *x;
   Node *y = z;
   int y_original_color = y->color;
   if (z->left == nil){
      x = z->right;
      RB_Transplant(z, z->right);
      delete z;
   }
   else if (z->right == nil){
      x = z->left;
      RB_Transplant(z, z->left);
      delete z;
   }
   else{ 
      y = findMin(z->right);
      y_original_color = y->color;
      x = y->right;
      if (y->parent == z){
         x->parent = y;
      }
      else{
         RB_Transplant(y, y->right);
         y->right = z->right;
         y->right->parent = y;
      }
      RB_Transplant(z, y);
      y->left = z->left;
      y->left->parent = y;
      y->color = z->color;
      delete z;
   }
   if (x != nil && y_original_color == BLACK){
      RB_DeleteFixUp(x);
   }
}
