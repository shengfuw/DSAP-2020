#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

class Entity{
protected:
    string id;
    bool isOn;
    bool isSer; // means nothing if isOn == false
    double lon;
    double lat;
public:
    Entity(string id, bool isOn, bool isSer, double lon, double lat);
    virtual void print() = 0;
};

Entity::Entity(string id, bool isOn, bool isSer, double lon, double lat): id(id), isOn(isOn), isSer(isSer), lon(lon), lat(lat){
}


class Car : public Entity{
private:
public:
    Car(string id, bool isOn, bool isSer, double lon, double lat);
    void print();
};


Car::Car(string id, bool isOn, bool isSer, double lon, double lat): Entity(id, isOn, isSer, lon, lat){
}

void Car::print(){
    cout << this->id << ": ";
    if(this->isOn == true){
        if(this->isSer == true)
            cout << "in-service, ( ";
        else
            cout << "empty, ( ";
        cout << this->lon << " , " << this->lat << " ) ";
    }
    else
      cout << "offline";
    cout << endl;
}


class Passenger : public Entity{
private:
public:
    Passenger(string id, bool isOn, bool isSer, double lon, double lat);
    void print();
};

Passenger::Passenger(string id, bool isOn, bool isSer, double lon, double lat): Entity(id, isOn, isSer, lon, lat){
}

void Passenger::print(){
    cout << this->id << ": ";
    if(this->isOn == true){
        if(this->isSer == true)
        cout << "in-service, ( ";
      else
        cout << "waiting, ( ";
      cout << this->lon << " , " << this->lat << " ) ";
    }
    else
      cout << "offline";
    cout << endl;
}

template<typename entityType>
class EntityArray{
protected:
    int capacity;
    int cnt;
    entityType** entityPtr;
public:
    EntityArray();
    ~EntityArray();
    void add(string id, bool isOn, bool isSer, double lon, double lat) throw(overflow_error);
    void print() noexcept;
};

template<typename entityType>
EntityArray<entityType>::EntityArray() {
    cnt = 0;
    capacity = 1;
    entityPtr = new entityType*[capacity];
}

template<typename entityType>
EntityArray<entityType>::~EntityArray(){
    for(int i = 0; i < this->cnt; i++)
        delete entityPtr[i];
    delete [] entityPtr;
}


template<typename entityType>
void EntityArray<entityType>::add(string id, bool isOn, bool isSer, double lon, double lat) throw(overflow_error) {
    if(cnt < capacity){
        entityPtr[cnt] = new entityType(id, isOn, isSer, lon, lat);
        cnt++;
    }
    else
        throw overflow_error("超過容量限制");
}

template<typename entityType>
void EntityArray<entityType>::print() noexcept{
    for(int i = 0; i < cnt; i++)
        entityPtr[i]->print();
}

int main(){
    EntityArray<Car> ca;
    try{
        ca.add("5HE-313", true, true, 0, 0);
        ca.add("LPA-039", true, false, 1, 1);
    }
    catch(overflow_error e){
        cout << e.what() << endl;
    }
    ca.print();

    EntityArray<Passenger> pa;
    try{
        pa.add("B90705023", true, true, 0, 0);
        pa.add("R94725008", true, false, 1, 1);
    }
    catch(overflow_error e){
        cout << e.what() << endl;
    }
    pa.print();
    
    return 0;
}

