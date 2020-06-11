#include <queue>
#include <tuple>
#include <vector>
using namespace std;

class Snake {
    friend void displayOutcome(const vector<vector<int>> map, Snake snake);
private:
	queue<tuple<int, int>> position;
    
    int Bodylength;
    int eatenTarget;
    
public:
	Snake(queue<tuple<int, int>> startPosition);
	queue<tuple<int, int>> nextPosition(vector<vector<int>> map);
    
    int getlen();
    int geteatenTarget();
    void display(vector<vector<int>> map);
};

