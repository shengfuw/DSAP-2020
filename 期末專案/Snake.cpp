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
        map[x][y] = -4; // head and body
        if(i == 0)
            map[x][y] = -2; // tail
        else if(i == 1)
            map[x][y] = -3; // next position of tail
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
    
    ////////////////////////////////
    ///start to find next position//
    ////////////////////////////////
    
    //get position of snake head
    int headX = get<0>(position.back());
    int headY = get<1>(position.back());
    int tailX = get<0>(position.front());
    int tailY = get<1>(position.front());
    //cout << headX << " " << headY << " ~\n";
    
    //up, left, down, right
    int directions[4][2] = {{-1,0}, {0,-1}, {1,0}, {0,1}};

    //calculate surrounding spaces of head and tail
    int headSurroundingSpaces = 4;
    int tailSurroundingSpaces = 4;
    for(int n = 0; n < 4; n++){
        int x = directions[n][0];
        int y = directions[n][1];
        if(map[headX+x][headY+y] == -1 || map[headX+x][headY+y] == -4)
            headSurroundingSpaces--;
        if(map[tailX+x][tailY+y] == -1 || map[tailX+x][tailY+y] == -4)
            tailSurroundingSpaces--;
    }
    
    //find which position/direction of four that head to move to
    int minDis = int(map.size()) * int(map[0].size());
    int dir = -1;
    int orientationISCorrect = 0;
    int MAXOfSurroundingSpaces = 0;
    
    for(int i = 0; i < 4; i++){
        int dirX = directions[i][0]; // up or down
        int dirY = directions[i][1]; // left or right
        int pos = map[headX+dirX][headY+dirY];
        if(pos != -1 && pos != -3 && pos != -4){ // check if head can move to this poistion
            
            //calculate distant from this poistion to the target
            int dis = abs(headX + dirX - targetX) + abs(headY + dirY - targetY);
            
            //check this position if move to counter orientation of the target
            int orientation = 1; // 1 : correct direction, 0 : counter direction
            int tarIsUP = (headX > targetX)? 1 : 0;
            int tarIsDown = (headX < targetX)? 1 : 0;
            int tarIsRight =  (headY < targetY)? 1 : 0;
            int tarIsLeft =  (headY > targetY)? 1 : 0;
            if((dirX == -1 && tarIsDown == 1) || (dirX == 1 && tarIsUP == 1) || (dirY == -1 && tarIsRight == 1) || (dirY == 1 && tarIsLeft == 1))
                orientation = 0;
            
            //calculate the number of this poistion's surrounding spaces
            int surroundingSpaces = 4;
            for(int n = 0; n < 4; n++){
                int x = directions[n][0];
                int y = directions[n][1];
                if(map[headX+dirX+x][headY+dirY+y] == -1 || map[headX+dirX+x][headY+dirY+y] == -4 || (map[headX+dirX+x][headY+dirY+y] == -3 && pos > 0))
                    surroundingSpaces--;
            }
            
            //check this poistion if casue closure
            bool isClosure = false;
            if(headSurroundingSpaces >= 2){
                int i = 0;
                bool up = false;
                while(true){
                    int nextPos = map[headX+dirX-i][headY+dirY];
                    if(nextPos == -4){
                        up = true;
                        break;
                    }
                    else if(nextPos == -1)
                        break;
                    i++;
                }
                //left
                i = 0;
                bool left = false;
                while(true){
                    int nextPos = map[headX+dirX][headY+dirY-i];
                    if(nextPos == -4){
                        left = true;
                        break;
                    }
                    else if(nextPos == -1)
                        break;
                    i++;
                }
                //down
                i = 0;
                bool down = false;
                while(true){
                    int nextPos = map[headX+dirX+i][headY+dirY];
                    if(nextPos == -4){
                        down = true;
                        break;
                    }
                    else if(nextPos == -1)
                        break;
                    i++;
                }
                //right
                i = 0;
                bool right = false;
                while(true){
                    int nextPos = map[headX+dirX][headY+dirY+i];
                    if(nextPos == -4){
                        right = true;
                        break;
                    }
                    else if(nextPos == -1)
                        break;
                    i++;
                }
                isClosure = right && up && down && left;
            }
            
            //display this position information
            //cout << headX + dirX << "," << headY + dirY << ": " << abs(headX + dirX - targetX) << " + " << abs(headY + dirY - targetY) << " = " << dis << " ; " << orientation << " " << surroundingSpaces << " " << isClosure << "\n";
            
            //compare order: distant -> surrounding space -> orientation
            bool moveToThisPosition = false;
            if((surroundingSpaces > 0 || map[headX+dirX][headY+dirY] == -2) && !isClosure){
                if(dis < minDis){
                    if(tailSurroundingSpaces != 0 || dis != 0)
                        moveToThisPosition = true;
                }
                else if(dis == minDis){
                    if(surroundingSpaces > MAXOfSurroundingSpaces)
                        moveToThisPosition = true;
                    else if(surroundingSpaces == MAXOfSurroundingSpaces && orientationISCorrect < orientation)
                        moveToThisPosition = true;
                }
            }
            if(moveToThisPosition){
                minDis = dis;
                dir = i;
                orientationISCorrect = orientation;
                MAXOfSurroundingSpaces = surroundingSpaces;
            }
        }
    }
    
    if(dir != -1){
        if(eatenTarget <= 53){ // HERE !!!!!!!!
            headX += directions[dir][0];
            headY += directions[dir][1];
        }
        
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

