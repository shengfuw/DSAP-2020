#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

class PrecondViolatedExcep : public logic_error{
public:
   PrecondViolatedExcep(const string& message = "");
}; // end PrecondViolatedExcep

PrecondViolatedExcep::PrecondViolatedExcep(const string& message): logic_error("Precondition Violated Exception: " + message){
}

template<class ItemType>
class ListInterface{
public:
   /** Sees whether this list is empty.
    @return True if the list is empty; otherwise returns false. */
   virtual bool isEmpty() const = 0;
   
   /** Gets the current number of entries in this list.
    @return The integer number of entries currently in the list. */
   virtual int getLength() const = 0;
   
   /** Inserts an entry into this list at a given position.
    @pre  None.
    @post  If 1 <= position <= getLength() + 1 and the insertion is
       successful, newEntry is at the given position in the list,
       other entries are renumbered accordingly, and the returned
       value is true.
    @param newPosition  The list position at which to insert newEntry.
    @param newEntry  The entry to insert into the list.
    @return  True if insertion is successful, or false if not. */
   virtual bool insert(int newPosition, const ItemType& newEntry) = 0;
   
   /** Removes the entry at a given position from this list.
    @pre  None.
    @post  If 1 <= position <= getLength() and the removal is successful,
       the entry at the given position in the list is removed, other
       items are renumbered accordingly, and the returned value is true.
    @param position  The list position of the entry to remove.
    @return  True if removal is successful, or false if not. */
   virtual bool remove(int position) = 0;
   
   /** Removes all entries from this list.
    @post  List contains no entries and the count of items is 0. */
   virtual void clear() = 0;
   
   /** Gets the entry at the given position in this list.
    @pre  1 <= position <= getLength().
    @post  The desired entry has been returned.
    @param position  The list position of the desired entry.
    @return  The entry at the given position. */
   virtual ItemType getEntry(int position) const = 0;
   
   /** Replaces the entry at the given position in this list.
    @pre  1 <= position <= getLength().
    @post  The entry at the given position is newEntry.
    @param position  The list position of the entry to replace.
    @param newEntry  The replacement entry. */
   virtual void setEntry(int position, const ItemType& newEntry) = 0;
}; // end ListInterface

template<class ItemType>
class Node{
private:
  ItemType item;
  Node<ItemType>* next;
public:
  Node();
  Node(const ItemType& anItem);
  Node(const ItemType& anItem, Node<ItemType>* nextNodePtr);
  void setItem(const ItemType& anItem);
  void setNext(Node<ItemType>* nextNodePtr);
  ItemType getItem() const ;
  Node<ItemType>* getNext() const ;
};

template<class ItemType>
Node<ItemType>::Node() : next(nullptr){
}

template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem) : item(anItem), next(nullptr){
}

template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem, Node<ItemType>* nextNodePtr) :
                item(anItem), next(nextNodePtr){
}

template<class ItemType>
void Node<ItemType>::setItem(const ItemType& anItem){
  item = anItem;
}

template<class ItemType>
void Node<ItemType>::setNext(Node<ItemType>* nextNodePtr){
  next = nextNodePtr;
}

template<class ItemType>
ItemType Node<ItemType>::getItem() const{
  return item;
}

template<class ItemType>
Node<ItemType>* Node<ItemType>::getNext() const{
  return next;
}


template<class ItemType>
class LinkedList : public ListInterface<ItemType>{
private:
   Node<ItemType>* headPtr; // Pointer to first node in the chain;
                            // (contains the first entry in the list)
   int itemCount;           // Current count of list items
   
   // Locates a specified node in this linked list.
   // @pre  position is the number of the desired node;
   //       position >= 1 and position <= itemCount.
   // @post  The node is found and a pointer to it is returned.
   // @param position  The number of the node to locate.
   // @return  A pointer to the node at the given position.
   Node<ItemType>* getNodeAt(int position) const;

