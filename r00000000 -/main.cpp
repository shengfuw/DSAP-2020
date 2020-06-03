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
    int height = 7, width = 9;
    generateMAP(map, height ,width);
    //displayMAP(map);
    
    queue<tuple<int,int>> startPosition;
    tuple<int,int> p1(3,1);
    tuple<int,int> p2(4,1);
    tuple<int,int> p3(4,2);
    tuple<int,int> p4(3,2);
    tuple<int,int> p5(2,2);
    tuple<int,int> p6(2,3);
    tuple<int,int> p7(3,3);
    tuple<int,int> p8(4,3);
    tuple<int,int> p9(5,3);
    startPosition.push(p1);
    startPosition.push(p2);
    startPosition.push(p3);
    startPosition.push(p4);
    startPosition.push(p5);
    startPosition.push(p6);
    startPosition.push(p7);
    startPosition.push(p8);
    startPosition.push(p9);
    Snake snake(startPosition);
    

    vector<vector<int>> targets = {
        {1,3},{5,6}
    };
    int targetsCNT = int(targets.size());
    int step = 0, curEaten = 0;
    map[targets[curEaten][0]][targets[curEaten][1]] = 1;
    
    cout << "START!\n";
    displayOutcome(map, snake);
    while (step <= 50) {
        snake.nextPosition(map);
        step++;
        cout << "Step " << step << "\n";
        displayOutcome(map, snake);
        if(snake.eatenTarget == targetsCNT)
            break;
        if(snake.eatenTarget > curEaten){
            map[targets[curEaten][0]][targets[curEaten][1]] = 0;
            curEaten++;
            map[targets[curEaten][0]][targets[curEaten][1]] = 1;
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
