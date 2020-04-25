#include <iostream>
#include <string>
#include <vector>
using namespace std;

void sortName(vector<string>& array);

class user{
private:
    string name;
    vector<string> tradedList;
    vector<int> scoreList;
public:
    user(string name): name(name) { };
    string getName();
    void update(string object, int score);
    void recommend();
};

string user::getName(){
    return name;
}

void user::update(string object, int score){
    tradedList.push_back(object);
    scoreList.push_back(score);
}

void user::recommend(){
    int bestScore = -1;
    for(int i = 0; i < scoreList.size(); i++){
        if(scoreList[i] > bestScore)
            bestScore = scoreList[i];
    }
    
    vector<string> outcome;
        
    for(int i = 0; i < tradedList.size(); i++){
        if(scoreList[i] == bestScore)
            outcome.push_back(tradedList[i]);
    }
        
    sortName(outcome);
    
    int n = static_cast<int>(outcome.size());
    if(static_cast<int>(outcome.size()) > 5)
       n = 5;
    for(int i = 0; i < n; i++){
        cout << outcome[i];
        if(i != n - 1)
            cout << " ";
    }
    cout << "\n";
}


class userArray{
    friend void trade(string consumer, string merchant, string product, int toM_score, int toC_score, userArray& consumers, userArray& merchants);
    friend void searchRecommend(string consumer, string product, userArray& consumers, userArray& merchants);
private:
    vector<user*> array;
public:
    userArray() { };
    //~userArray();
    void add(string name);
};

void userArray::add(string name){
    int repeated = false;
    for(int i = 0; i < array.size(); i++){
        if(array[i]->getName() == name)
            repeated = true;
    }
    if(repeated == false){
        user* userPtr = new user(name);
        array.push_back(userPtr);
    }
}

void trade(string consumer, string merchant, string product, int toM_score, int toC_score, userArray& consumers, userArray& merchants){
    for(int i = 0; i < consumers.array.size(); i++){
        if(consumers.array[i]->getName() == consumer)
            consumers.array[i]->update(merchant, toM_score);
    }
    
    for(int i = 0; i < merchants.array.size(); i++){
        if(merchants.array[i]->getName() == merchant)
            merchants.array[i]->update(consumer, toC_score);
    }
}

void searchRecommend(string consumer, string product, userArray& consumers, userArray& merchants){
    for(int i = 0; i < consumers.array.size(); i++){
        if(consumers.array[i]->getName() == consumer)
            consumers.array[i]->recommend();
    }
}


int main(){
    
    userArray consumers;
    userArray merchants;
    
    while(cin){
        char function = 0;
        cin >> function;
        switch (function) {
            case 'C':{
                string name;
                cin >> name;
                consumers.add(name);
                break;
            }
            case 'M':{
                string name;
                cin >> name;
                merchants.add(name);
                break;
            }
            case 'T':{
                string consumer, merchant, product;
                int toM_score, toC_score;
                cin >> consumer >> merchant >> product >> toM_score >> toC_score;
                trade(consumer, merchant, product, toM_score,  toC_score, consumers, merchants);
                break;
            }
            case 'S':{
                string consumer, product;
                cin >> consumer >> product;
                searchRecommend(consumer, product, consumers, merchants);
                break;
            }
            default:
                break;
        }
    }
}


void sortName(vector<string>& array){
    for(int i = static_cast<int>(array.size()) - 1; i >= 0; i--){
        for(int j = 0; j < i ; j++){
            if(array[j].compare(array[j+1]) > 0){
                string temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }
}
