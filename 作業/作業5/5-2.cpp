#include <iostream>
#include <string>
#include <cmath>
#include <stdexcept>
using namespace std;

const int MAX_ITEM_CNT = 10000;

int getItemType(string itemList[MAX_ITEM_CNT], int itemTypeList[MAX_ITEM_CNT], string itemName);

//道具
class Item{
    friend class ItemBag;
private:
    string name;
    int type;
public:
    Item(){ };
    Item(string name, int type): name(name), type(type){ };
    string getName(){ return name; };
    bool operator==(Item& object) const;
};

bool Item::operator==(Item& object) const{
    bool same = false;
    if(this->name == object.name)
        same = true;
    return same;
}

class BagInterface{
public:
    virtual void addItem(Item i) = 0;
    virtual bool hasItem(Item i) = 0;
    virtual string getItemList() = 0;
    virtual string getItemSummary() = 0;
    virtual void useItem(Item i) = 0;
    virtual void removeItem(Item i) = 0;
};

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
Node<ItemType>::Node(): next(nullptr){
}

template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem): item(anItem), next(nullptr){
}

template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem, Node<ItemType>* nextNodePtr):item(anItem), next(nextNodePtr){
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


//道具背包
class ItemBag: public BagInterface{
private:
    Node<Item>* headPtr;
    int itemCNT;
    int maxCNT;
    
    bool isEmpty() const;
    void clear();
    Node<Item>* getPointerTo(Item& object) const;
public:
    ItemBag(int maxCNT);
    //no Copy constructor: ItemBag(const ItemBag<Item>& aBag);
    virtual ~ItemBag();
    void addItem(Item object) throw(overflow_error);
    bool hasItem(Item object);
    string getItemList();
    string getItemSummary();
    void useItem(Item object) throw(logic_error);
    void removeItem(Item object) throw(logic_error);
    int getUseItemType(string name);
};

ItemBag::ItemBag(int maxCNT): headPtr(nullptr), itemCNT(0), maxCNT(maxCNT){
}

ItemBag::~ItemBag(){
    clear();
}

bool ItemBag::isEmpty() const{
    return itemCNT == 0;
}

void ItemBag::clear(){
    Node<Item>* nodeToDeletePtr = headPtr;
    while(headPtr != nullptr){
        headPtr = headPtr->getNext();
        nodeToDeletePtr->setNext(nullptr);
        delete nodeToDeletePtr;
        nodeToDeletePtr = headPtr;
    }
    itemCNT = 0;
}

Node<Item>* ItemBag::getPointerTo(Item& object) const{
    bool found = false;
    Node<Item>* curPtr = headPtr;
    
    while(!found && (curPtr != nullptr)){
        if(curPtr->getItem() == object)
            found = true;
        else
            curPtr = curPtr->getNext();
    }
    
    return curPtr;
}

void ItemBag::addItem(Item object) throw(overflow_error){
    if(itemCNT >= maxCNT)
        throw overflow_error("no more capacity\n");
    
    Node<Item>* newNodePtr = new Node<Item>();
    newNodePtr->setItem(object);
    newNodePtr->setNext(headPtr);
    headPtr = newNodePtr;
    itemCNT++;
}

bool ItemBag::hasItem(Item object){
    if(this->getPointerTo(object) == nullptr)
        return false;
    else
        return true;
}

string ItemBag::getItemList(){
    string output;
    if(this->isEmpty()){
        output = "empty\n";
        return output;
    }
    
    string List[MAX_ITEM_CNT];
    int ListCNT = 0;
    
    Node<Item>* curPtr = headPtr;
    while(curPtr != nullptr){
        List[ListCNT] = curPtr->getItem().getName();
        ListCNT++;
        curPtr = curPtr->getNext();
    }
    
    //sort
    for(int i = ListCNT - 1; i >= 0; i--){
        for(int j = 0; j < i ; j++){
            if(List[j].compare(List[j+1]) > 0){
                string temp = List[j];
                List[j] = List[j+1];
                List[j+1] = temp;
            }
        }
    }
    
    //merge
    for(int i = 0; i < ListCNT; i++){
        output += List[i];
        if(i < ListCNT - 1)
            output += ",";
    }
    output += "\n";
    return output;
}

string ItemBag::getItemSummary(){
    string output;
    if(this->isEmpty()){
        output = "empty\n";
        return output;
    }
    
    string List[MAX_ITEM_CNT];
    int ListCNT = 0;
    
    Node<Item>* curPtr = headPtr;
    while(curPtr != nullptr){
        bool repeat = false;
        for(int i = 0; i < ListCNT; i++){
            if(curPtr->getItem().getName() == List[i])
                repeat = true;
        }
        if(repeat == false){
            List[ListCNT] = curPtr->getItem().getName();
            ListCNT++;
        }
        curPtr = curPtr->getNext();
    }

    //sort
    for(int i = ListCNT - 1; i >= 0; i--){
        for(int j = 0; j < i ; j++){
            if(List[j].compare(List[j+1]) > 0){
                string temp = List[j];
                List[j] = List[j+1];
                List[j+1] = temp;
            }
        }
    }
    
    //count
    int ListCount[MAX_ITEM_CNT] = {0};
    curPtr = headPtr;
    while(curPtr != nullptr){
        for(int i = 0; i < ListCNT; i++){
            if(curPtr->getItem().getName() == List[i])
                ListCount[i]++;
        }
        curPtr = curPtr->getNext();
    }
    
    //merge
    for(int i = 0; i < ListCNT; i++){
        output += List[i];
        output += ",";
        output += to_string(ListCount[i]);
        if(ListCNT > 1 && i < ListCNT - 1)
            output += ";";
    }
    output += "\n";
    return output;
}

void ItemBag::useItem(Item object) throw(logic_error){
    Node<Item>* entryNodePtr = getPointerTo(object);
    if(entryNodePtr == nullptr)
        throw logic_error("does the character own it?\n");
    
    entryNodePtr->setItem(headPtr->getItem());
    Node<Item>* nodeToDeletePtr = headPtr;
    headPtr = headPtr->getNext();
    delete nodeToDeletePtr;
    nodeToDeletePtr = nullptr;
    itemCNT--;
}

void ItemBag::removeItem(Item object) throw(logic_error){
    Node<Item>* entryNodePtr = getPointerTo(object);
    if(entryNodePtr == nullptr)
        throw logic_error("does the character own it?\n");
    
    entryNodePtr->setItem(headPtr->getItem());
    Node<Item>* nodeToDeletePtr = headPtr;
    headPtr = headPtr->getNext();
    delete nodeToDeletePtr;
    nodeToDeletePtr = nullptr;
    itemCNT--;
}

//角色
class Character{
protected:
    static const int EXP_LV = 100;
    string name;
    int level;
    int exp;
    int power;
    int knowledge;
    int luck;
    void levelUp(int pInc, int kInc, int lInc);
    ItemBag bag;
public:
    Character(string n, int lv, int po, int kn, int lu, int bagCapacity);
    string getName() { return name; };
    virtual void beatMonster(int exp) = 0;
    virtual void print();
    void addItem(string itemName, int itemType);
    void hasItem(string itemName);
    virtual void useItem(string itemName, int itemType) = 0;
    void getItemList() { cout << bag.getItemList(); };
    void getItemSummary() { cout << bag.getItemSummary(); };
    void revomeItem(string itemName);
};

Character::Character(string n, int lv, int po, int kn, int lu, int bagCapacity): name(n), level(lv), exp(pow(lv - 1, 2) * EXP_LV), power(po), knowledge(kn), luck(lu), bag(bagCapacity){
}

void Character::print(){
    cout << name << ": Level " << level << " (" << exp << "/" << pow(this->level, 2) * EXP_LV << "), " << power << "-" << knowledge << "-" << luck << "\n";
}

void Character::levelUp(int pInc, int kInc, int lInc){
    level++;
    power += pInc;
    knowledge += kInc;
    luck += lInc;
}
void Character::addItem(string itemName, int itemType){
    Item item(itemName, itemType);
    try{
        bag.addItem(item);
    }
    catch(overflow_error e){
        cout << e.what();
    }
}

void Character::hasItem(string itemName){
    Item item(itemName, -1);
    if(bag.hasItem(item))
        cout << "yes\n";
    else
        cout << "no\n";
}

void Character::revomeItem(string itemName){
    Item item(itemName, -1);
    try{
        bag.removeItem(item);
    }
    catch(logic_error e){
        cout << e.what();
    }
}

//戰士
class Warrior : public Character{
private:
    static const int PO_LV = 10;
    static const int KN_LV = 5;
    static const int LU_LV = 5;
    static const int canUseItemType = 2;
public:
    Warrior(string n, int lv, int bagCapacity);
    void print();
    void beatMonster(int exp);
    void useItem(string itemName, int itemType);
};

Warrior::Warrior(string n, int lv, int bagCapacity): Character(n, lv, lv * PO_LV, lv * KN_LV, lv * LU_LV, bagCapacity){
}

void Warrior::print(){
  cout << "Warrior ";
  Character::print();
}

void Warrior::beatMonster(int exp){
  this->exp += exp;
  while(this->exp >= pow(level, 2) * Character::EXP_LV)
    this->levelUp(PO_LV, KN_LV, LU_LV);
}

void Warrior::useItem(string itemName, int itemType){
    Item item(itemName, -1);
    if(bag.hasItem(item) == false)
        cout << "does the character own it?\n";
    else{
        if(itemType != 1 && itemType != canUseItemType)
            cout << "cannot use it\n";
        else
            bag.useItem(item);
    }
}


//巫師
class Wizard : public Character{
private:
    static const int PO_LV = 4;
    static const int KN_LV = 9;
    static const int LU_LV = 7;
     static const int canUseItemType = 3;
public:
    Wizard(string n, int lv, int bagCapacity);
    void print();
    void beatMonster(int exp);
    void useItem(string itemName,int itemType);
};

Wizard::Wizard(string n, int lv, int bagCapacity): Character(n, lv, lv * PO_LV, lv * KN_LV, lv * LU_LV, bagCapacity){
}

void Wizard::print(){
  cout << "Wizard ";
  Character::print();
}

void Wizard::beatMonster(int exp){
  this->exp += exp;
  while(this->exp >= pow(level, 2) * Character::EXP_LV)
    this->levelUp(PO_LV, KN_LV, LU_LV);
}

void Wizard::useItem(string itemName, int itemType){
    Item item(itemName, -1);
    if(bag.hasItem(item) == false)
        cout << "does the character own it?\n";
    else{
        if(itemType != 1 && itemType != canUseItemType)
            cout << "cannot use it\n";
        else
            bag.useItem(item);
    }
}

//隊伍（角色陣列）
class Team{
private:
    int memberCNT;
    static const int capacity = 10;
    Character** members;
public:
    Team();
    int getCNT(){ return memberCNT; };
    Character& operator[](int i);
    void addWarrior(string name, int lv, int bagCapacity) throw(overflow_error);
    void addWizard(string name, int lv, int bagCapacity) throw(overflow_error);
    void memberBeatMonster(string name, int exp);
    void printMember(string name);
};

Team::Team(){
    memberCNT = 0;
    members = new Character*[capacity];
}
 
Character& Team::operator[](int i){
    return *members[i];
}

void Team::addWarrior(string name, int lv, int bagCapacity) throw(overflow_error){
    for(int i = 0; i < memberCNT; i++){
        if(members[i]->getName() == name)
            throw overflow_error("the character exists\n");
    }
    if(memberCNT < capacity){
       members[memberCNT] = new Warrior(name, lv, bagCapacity);
       memberCNT++;
    }
}

void Team::addWizard(string name, int lv, int bagCapacity) throw(overflow_error){
    for(int i = 0; i < memberCNT; i++){
        if(members[i]->getName() == name)
            throw overflow_error("the character exists\n");
    }
    
    if(memberCNT < capacity){
        members[memberCNT] = new Wizard(name, lv, bagCapacity);
        memberCNT++;
    }
}

void Team::memberBeatMonster(string name, int exp){
    for(int i = 0; i < memberCNT; i++){
        if(members[i]->getName() == name){
            members[i]->beatMonster(exp);
            break;
        }
    }
}

void Team::printMember(string name){
  for(int i = 0; i < memberCNT; i++){
    if(members[i]->getName() == name){
      members[i]->print();
      break;
    }
  }
}

int main(){
    Team characterArray;
    string itemList[MAX_ITEM_CNT];
    int itemTypeList[MAX_ITEM_CNT] = {0};
    int itemListCNT = 0;
    
    while(cin){
        char function = 0;
        cin >> function;
        switch(function){
            case 'R':{
                string name;
                int level = 0, bagCapacity = 0;
                cin >> name >> level >> bagCapacity;
                try{
                    characterArray.addWarrior(name, level, bagCapacity);
                }
                catch(overflow_error e){
                    cout << e.what();
                }
                break;
            }
            case 'D':{
                string name;
                int level = 0, bagCapacity = 0;
                cin >> name >> level >> bagCapacity;
                try{
                    characterArray.addWizard(name, level, bagCapacity);//
                }
                catch(overflow_error e){
                    cout << e.what();
                }
                break;
            }
            case 'A':{
                string characterName, itemName;
                int itemType;
                cin >> characterName >> itemName >> itemType;
                
                itemList[itemListCNT] = itemName;
                itemTypeList[itemListCNT] = itemType;
                itemListCNT++;
                
                bool hasCharacter = false;
                for(int i = 0; i < characterArray.getCNT(); i++){
                    if(characterArray[i].getName() == characterName){
                        characterArray[i].addItem(itemName, itemType);
                        hasCharacter = true;
                    }
                }
                if(!hasCharacter)
                    cout << "no such a character\n";
                break;
            }
            case 'H':{
                string characterName, itemName;
                cin >> characterName >> itemName;
                bool hasCharacter = false;
                for(int i = 0; i < characterArray.getCNT(); i++){
                    if(characterArray[i].getName() == characterName){
                        characterArray[i].hasItem(itemName);
                        hasCharacter = true;
                    }
                }
                if(!hasCharacter)
                    cout << "no such a character\n";
                break;
            }
            case 'U':{
                string characterName, itemName;
                cin >> characterName >> itemName;
                bool hasCharacter = false;
                for(int i = 0; i < characterArray.getCNT(); i++){
                    if(characterArray[i].getName() == characterName){
                        int itemType = getItemType(itemList, itemTypeList, itemName);
                        characterArray[i].useItem(itemName, itemType);
                        hasCharacter = true;
                    }
                }
                if(!hasCharacter)
                    cout << "no such a character\n";
                break;
            }
            case 'L':{
                string characterName;
                cin >> characterName;
                bool hasCharacter = false;
                for(int i = 0; i < characterArray.getCNT(); i++){
                    if(characterArray[i].getName() == characterName){
                        characterArray[i].getItemList();
                        hasCharacter = true;
                    }
                }
                if(!hasCharacter)
                    cout << "no such a character\n";
                break;
            }
            case 'S':{
                string characterName;
                cin >> characterName;
                bool hasCharacter = false;
                for(int i = 0; i < characterArray.getCNT(); i++){
                    if(characterArray[i].getName() == characterName){
                        characterArray[i].getItemSummary();
                        hasCharacter = true;
                    }
                }
                if(!hasCharacter)
                    cout << "no such a character\n";
                break;
                break;
            }
            case 'V':{
                string characterName, itemName;
                cin >> characterName >> itemName;
                bool hasCharacter = false;
                for(int i = 0; i < characterArray.getCNT(); i++){
                    if(characterArray[i].getName() == characterName){
                        characterArray[i].revomeItem(itemName);
                        hasCharacter = true;
                    }
                }
                if(!hasCharacter)
                    cout << "no such a character\n";
                break;
                break;
            }
            default:
                break;
        }
    }
}

int getItemType(string itemList[MAX_ITEM_CNT], int itemTypeList[MAX_ITEM_CNT], string itemName){
    for(int i = 0; i < MAX_ITEM_CNT; i++){
        if(itemList[i] == itemName){
            return itemTypeList[i];
            break;
        }
    }
    return 1;
}