   // Adds a given node at a given position within the subchain pointed to by subChainPtr.
   // Returns a pointer to the augmented subchain.
   Node<ItemType>* insertNode(int newPosition, Node<ItemType>* newNodePtr, Node<ItemType>* subChainPtr);

public:
   LinkedList();
   LinkedList(const LinkedList<ItemType>& aList);
   virtual ~LinkedList();

   bool isEmpty() const;
   int getLength() const;
   bool insert(int newPosition, const ItemType& newEntry);
   bool remove(int position);
   void clear();
   
   /** @throw PrecondViolatedExcep if position < 1 or
                                      position > getLength(). */
   ItemType getEntry(int position) const throw(PrecondViolatedExcep);

   /** @throw PrecondViolatedExcep if position < 1 or
                                      position > getLength(). */
   void setEntry(int position, const ItemType& newEntry)
                               throw(PrecondViolatedExcep);
}; // end LinkedList

template<class ItemType>
LinkedList<ItemType>::LinkedList() : headPtr(nullptr), itemCount(0){
}  // end default constructor

template<class ItemType>
LinkedList<ItemType>::LinkedList(const LinkedList<ItemType>& alist){
    itemCount = alist->itemCount;
    Node<ItemType>* origChainPtr = alist->headPtr; // Points to nodes in original chain
     
    if(origChainPtr == nullptr)
      headPtr = nullptr;  // Original bag is empty; so is copy
    else{
      // Copy first node
      this->headPtr = new Node<ItemType>();
      this->headPtr->setItem(origChainPtr->getItem());
       
      // Copy remaining nodes
      Node<ItemType>* newChainPtr = headPtr; // Last-node pointer
      while(origChainPtr != nullptr){
        origChainPtr = origChainPtr->getNext(); // Advance pointer
          
        // Get next item from original chain
        ItemType nextItem = origChainPtr->getItem();
           
        // Create a new node containing the next item
        Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);
           
        // Link new node to end of new chain
        newChainPtr->setNext(newNodePtr);
           
        // Advance pointer to new last node
        newChainPtr = newChainPtr->getNext();
      }
        
      newChainPtr->setNext(nullptr); // Flag end of new chain
    } // end if
} // end copy constructor

template<class ItemType>
LinkedList<ItemType>::~LinkedList(){
   clear();
}  // end destructor

template<class ItemType>
bool LinkedList<ItemType>::isEmpty() const{
   return itemCount == 0;
}  // end isEmpty

template<class ItemType>
int LinkedList<ItemType>::getLength() const{
   return itemCount;
}  // end getLength

template<class ItemType>
bool LinkedList<ItemType>::insert(int newPosition, const ItemType& newEntry){
   bool ableToInsert = (newPosition >= 1) && (newPosition <= itemCount + 1);
   if (ableToInsert){
      // Create a new node containing the new entry
      Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);
      headPtr = insertNode(newPosition, newNodePtr, headPtr);
   }  // end if
   
   return ableToInsert;
}  // end insert

template<class ItemType>
bool LinkedList<ItemType>::remove(int position){
   bool ableToRemove = (position >= 1) && (position <= itemCount);
   if (ableToRemove){
      Node<ItemType>* curPtr = nullptr;
      if (position == 1){
         // Remove the first node in the chain
         curPtr = headPtr; // Save pointer to node
         headPtr = headPtr->getNext();
      }
      else{
         // Find node that is before the one to delete
         Node<ItemType>* prevPtr = getNodeAt(position - 1);
         
         // Point to node to delete
         curPtr = prevPtr->getNext();
         
         // Disconnect indicated node from chain by connecting the
         // prior node with the one after
         prevPtr->setNext(curPtr->getNext());
      }  // end if
      
      // Return node to system
      curPtr->setNext(nullptr);
      delete curPtr;
      curPtr = nullptr;
      
      itemCount--;  // Decrease count of entries
   }  // end if
   
   return ableToRemove;
}  // end remove

