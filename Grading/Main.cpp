#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <queue>
#include <tuple>
#include <vector>
#include <cmath>
#include <sstream>
#include <fstream>
#include <cstring>

#include "Snake.h"

using namespace std;

int const mapCNT = 110;

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

void loadmaps(vector<vector<int>> map[mapCNT]) {
    //    vector<vector<int>> map[mapCNT]; //maps
    fstream file;
    char buffer[250];
    string fname;
    for (int i = 1; i < mapCNT; i++) {
        if (i < 10)
            fname = "00" + to_string(i);
        else if (i < 100)
            fname = "0" + to_string(i);
        else
            fname = to_string(i);
        file.open("/Users/shengfu/Desktop/臺大/資料結構與進階程式設計 陳炳宇/資料結構與進階程式設計/Grading/map/maps/map_" + fname, ios::in);
        if (!file) {
            cout << "no file" << endl;
        }
        else {
            do {
                vector<int> tempv;
                file.getline(buffer, sizeof(buffer));
                const char* d = " ";
                char *row;
                row = strtok(buffer, d);
                while (row) {
                    string s = row;
                    int temp = stoi(s);
                    tempv.push_back(temp);
                    row = strtok(NULL, d);
                }
                map[i].push_back(tempv);
            } while (!file.eof());
        }
        file.close();
    }
}

vector<vector<int>> generate_map(vector<vector<int>> map[mapCNT], int mapindex, queue<tuple<int, int>> snake) {
    tuple<int, int> position;
    int row = 0, col = 0;
    int flag3 = 0;
    int flag5 = 0;
    //int flag7 = 0;
    int flagall = 0;

    for (int m = 0; m < 50; m++) {
        for (int n = 0; n < 50; n++) {
            if (map[mapindex][m][n] == 1) {
                row = m;
                col = n;
                position = make_tuple(m, n);
                //cout << m << " " << n << "\n";
            }
        }
    }
    
    //cout << mapindex << " #\n";

    int flag = 0;
    queue<tuple<int, int>> tempsnake = snake;
    while (!tempsnake.empty() && flag == 0) {
        if (tempsnake.front() == position) {
            flag = 1;
        }
        tempsnake.pop();
    }
    if (flag == 0){
        return map[mapindex];
    }
    else {
        for (int i = row - 1; i < row + 2; i++) {
            if (i > 0 && i < 49 && flag3 == 0) {
                for (int j = col - 1; j < col + 2; j++) {
                    if (j > 0 && j < 49 && flag3 == 0) {
                        tempsnake = snake;
                        flag = 0;
                        position = make_tuple(i, j);
                       
                        while (!tempsnake.empty() && flag == 0) {
                            if (tempsnake.front() == position) {
                                flag = 1;
                            }
                            tempsnake.pop();
                        }
                        if (flag == 0) {
                            flag3 = 1;
                            row = i;
                            col = j;
                            break;
                        }
                    }
                    if (flag3 == 1)
                        break;
                }
            }
            if (flag3 == 1) {
                break;
            }
        }
        if (flag3 == 1) {
            vector<vector<int>> newmap;
            for (int i = 0; i < 50; i++) {
                vector<int> tempv;
                for (int j = 0; j < 50; j++) {
                    if (i == 0 || i == 49) {
                        tempv.push_back(-1);
                    }
                    else {
                        if (i == row && j == col) {
                            tempv.push_back(1);
                        }
                        else if (j == 0 || j == 49)
                            tempv.push_back(-1);
                        else
                            tempv.push_back(0);
                    }
                }
                newmap.push_back(tempv);
            }
            return newmap;
        }
        else if (flag3 == 0 && flag5 == 0) {
            for (int i = row - 2; i < row + 3; i++) {
                if (i > 0 && i < 49 && flag5 == 0) {
                    for (int j = col - 2; j < col + 3; j++) {
                        if (j > 0 && j < 49 && flag5 == 0) {
                            tempsnake = snake;
                            flag = 0;
                            position = make_tuple(i, j);
                            while (!tempsnake.empty() && flag == 0) {
                                if (tempsnake.front() == position) {
                                    flag = 1;
                                }
                                tempsnake.pop();
                            }
                            if (flag == 0) {
                                flag5 = 1;
                                row = i;
                                col = j;
                                break;
                            }
                        }
                        if (flag5 == 1)
                            break;
                    }
                }
                if (flag5 == 1) {
                    break;
                }
            }
        }
        if (flag5 == 1) {
            vector<vector<int>> newmap;
            for (int i = 0; i < 50; i++) {
                vector<int> tempv;
                for (int j = 0; j < 50; j++) {
                    if (i == 0 || i == 49) {
                        tempv.push_back(-1);
                    }
                    else {
                        if (i == row && j == col) {
                            tempv.push_back(1);
                        }
                        else if (j == 0 || j == 49)
                            tempv.push_back(-1);
                        else
                            tempv.push_back(0);
                    }
                }
                newmap.push_back(tempv);
            }
            return newmap;
        }
        else if (flag3 == 0 && flag5 == 0 && flagall == 0) {
            for (int i = 0; i < 50; i++) {
                if (i > 0 && i < 49 && flagall == 0) {
                    for (int j = 0; j < 50; j++) {
                        if (j > 0 && j < 49 && flagall == 0) {
                            tempsnake = snake;
                            flag = 0;
                            position = make_tuple(i, j);
                            
                            while (!tempsnake.empty() && flag == 0) {
                                if (tempsnake.front() == position) {
                                    flag = 1;
                                }
                                tempsnake.pop();
                            }
                            if (flag == 0) {
                                flag5 = 1;
                                row = i;
                                col = j;
                                break;
                            }
                        }
                        if (flagall == 1)
                            break;
                    }
                }
                if (flagall == 1) {
                    break;
                }
            }
        }
        if (flagall == 1) {
            vector<vector<int>> newmap;
            for (int i = 0; i < 50; i++) {
                vector<int> tempv;
                for (int j = 0; j < 50; j++) {
                    if (i == 0 || i == 49) {
                        tempv.push_back(-1);
                    }
                    else {
                        if (i == row && j == col) {
                            tempv.push_back(1);
                        }
                        else if (j == 0 || j == 49)
                            tempv.push_back(-1);
                        else
                            tempv.push_back(0);
                    }
                }
                newmap.push_back(tempv);
            }
            return newmap;
        }
    }
    return map[mapindex];
}

