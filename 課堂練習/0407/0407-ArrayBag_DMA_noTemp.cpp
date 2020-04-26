#include<iostream>
#include<string>
using namespace std;

class BagInterface{
public:
  virtual int getCurrentSize() const = 0;
  virtual bool isEmpty() const = 0;
  virtual bool add(const string& newEntry) = 0;
  virtual bool remove(const string& anEntry) = 0;
  virtual void clear() = 0;
  v8irtual int getFrequencyOf(const string& anEntry) const = 0;
  virtual bool contains(const string& anEntry) const = 0;
  virtual void print() const = 0;
};



class ArrayBag : public BagInterface{
private:
  static const int DEFAULT_CAPACITY = 6;
  string* items;
  int itemCount;
  int maxItems;
  int getIndexOf(const string& target) const;

public:
  ArrayBag();
  ~ArrayBag();
  int getCurrentSize() const;
  bool isEmpty() const;
  bool add(const string& newEntry);
  bool remove(const string& anEntry);
  void clear();
  bool contains(const string& anEntry) const;
  int getFrequencyOf(const string& anEntry) const;
  void print() const;
};

ArrayBag::ArrayBag(): itemCount(0), maxItems(DEFAULT_CAPACITY){
  items = new string[DEFAULT_CAPACITY];
}

ArrayBag::~ArrayBag(){
  delete [] items;
}

int ArrayBag::getCurrentSize() const{
  return itemCount;
}

bool ArrayBag::isEmpty() const{
  return itemCount == 0;
}

bool ArrayBag::add(const string& newEntry){
  bool hasRoomToAdd = (itemCount < maxItems);
  if(!hasRoomToAdd){
    string* oldArray = items;
    items = new string[2 * maxItems];
    for(int index = 0; index < maxItems; index++)
      items[index] = oldArray[index];
    delete [] oldArray;
    maxItems = 2 * maxItems;
  }
  items[itemCount] = newEntry;
  itemCount++;
  return true;
}
 
bool ArrayBag::remove(const string& anEntry){
  int locatedIndex = getIndexOf(anEntry);
  bool canRemoveItem = (locatedIndex > -1);
  if(canRemoveItem){
    itemCount--;
    items[locatedIndex] = items[itemCount];
  }
  return canRemoveItem;
}

void ArrayBag::clear(){
  itemCount = 0;
}

int ArrayBag::getFrequencyOf(const string& anEntry) const{
  int frequency = 0;
  int curIndex = 0;
  while(curIndex < itemCount){
    if(items[curIndex] == anEntry)
      frequency++;
    curIndex++;
  }
  return frequency;
}

bool ArrayBag::contains(const string& anEntry) const{
  return getIndexOf(anEntry) > -1;
}

void ArrayBag::print() const{
  for(int i = 0; i < itemCount; i++)
    cout << items[i] << " ";
  cout << endl;
}

int ArrayBag::getIndexOf(const string& target) const{
  bool found = false;
  int result = -1;
  int searchIndex = 0;
   
  while(!found && (searchIndex < itemCount)){
    if(items[searchIndex] == target){
      found = true;
      result = searchIndex;
    }
    else
      searchIndex++;
  }
  return result;
}


void displayBag(ArrayBag& bag){
  cout << "The bag contains " << bag.getCurrentSize()
       << " items:" << endl;

  bag.print();

  cout << endl << endl;
}

void bagTester(ArrayBag& bag){
  cout << "isEmpty: returns " << bag.isEmpty()
       << "; should be 1 (true)" << endl;
  displayBag(bag);

  string items[] = {"one", "two", "three", "four", "five", "one"};
  cout << "Add 6 items to the bag: " << endl;
  for (int i = 0; i < 6; i++){
    bag.add(items[i]);
  }
   
  displayBag(bag);
   
  cout << "isEmpty: returns " << bag.isEmpty()
       << "; should be 0 (false)" << endl;
    
  cout << "getCurrentSize: returns " << bag.getCurrentSize()
       << "; should be 6" << endl;
   
  cout << "Try to add another entry: add(\"extra\") returns "
       << bag.add("extra") << endl;
   
  cout << "contains(\"three\"): returns " << bag.contains("three")
       << "; should be 1 (true)" << endl;

  cout << "contains(\"ten\"): returns " << bag.contains("ten")
       << "; should be 0 (false)" << endl;

  cout << "getFrequencyOf(\"one\"): returns "
       << bag.getFrequencyOf("one") << " should be 2" << endl;

  cout << "remove(\"one\"): returns " << bag.remove("one")
       << "; should be 1 (true)" << endl;

  cout << "getFrequencyOf(\"one\"): returns "
       << bag.getFrequencyOf("one") << " should be 1" << endl;

  cout << "remove(\"one\"): returns " << bag.remove("one")
       << "; should be 1 (true)" << endl;

  cout << "remove(\"one\"): returns " << bag.remove("one")
       << "; should be 0 (false)" << endl;

  cout << endl;
   
  displayBag(bag);
   
  cout << "After clearing the bag, ";
  bag.clear();
   
  cout << "isEmpty: returns " << bag.isEmpty()
       << "; should be 1 (true)" << endl;
}

int main(){
  ArrayBag bag;

  cout << "Testing the Array-Based Bag:" << endl;
  cout << "The initial bag is empty." << endl;
  bagTester(bag);
  cout << "All done!" << endl;

  return 0;
}
