#include <iostream>
#include <queue>
#include <fstream>
using namespace std;


struct event{
    int type; // 1 = Arrival, 0 = Departure
    int time;
    int duration; //only for Arrival event
    char teller;//only for Departure event
    int ID;
    event(bool type, int time, int duration = 0, char teller = 0, int ID = 0): type(type), time(time), duration(duration), teller(teller), ID(ID){ };
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

void intoLine(queue<customer> &bankQueue, bool& tellerAvailable, event newEvent, int currentTime, priority_queue<event> &eventListPQueue, char teller, int& customer_CNT);
void outLine(queue<customer> &bankQueue, int currentTime, priority_queue<event> &eventListPQueue, double& SUMOfWaitingTime, bool& tellerAvailable, int& customer_CNT, char teller);

int main(){
    priority_queue<event> eventListPQueue;
    queue<customer> bankQueueA;
    queue<customer> bankQueueB;
    queue<customer> bankQueueC;
    
    bool AtellerAvailable = true;
    bool BtellerAvailable = true;
    bool CtellerAvailable = true;
    int A_customer_CNT = 0;
    int B_customer_CNT = 0;
    int C_customer_CNT = 0;
    
    double customer_CNT = 0;
    double SUMOfWaitingTime = 0;
    
    /*
    fstream file;
    file.open("/Users/shengfu/Desktop/臺大/資料結構與進階程式設計 陳炳宇/作業/hw 09_testdata/hw9-2.samplec in");
    if(file){
        int time = 0;
        int duration = 0;
        while(file >> time){
            file >> duration;
            event newArrivalEvent(1, time, duration, 0, customer_CNT);
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
    
    /*
    priority_queue<event> test = eventListPQueue;
    int n = test.size();
    for(int i = 0; i < n; i++){
        cout << test.top().time << " " << test.top().duration << "\n";
        test.pop();
    }
    */
    
    cout << "Simulation Begins\n";
    while(!eventListPQueue.empty()){
        event newEvent = eventListPQueue.top();
        int currentTime = newEvent.time;
        
        if(newEvent.type == 1){
            cout << "Processing an arrival event at time: " << currentTime << "\n";
            eventListPQueue.pop();
            
            //cout << A_customer_CNT << ", " << B_customer_CNT << ", " << C_customer_CNT << "\n";
            
            if(C_customer_CNT < A_customer_CNT && C_customer_CNT < B_customer_CNT){
                intoLine(bankQueueC, CtellerAvailable, newEvent, currentTime, eventListPQueue, 'C', C_customer_CNT);
                //cout << "C\n";
            }
            else if(B_customer_CNT < A_customer_CNT){
                intoLine(bankQueueB, BtellerAvailable, newEvent, currentTime, eventListPQueue, 'B', B_customer_CNT);
                //cout << "B\n";
            }
            else{
                intoLine(bankQueueA, AtellerAvailable, newEvent, currentTime, eventListPQueue, 'A', A_customer_CNT);
                //cout << "A\n";
            }
            
            //cout << A_customer_CNT << ", " << B_customer_CNT << ", " << C_customer_CNT << "\n---------------\n";
        }
        else{
            cout << "Processing a departure event at time: " << currentTime << "\n";
            eventListPQueue.pop();
            
            //cout << A_customer_CNT << ", " << B_customer_CNT << ", " << C_customer_CNT << "\n";
            
            char teller = newEvent.teller;
            //cout << teller << "\n";
            if(teller == 'A')
                outLine(bankQueueA, currentTime, eventListPQueue, SUMOfWaitingTime, AtellerAvailable, A_customer_CNT, 'A');
            else if(teller == 'B')
                outLine(bankQueueB, currentTime, eventListPQueue, SUMOfWaitingTime, BtellerAvailable, B_customer_CNT, 'B');
            else
                outLine(bankQueueC, currentTime, eventListPQueue, SUMOfWaitingTime, CtellerAvailable, C_customer_CNT, 'C');
            
             //cout << A_customer_CNT << ", " << B_customer_CNT << ", " << C_customer_CNT << "\n~~~~~~~~~~~~~~\n";
        }
    }
    cout << "Simulation Ends\n\nFinal Statistics:\n\n";
    cout << "\tTotal number of people processed: " << customer_CNT << "\n";
    cout << "\tAverage amount of time spent waiting: ";
    printf("%3.1f" , SUMOfWaitingTime/customer_CNT );
    cout << "\n";
}

void intoLine(queue<customer> &bankQueue, bool& tellerAvailable, event newEvent, int currentTime, priority_queue<event> &eventListPQueue, char teller, int& customer_CNT){
    if(bankQueue.empty() && tellerAvailable){
        int departureTime = currentTime + newEvent.duration;
        //cout << teller << " " << currentTime << " " << departureTime << "\n";
        event newDepartureEvent(0, departureTime, 0, teller);
        //cout << departureTime << "\n";
        eventListPQueue.push(newDepartureEvent);
        tellerAvailable = false;
    }
    else{
        //cout << newEvent.duration << "\n";
        customer newCustomer(currentTime, newEvent.duration);
        bankQueue.push(newCustomer);
    }
    customer_CNT++;
}

void outLine(queue<customer> &bankQueue, int currentTime, priority_queue<event> &eventListPQueue, double& SUMOfWaitingTime, bool& tellerAvailable, int& customer_CNT, char teller){
    if(!bankQueue.empty()){
        customer newCustomer = bankQueue.front();
        bankQueue.pop();
        int departureTime = currentTime + newCustomer.duration;
        //cout << departureTime << "\n";
        event newDepartureEvent(0, departureTime, 0, teller);
        eventListPQueue.push(newDepartureEvent);
        int waitingTime = currentTime - newCustomer.waitFrom;
        SUMOfWaitingTime += waitingTime;
    }
    else
        tellerAvailable = true;
    customer_CNT--;
}
/*
 1    4: A(5)
 1    4: B(5)
 1    4: C(5)
 1    4: A(9)
 1    4: B(9)
 1    4: C(9)
 1    4: A(13)
 1    4: B(13)
 1     30: C(39)
 2     1: A(14)
 30    2: A(32)
 */
