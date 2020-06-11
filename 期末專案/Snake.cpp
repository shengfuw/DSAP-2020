#include "Snake.h"
#include <cmath>
#include <string>
#include <iomanip>
#include <iostream>

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
    
    ////////////////////////////////
    ///start to find next position//
    ////////////////////////////////
    
    //get position of snake head
    int headX = get<0>(position.back());
    int headY = get<1>(position.back());
    int tailX = get<0>(position.front());
    int tailY = get<1>(position.front());
    //cout << headX << " " << headY << " ~\n";
    
    //find a target
    int targetX = 0, targetY = 0, MAXscore = 0, minDisTarget = 0;
    for(int i = 0; i < map.size(); i++){
        for(int j = 0; j < map[i].size(); j++){
            int dis = abs(headX - map[i][j]) + abs(headY - map[i][j]);
            if(map[i][j] > MAXscore || (map[i][j] == MAXscore &&  dis < minDisTarget)){
                targetX = i;
                targetY = j;
                MAXscore = map[i][j];
                minDisTarget = dis;
            }
        }
    }
    //cout << targetX << " " << targetY << " :target\n";
    
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
    
    for(int diri = 0; diri < 4; diri++){
        int dirX = directions[diri][0]; // up or down
        int dirY = directions[diri][1]; // left or right
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

            //display(map);
            
            //check this poistion if casue closure
            bool isClosure = true;
            for(int i = 0 ; i < 4; i++){
                int x1 = directions[i][0], y1 = directions[i][1];
                int a = 1;
                //level 1
                while (isClosure) {
                    int nextPos = map[headX+dirX+(x1*a)][headY+dirY+(y1*a)];
                    
                    //level 2
                    if(nextPos == -4){
                        if(a > 1){
                            for(int j = 0; j < 4; j++){
                                int x2 = directions[j][0], y2 = directions[j][1];
                                int b = 1;
                                while (isClosure) {
                                    int nextPos2 = map[headX+dirX+(x1*(a-1))+(x2*b)][headY+dirY+(y1*(a-1))+(y2*b)];
                                    
                                    //level 3
                                    if(nextPos2 == -4){
                                        if(b > 1){
                                            for(int k = 0; k < 4; k++){
                                                int x3 = directions[k][0], y3 = directions[k][1], c = 1;
                                                while (isClosure) {
                                                    int nextPos3 = map[headX+dirX+(x1*(a-1))+(x2*(b-1))+(x3*c)][headY+dirY+(y1*(a-1))+(y2*(b-1))+(y3*c)];
                                                    
                                                    //levle 4
                                                    if(nextPos3 == -4){
                                                        if(c > 1){
                                                            for(int l = 0; l < 4; l++){
                                                                int x4 = directions[l][0], y4 = directions[l][1], d = 1;
                                                                while (isClosure) {
                                                                    int nextPos4 = map[headX+dirX+(x1*(a-1))+(x2*(b-1))+(x3*(c-1))+(x4*d)][headY+dirY+(y1*(a-1))+(y2*(b-1))+(y3*(c-1))+(y4*d)];

                                                                    if(nextPos4 == -4){
                                                                        break;
                                                                    }
                                                                    else if (nextPos4 == -1){
                                                                        isClosure = false;
                                                                        break;
                                                                    }
                                                                    d++;
                                                                }
                                                            }
                                                        }
                                                        break;
                                                    }
                                                    
                                                    else if (nextPos3 == -1){
                                                        isClosure = false;
                                                        break;
                                                    }
                                                    c++;
                                                }
                                            }
                                        }
                                        break;
                                    }
                                    else if(nextPos2 == -1){
                                        isClosure = false;
                                        break;
                                    }
                                    b++;
                                }
                            }
                        }
                        break;
                    }
                    else if(nextPos == -1){
                        isClosure = false;
                        break;
                    }
                    a++;
                }
            }

            //if(isClosure)
                //display(map);
            
            //display this position information
            //cout << dirX << " " << dirY << ". " << headX + dirX << "," << headY + dirY << ": " << abs(headX + dirX - targetX) << " + " << abs(headY + dirY - targetY) << " = " << dis << " ; " << orientation << " " << surroundingSpaces << " " << isClosure << "\n";
            
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
                dir = diri;
                orientationISCorrect = orientation;
                MAXOfSurroundingSpaces = surroundingSpaces;
            }
        }
    }
    
    if(dir != -1){
        headX += directions[dir][0];
        headY += directions[dir][1];
        
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

void Snake::display(vector<vector<int>> map){
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
    
    Snake tempSnake = *this;
    
    //cout << "tail {";
    for(int i = 0; i < tempSnake.getlen(); i++){
        int x = get<0>(tempSnake.position.front());
        int y = get<1>(tempSnake.position.front());
        tempSnake.position.pop();
        if(i == getlen() - 1)
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
