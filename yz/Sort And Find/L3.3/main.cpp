#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Node {
    string name;
    int prade;
    int id;
    
    Node () {}
    Node (string name, int prade, int id) : name(name), prade(prade), id(id) {}
    
    bool operator <(const Node &o) const {
        if (prade == o.prade)
            return id < o.id;
        return prade < o.prade;
    }
    
    bool operator >(const Node &o) const {
        if (prade == o.prade)
            return id < o.id;
        return prade > o.prade;
    }
};

int main() {
    int n;
    int flag;
    while (cin >> n >> flag) {
        vector<Node> peo;
        for (int i = 0; i < n ; i++) {
            string name;
            int prade, id = i;
            cin >> name >> prade;
            peo.push_back(Node(name, prade, id));
        }
        if (flag)
            sort(peo.begin(), peo.end(), less<Node>());
        else
            sort(peo.begin(), peo.end(), greater<Node>());
        for (int i = 0; i < n; i++)
            cout << peo[i].name << " " << peo[i].prade << endl;
    }
    return 0;
}