queue<tuple<int, int>> get_start_position() {
    queue<tuple<int, int>> re;

    tuple<int, int> pos1(1, 1);
    tuple<int, int> pos2(1, 2);
    tuple<int, int> pos3(1, 3);
    tuple<int, int> pos4(1, 4);
    tuple<int, int> pos5(1, 5);

    re.push(pos1);
    re.push(pos2);
    re.push(pos3);
    re.push(pos4);
    re.push(pos5);

    return re;
}

int main() {

    queue<tuple<int, int>> ori_pos;
    queue<tuple<int, int>> new_pos = get_start_position();

    Snake snake(new_pos);

    vector<vector<int>> whole_map[mapCNT];
    loadmaps(whole_map);

    int cur_map_index = 1;
    vector<vector<int>> map = generate_map(whole_map, cur_map_index, new_pos);
    
    int step_limit = 10000;
    int point = 0;
    cout << get<0>(new_pos.back()) << ", " << get<1>(new_pos.back()) << "|" << point << "\n";

    for (int i = 0; i < step_limit; i++) {
        
        ori_pos = new_pos;
        new_pos = snake.nextPosition(map);

        //if(cur_map_index > 100)
            //displayOutcome(map, snake);
        
        int new_head_x = get<0>(new_pos.back());
        int new_head_y = get<1>(new_pos.back());
        cout << i << ": " << get<0>(new_pos.back()) << ", " << get<1>(new_pos.back()) << "|" << map[new_head_x][new_head_y] << "$" << point << "\n";

        /* Walk one step */
        int one_step_limit = 1;
        one_step_limit -= abs(get<0>(ori_pos.back()) - new_head_x);
        one_step_limit -= abs(get<1>(ori_pos.back()) - new_head_y);
        if (one_step_limit != 0) {
            cout << " A: Invalid step... " << get<0>(new_pos.back()) << ", " << get<1>(new_pos.back()) << "\n";
            //displayOutcome(map, snake);
            break;
        }

        /* Hit wall */
        if (map[new_head_x][new_head_y] == -1) {
            cout << " B: GAME OVER! Hit wall... " << get<0>(new_pos.back()) << ", " << get<1>(new_pos.back()) << "\n";
            //displayOutcome(map, snake);
            break;
        }

        /* Hit self */
        queue<tuple<int, int>> tmp_queue = new_pos;
        bool ifGameOver = false;
        for (int i = 0; i < new_pos.size() - 1; i++) {
            if (get<0>(tmp_queue.front()) == new_head_x && get<1>(tmp_queue.front()) == new_head_y) {
                cout << " C: GAME OVER! Hit yourself... " << get<0>(new_pos.back()) << ", " << get<1>(new_pos.back()) << "\n";
                //displayOutcome(map, snake);
                ifGameOver = true;
                break;
            }
            tmp_queue.pop();
        }
        if(ifGameOver)
            break;

        /* Count point and check eat longer */
        if (map[new_head_x][new_head_y] > 0) {
            if (new_pos.size() != ori_pos.size() + 1) {
                cout << " D: Invalid eat length... " << get<0>(new_pos.back()) << ", " << get<1>(new_pos.back()) << "\n";
                break;
            }
            
            point += map[new_head_x][new_head_y];
            cur_map_index++;
            if(cur_map_index > mapCNT - 1)
                break;
            map = generate_map(whole_map, cur_map_index, new_pos);
        }
        else {
            if (new_pos.size() != ori_pos.size()) {
                cout << " E: Invalid length... " << get<0>(new_pos.back()) << ", " << get<1>(new_pos.back()) << "\n";
                //displayOutcome(map, snake);
                break;
            }
        }
    }
    cout << " | Final: " << get<0>(new_pos.back()) << ", " << get<1>(new_pos.back()) << " $ " << point << " (" << cur_map_index - 1 << " / " << mapCNT - 1 << " maps);\n";

    //system("pause");
    return 0;
}
