#include<iostream>
#include<string>
using namespace std;

template<typename ItemType>
class BagInterface
{
public:
  virtual int getCurrentSize() const = 0;
  virtual bool isEmpty() const = 0;
  virtual bool add(const ItemType& newEntry) = 0;
  virtual bool remove(const ItemType& anEntry) = 0;
  virtual void clear() = 0;
  virtual int getFrequencyOf(const ItemType& anEntry) const = 0;
  virtual bool contains(const ItemType& anEntry) const = 0;
  virtual void print() const = 0;
};




template<typename ItemType>
class ArrayBag : public BagInterface<ItemType>
{
private:
  static const int DEFAULT_CAPACITY = 6;
  ItemType items[DEFAULT_CAPACITY];
  int itemCount;
  int maxItems;
  int getIndexOf(const ItemType& target) const;

public:
  ArrayBag();
  int getCurrentSize() const;
  bool isEmpty() const;
  bool add(const ItemType& newEntry);
  bool remove(const ItemType& anEntry);
  void clear();
  bool contains(const ItemType& anEntry) const;
  int getFrequencyOf(const ItemType& anEntry) const;
  void print() const;
};

template<typename ItemType>
ArrayBag<ItemType>::ArrayBag(): itemCount(0), maxItems(DEFAULT_CAPACITY)
{
}

template<typename ItemType>
int ArrayBag<ItemType>::getCurrentSize() const
{
  return itemCount;
}

template<typename ItemType>
bool ArrayBag<ItemType>::isEmpty() const
{
  return itemCount == 0;
}

template<typename ItemType>
bool ArrayBag<ItemType>::add(const ItemType& newEntry)
{
  bool hasRoomToAdd = (itemCount < maxItems);
  if(hasRoomToAdd)
  {
    items[itemCount] = newEntry;
    itemCount++;
  }
  return hasRoomToAdd;
}
 
template<typename ItemType>
bool ArrayBag<ItemType>::remove(const ItemType& anEntry)
{
  int locatedIndex = getIndexOf(anEntry);
  bool canRemoveItem = (locatedIndex > -1);
  if(canRemoveItem)
  {
    itemCount--;
    items[locatedIndex] = items[itemCount];
  }
  return canRemoveItem;
}

template<typename ItemType>
void ArrayBag<ItemType>::clear()
{
  itemCount = 0;
}

template<typename ItemType>
int ArrayBag<ItemType>::getFrequencyOf(const ItemType& anEntry) const
{
  int frequency = 0;
  int curIndex = 0;
  while(curIndex < itemCount)
  {
    if(items[curIndex] == anEntry)
      frequency++;
    curIndex++;
  }
  return frequency;
}

template<typename ItemType>
bool ArrayBag<ItemType>::contains(const ItemType& anEntry) const
{
  return getIndexOf(anEntry) > -1;
}

template<typename ItemType>
void ArrayBag<ItemType>::print() const
{
  for(int i = 0; i < itemCount; i++)
    cout << items[i] << " ";
  cout << endl;
}

template<typename ItemType>
int ArrayBag<ItemType>::getIndexOf(const ItemType& target) const
{
  bool found = false;
  int result = -1;
  int searchIndex = 0;
   
  while(!found && (searchIndex < itemCount))
  {
    if(items[searchIndex] == target)
    {
      found = true;
      result = searchIndex;
    }
    else
      searchIndex++;
  }
  return result;
}












void displayBag(ArrayBag<string>& bag)
{
  cout << "The bag contains " << bag.getCurrentSize()
       << " items:" << endl;

  bag.print();

  cout << endl << endl;
}

void bagTester(ArrayBag<string>& bag)
{
  cout << "isEmpty: returns " << bag.isEmpty()
       << "; should be 1 (true)" << endl;
  displayBag(bag);

  string items[] = {"one", "two", "three", "four", "five", "one"};
  cout << "Add 6 items to the bag: " << endl;
  for (int i = 0; i < 6; i++)
  {
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

int main()
{
  ArrayBag<string> bag;

  cout << "Testing the Array-Based Bag:" << endl;
  cout << "The initial bag is empty." << endl;
  bagTester(bag);
  cout << "All done!" << endl;

  return 0;
}
