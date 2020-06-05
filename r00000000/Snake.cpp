#include "Snake.h"
#include <iostream>
#include <iomanip>
#include <cmath>

Snake::Snake(queue<tuple<int, int>> startPosition) {
    Bodylength = int(startPosition.size());
    eatenTarget = 0;
    position = startPosition;
}

queue<tuple<int, int>> Snake::nextPosition(vector<vector<int>> map) {
    
    //add snake into the map
    queue<tuple<int, int>> tempSnakeForTraversal = position;
    for(int i = 0; i < Bodylength; i++){
        int x = get<0>(tempSnakeForTraversal.front());
        int y = get<1>(tempSnakeForTraversal.front());
        tempSnakeForTraversal.pop();
        map[x][y] = -3; // head and body
        if(i == 0)
            map[x][y] = -2; // tail
    }
    
    //dispaly map
    /*
    for(int i = 0; i < map.size(); i++){
        for(int j = 0; j < map[i].size(); j++){
            cout << setw(2) << map[i][j] << " ";
        }
        cout << "\n";
    }
    */
    
    //find a target
    int targetX = 0;
    int targetY = 0;
    for(int i = 0; i < map.size(); i++){
        for(int j = 0; j < map[i].size(); j++){
            if(map[i][j] > 0){
                targetX = i;
                targetY = j;
            }
        }
    }
    //cout << targetX << " " << targetY << " :target\n";
    
    
    //start to find next position
    
    int headX = get<0>(position.back());
    int headY = get<1>(position.back());
    //cout << headX << " " << headY << " ~\n";
    
    int minDis = int(map.size()) * int(map[0].size());
    int directions[4][2] = {{-1,0}, {0,-1}, {1,0}, {0,1}};// up, left, down, right
    int dir = -1;
    int orientationISCorrect = 0;
    int spaceMAX = 0;
    
    int tailSurroundingSpaces = 4;
    for(int n = 0; n < 4; n++){
        int tailX = get<0>(position.front());
        int tailY = get<1>(position.front());
        int x = directions[n][0];
        int y = directions[n][1];
        if(map[tailX+x][tailY+y] == -1 || map[tailX+x][tailY+y] == -3)
            tailSurroundingSpaces--;
    }
    
    for(int i = 0; i < 4; i++){
        int dirX = directions[i][0];
        int dirY = directions[i][1];
        int pos = map[headX+dirX][headY+dirY];// check if can move to this poistion
        if(pos != -3 && pos != -1){
            //calculate distant from this poistion to the target
            int dis = abs(headX + dirX - targetX) + abs(headY + dirY - targetY);

            //calculate this poistion surrounding spaces
            int surroundingSpaces = 4;
            for(int n = 0; n < 4; n++){
                int x = directions[n][0];
                int y = directions[n][1];
                if(map[headX+dirX+x][headY+dirY+y] == -1 || map[headX+dirX+x][headY+dirY+y] == -3)
                    surroundingSpaces--;
            }
            
            //check this position if move to counter orientation
            int orientation = 1; //
            int tarIsUP = (headX > targetX)? 1 : 0;
            int tarIsDown = (headX < targetX)? 1 : 0;
            int tarIsRight =  (headY < targetY)? 1 : 0;
            int tarIsLeft =  (headY > targetY)? 1 : 0;
            if((dirX == -1 && tarIsDown == 1) || (dirX == 1 && tarIsUP == 1) || (dirY == -1 && tarIsRight == 1) || (dirY == 1 && tarIsLeft == 1))
                orientation = 0; // coun direction
            
            //display this position information
            //cout << headX + dirX << "," << headY + dirY << ": " << abs(headX + dirX - targetX) << " + " << abs(headY + dirY - targetY) << " = " << dis << " ; " << orientation << " " << surroundingSpaces << "\n";
            
            //compare order: distant -> surrounding space -> orientation
            bool swapPosition = false;
            if(surroundingSpaces > 0 || map[headX+dirX][headY+dirY] == -2){
                if(dis < minDis){
                    if(tailSurroundingSpaces != 0 || dis != 0) // 需要去考慮尾巴沒空間身體延長的問題嗎？
                        swapPosition = true;
                }
                else if(dis == minDis){
                    if(surroundingSpaces > spaceMAX)
                        swapPosition = true;
                    else if(surroundingSpaces == spaceMAX && orientationISCorrect < orientation)
                        swapPosition = true;
                }
            }
            if(swapPosition){
                minDis = dis;
                dir = i;
                orientationISCorrect = orientation;
                spaceMAX = surroundingSpaces;
            }
        }
    }
    
    if(dir != -1){
        headX += directions[dir][0];
        headY += directions[dir][1];
        //cout << headX << " " << headY << " !\n";
        
        tuple<int,int> head(headX, headY);
        position.push(head);
        
        if(minDis == 0){ // Eating
            Bodylength++;
            eatenTarget++;
        }
        else{ // Moving
            position.pop();
        }
    }
    
    return position;
}

int Snake::getlen(){
    return Bodylength;
}

int Snake::geteatenTarget(){
    return eatenTarget;
}

