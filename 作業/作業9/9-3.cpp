#include <iostream>
#include <queue>
#include <fstream>
using namespace std;


struct event{
    int duration;
    int type; // 1 = Arrival, 0 = Departure
    int time;
    int ID;
    event(bool type, int time, int duration = 0, int ID = 0): type(type), time(time), duration(duration), ID(ID){ };
};

bool operator<(const event& aEvent, const event& bEvent){
    if(aEvent.time == bEvent.time){
        if(aEvent.type == bEvent.type)
            return aEvent.ID > bEvent.ID;
        return aEvent.type < bEvent.type;
    }
    return aEvent.time > bEvent.time;
}

bool operator>(const event& aEvent, const event& bEvent){
    if(aEvent.time == bEvent.time)
        if(aEvent.type == bEvent.type)
            return aEvent.ID > bEvent.ID;
        return aEvent.type > bEvent.type;
    return aEvent.time < bEvent.time;
}

struct customer{
    int waitFrom;
    int duration;
    customer(int waitFrom, int duration): waitFrom(waitFrom), duration(duration){ };
};

int main(){
    priority_queue<event> eventListPQueue;
    queue<customer> bankQueue;
    
    bool tellerAvailable = true;
    double customer_CNT = 0;
    double SUMOfWaitingTime = 0;
    int bankCustomerCnt = 0;
    
    /*
    fstream file;
    file.open("/Users/shengfu/Desktop/臺大/資料結構與進階程式設計 陳炳宇/作業/hw 09_testdata/hw9-2.samplec in");
    if(file){
        int time = 0;
        int duration = 0;
        while(file >> time){
            file >> duration;
            event newArrivalEvent(1, time, duration, customer_CNT);
            eventListPQueue.push(newArrivalEvent);
            customer_CNT++;
        }
    }
    */
    
    int time = 0;
    int duration = 0;
    while(cin >> time){
        cin >> duration;
        event newArrivalEvent(1, time, duration);
        eventListPQueue.push(newArrivalEvent);
        customer_CNT++;
    }
    
    cout << "Simulation Begins\n";
    while(!eventListPQueue.empty()){
        event newEvent = eventListPQueue.top();
        int currentTime = newEvent.time;
        
        if(newEvent.type == 1){
            cout << "Processing an arrival event at time: " << currentTime << "\n";
            eventListPQueue.pop();
            if(bankCustomerCnt < 3 && tellerAvailable){
                int departureTime = currentTime + newEvent.duration;
                event newDepartureEvent(0, departureTime);
                eventListPQueue.push(newDepartureEvent);
                if(bankCustomerCnt >= 3)
                    tellerAvailable = false;
            }
            else{
                customer newCustomer(currentTime, newEvent.duration);
                bankQueue.push(newCustomer);
            }
            bankCustomerCnt++;
        }
        else{
            cout << "Processing a departure event at time: " << currentTime << "\n";
            eventListPQueue.pop();
            bankCustomerCnt--;
            if(bankCustomerCnt >= 3){
                customer newCustomer = bankQueue.front();
                bankQueue.pop();
                int departureTime = currentTime + newCustomer.duration;
                event newDepartureEvent(0, departureTime);
                eventListPQueue.push(newDepartureEvent);
                int waitingTime = currentTime - newCustomer.waitFrom;
                SUMOfWaitingTime += waitingTime;
            }
            else
                tellerAvailable = true;
        }
    }
    cout << "Simulation Ends\n\n" << "Final Statistics:\n\n";
    cout << "\tTotal number of people processed: " << customer_CNT << "\n";
    cout << "\tAverage amount of time spent waiting: ";
    printf("%3.1f" , SUMOfWaitingTime/customer_CNT );
    cout << "\n";
}
/* Test data
 1    4: 5
 1    4: 5
 1    4: 5
 1    4: 9
 1    4: 9
 1    4: 9
 1    4: 13
 1    4: 13
 1    30: 39
 2    1: 14
 30   2: 32
 */
