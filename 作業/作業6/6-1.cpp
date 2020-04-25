#include <iostream>
using namespace std;

const int MAX_CNT = 200;

int main(){
    int cnt = 0, upperBound = 0;
    cin >> cnt >> upperBound;
    
    double values[MAX_CNT] = {0}, weights[MAX_CNT] = {0}, CPValues[MAX_CNT] = {0}, outcome[MAX_CNT] = {0}, choiced[MAX_CNT] = {0};
    
    for(int i = 0; i < cnt; i++)
        cin >> values[i];
    
    for(int i = 0; i < cnt; i++){
        cin >> weights[i];
        CPValues[i] = values[i] / weights[i];
    }
    
    /*
    for(int i = 0; i < cnt; i++){
        cout << CPValues[i] << " ";
    }
    cout << "\n";
    */
    
    bool hasNotCheckedItem = true;
    double sumOfWeight = 0;
    int choiced_CNT = 0;

    while(hasNotCheckedItem){
        double maxCP = -1;
        int maxN = -1;
        for(int i = 0; i < cnt; i++){
            if(CPValues[i] > maxCP && (sumOfWeight + weights[i]) <= upperBound && choiced[i] == 0){
                maxCP = CPValues[i];
                maxN = i;
            }
        }
        
        if(maxCP == -1)
            hasNotCheckedItem = false;
        else{
            sumOfWeight += weights[maxN];
            choiced[maxN] = 1;
            outcome[choiced_CNT] = maxN;
            choiced_CNT++;
        }
    }
    
    //sort outcome
    for(int i = choiced_CNT - 1; i >= 0; i--){
        for(int j = 0; j < i ; j++){
            if(outcome[j] > outcome[j+1]){
                int temp = outcome[j];
                outcome[j] = outcome[j+1];
                outcome[j+1] = temp;
            }
        }
    }
    
    //print outcome
    for(int i = 0; i < choiced_CNT; i++){
        cout << outcome[i] + 1;
        if(i < choiced_CNT - 1)
            cout << ",";
        else
            cout << ";";
    }
    cout << sumOfWeight << "\n";
}
/*
8 20
10 13 8 15 24 12 10 20
3 7 5 2 6 5 10 5
 
8 20
15 20 24 10 12 7.5 8 1
2 5 6 3 5 4 5 1
 
4 6
2 2 4 6
2 3 4 5
 
7 24
7 6 5 4 3 2 1
7 6 5 4 3 2 1
*/