template<class ItemType>
void LinkedList<ItemType>::clear(){
   while (!isEmpty())
      remove(1);
}  // end clear

template<class ItemType>
ItemType LinkedList<ItemType>::getEntry(int position) const throw(PrecondViolatedExcep){
   // Enforce precondition
   bool ableToGet = (position >= 1) && (position <= itemCount);
   if (ableToGet){
      Node<ItemType>* nodePtr = getNodeAt(position);
      return nodePtr->getItem();
   }
   else{
      string message = "getEntry() called with an empty list or invalid position.";
      throw(PrecondViolatedExcep(message));
   }  // end if
}  // end getEntry

template<class ItemType>
Node<ItemType>* LinkedList<ItemType>::getNodeAt(int position) const{
   // Debugging check of precondition
   assert( (position >= 1) && (position <= itemCount) );
   
   // Count from the beginning of the chain
   Node<ItemType>* curPtr = headPtr;
   for (int skip = 1; skip < position; skip++)
      curPtr = curPtr->getNext();
      
   return curPtr;
}  // end getNodeAt

// RECURSIVE
template<class ItemType>
Node<ItemType>* LinkedList<ItemType>::insertNode(int position, Node<ItemType>* newNodePtr, Node<ItemType>* subChainPtr){
   if (position == 1){
      // Insert new node at beginning of subchain
      newNodePtr->setNext(subChainPtr);
      subChainPtr = newNodePtr;
      itemCount++;  // Increase count of entries
   }
   else{
      Node<ItemType>* afterPtr = insertNode(position - 1, newNodePtr, subChainPtr->getNext());
      subChainPtr->setNext(afterPtr);
   }  // end if
   
   return subChainPtr;
}  // end insertNode

template<class ItemType>
void LinkedList<ItemType>::setEntry(int position, const ItemType& newEntry)
throw(PrecondViolatedExcep){
    bool ableToSet = (position >= 1) && (position <= itemCount);
    if (ableToSet){
        remove(position);
        insert(position, newEntry);
    }
    else{
        string message = "setEntry() called with an empty list or invalid position.";
        throw(PrecondViolatedExcep(message));
    }  // end if
}  // end setEntry
//  End of implementation file.

int main(){
    ListInterface<string>* listPtr = new LinkedList<string>();
    string data[] = {"one", "two", "three", "four", "five", "six"};
    cout << "isEmpty: returns " << listPtr->isEmpty() << "; should be 1 (true)\n";
    for (int i = 0; i < 6; i++){
        if (listPtr->insert(i + 1, data[i]))
            cout << "Inserted " << listPtr->getEntry(i + 1) << " at position " << (i + 1) << endl;
        else
            cout << "Cannot insert " << data[i] << " at position " << (i + 1) << endl;
    }  // end for
    
    cout << "list now has " << listPtr->getLength() << " elements\n";
    cout << "position 4 now is: " << listPtr->getEntry(4) << "\n";
    listPtr->remove(4);
    cout << "After removing position 4, position 4 is: " << listPtr->getEntry(4) << "\n";
    cout << "list now has " << listPtr->getLength() << " elements\n";
    listPtr->setEntry(4, "happy");
    cout << "After SetEntity position 4, position 4 is: " << listPtr->getEntry(4) << "\n";
    for(int i = 1; i <= listPtr->getLength(); i++){
        cout << i << " is: " << listPtr->getEntry(i) << "\n";
    }
    
   return 0;
}  // end main

/*
 isEmpty: returns 1; should be 1 (true)
 Inserted one at position 1
 Inserted two at position 2
 Inserted three at position 3
 Inserted four at position 4
 Inserted five at position 5
 Cannot insert six at position 6
 list now has 5 elements
 position 4 now is: four
 After removing position 4, position 4 is: five
 list now has 4 elements
 */
