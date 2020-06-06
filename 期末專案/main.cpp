#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <ctime>
#include <random>
#include <string>
#include "Snake.h"
using namespace std;

void generateMAP(vector<vector<int>>& map, int height, int width);
void displayMAP(const vector<vector<int>> map);
void displayOutcome(const vector<vector<int>> map, Snake snake);

int main(){
    vector<vector<int>> map;
    int height = 5, width = 10;
    generateMAP(map, height ,width);
    //displayMAP(map);
    
    
    //set snake start position
    vector<vector<int>> startBody = {
        {3,1},{3,2},{3,3},{2,3},{1,3},{1,2},{1,1},{2,1}
    };
    queue<tuple<int,int>> startPosition;
    for(int i = 0; i < startBody.size(); i++){
        tuple<int,int> temp(startBody[i][0],startBody[i][1]);
        startPosition.push(temp);
    }
    Snake snake(startPosition);
    
    //set targets
    vector<vector<int>> targets = {
        {2,7}
    };
    /*
    for(int i = 2; i <= 20; i++)
        targets.push_back({i,i});
    targets.push_back({1,28});
    */
    
    int targetsCNT = int(targets.size());
    int step = 0, curEaten = 0;
    map[targets[curEaten][0]][targets[curEaten][1]] = 1;
    
    cout << "START!\n";
    displayOutcome(map, snake);
    while (step <= 50) {
        snake.nextPosition(map);
        step++;
        cout << "Step " << step << ":\n";
        displayOutcome(map, snake);
        if(snake.geteatenTarget() == targetsCNT)
            break;
        if(snake.geteatenTarget() > curEaten){
            map[targets[curEaten][0]][targets[curEaten][1]] = 0;
            curEaten++;            map[targets[curEaten][0]][targets[curEaten][1]] = 1;
        }
    }
}

void generateMAP(vector<vector<int>>& map, int height, int width){
    for(int i = 0; i < height; i++){
        if(i == 0 || i == height - 1){
            vector<int> temp;
            for(int j = 0; j < width; j++)
                temp.push_back(-1);
            map.push_back(temp);
        }
        else{
            vector<int> temp;
            temp.push_back(-1);
            for(int j = 1; j < width - 1; j++)
                temp.push_back(0);
            temp.push_back(-1);
            map.push_back(temp);
        }
    }
    
    /*
    srand((unsigned)time(NULL));
    int x = rand() % (width - 2) + 1;
    int y = rand() % (height - 2) + 1;
    map[x][y] = 1;
    */
    //cout << x << " " << y << "\n-------------\n";
}

void displayMAP(const vector<vector<int>> map){
    for(int i = 0; i < map.size(); i++){
        for(int j = 0; j < map[i].size(); j++){
            cout << setw(2) << map[i][j] << " ";
        }
        cout << "\n";
    }
}

void displayOutcome(const vector<vector<int>> map, Snake snake){
    int height = int(map.size());
    int width = int(map[0].size());
    string** outcome;
    outcome = new string*[height];
    for(int i = 0; i < height; i++)
        outcome[i] = new string[width];
    
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if(map[i][j] == -1)
                outcome[i][j] = "/";
            else if(map[i][j] == 0)
                outcome[i][j] = " ";
            else
                outcome[i][j] = to_string(map[i][j]);
        }
    }
    
    //cout << "tail {";
    for(int i = 0; i < snake.getlen(); i++){
        int x = get<0>(snake.position.front());
        int y = get<1>(snake.position.front());
        snake.position.pop();
        if(i == snake.getlen() - 1)
            outcome[x][y] = "@";
        else if(i == 0)
            outcome[x][y] = "+";
        else
            outcome[x][y] = "x";
        /*
        cout << "(" << x << ", " << y << ")";
        if(i != snake.getlen() - 1){
            cout << ", ";
        }
        */
    }
    //cout << "} head\n";
    
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            cout << setw(2) << outcome[i][j] << " ";
        }
        cout << "\n";
    }
    
    cout << "---------------------------\n";
}
