#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int DIS_INF = 1000000;

class edge{ //紀錄邊：（連結的點, 距離）
    friend class adjList;
private:
    int nodeID, weight;
public:
    edge(int nodeID, int weight);
};
//constructor
edge::edge(int nodeID, int weight):nodeID(nodeID), weight(weight){
}

class adjList{ //以adjacent list的形式紀錄圖整個圖形
private:
    int node_CNT; //點的數目
    vector<edge>* graph; //vector陣列來表示每個點的鄰接邊(edge)
public:
    adjList(int node_CNT);
    ~adjList();
    void addEdge(int nodeID, edge app);
    void distCal(int noteID, int** outcome);
};
//constructor
adjList::adjList(int node_CNT): node_CNT(node_CNT){
    graph = new vector<edge>[node_CNT+1];
}
//destructor
adjList::~adjList(){
    delete [] graph;
}
//增加邊至圖形
void adjList::addEdge(int nodeID, edge a){
    graph[nodeID].push_back(a);
}
//以某個點出發，計算所有與點與其的最小距離（利用dijkstra's algorithm）
void adjList::distCal(int traget, int** outcome){
    for(int i = 1; i <= node_CNT; i++){
        outcome[0][i] = 0;
        outcome[1][i] = DIS_INF;
    }
    outcome[0][traget] = 1;
    outcome[1][traget] = 0;
    for(int i = 0; i < graph[traget].size(); i++)
        outcome[1][graph[traget][i].nodeID] = graph[traget][i].weight;
    
    for(int n = 0; n < node_CNT - 2 ; n++){
        int miniWeight = DIS_INF, miniNode = traget;
        for(int i = 1; i < node_CNT + 1; i++){
            if(outcome[1][i] < miniWeight && outcome[0][i] != 1){
                miniWeight = outcome[1][i];
                miniNode = i;
            }
        }
        outcome[0][miniNode] = 1;
        for(int i = 0; i < graph[miniNode].size(); i++){
            if(outcome[0][graph[miniNode][i].nodeID] != 1 && graph[miniNode][i].weight + miniWeight < outcome[1][graph[miniNode][i].nodeID]){
                outcome[1][graph[miniNode][i].nodeID] = graph[miniNode][i].weight + miniWeight;
            }
        }
    }
}

int main(){
    int node_CNT = 0, edge_CNT = 0;
    string input;
    getline(cin, input, ',');
    node_CNT = stoi(input);
    getline(cin, input);
    edge_CNT = stoi(input);
    
    adjList graph(node_CNT);
       
    for(int i = 0; i < edge_CNT; i++){
        string edge_input;
        int node, nextNode, weight;
        getline(cin, edge_input, ',');
        node = stoi(edge_input);
        getline(cin, edge_input, ',');
        nextNode = stoi(edge_input);
        getline(cin, edge_input);
        weight = stoi(edge_input);
        edge a(nextNode, weight);
        graph.addEdge(node, a);
        edge b(node, weight);
        graph.addEdge(nextNode, b);
    }
       
    string target_input;
    int target = 0, minDist = 0;
    getline(cin, target_input, ',');
    target = stoi(target_input);
    getline(cin, target_input);
    minDist = stoi(target_input);
    
    int** outcome = new int*[2];
    outcome[0] = new int[node_CNT+1];
    outcome[1] = new int[node_CNT+1];
    graph.distCal(target, outcome);
    
    int count = 0;
    for(int i = 1; i <= node_CNT; i++){
        if(outcome[1][i] < minDist && outcome[1][i] != 0)
            count++;
    }
    if(count == 0)
        cout << "None";
    else{
        for(int i = 1; i <= node_CNT; i++){
            if(outcome[1][i] < minDist && outcome[1][i] != 0){
                cout << i;
                if(count != 1)
                    cout << ",";
                count--;
            }
        }
    }
    
    delete [] outcome[0];
    delete [] outcome[1];
}




