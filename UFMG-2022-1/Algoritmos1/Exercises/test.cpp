#include <iostream>
#include <list>
#include <vector>
#include <queue>

using namespace std;

void showpq(priority_queue<int, vector<int>, greater<int> > q) {
    priority_queue<int, vector<int>, greater<int> > g = q;

    while (!g.empty()) {
        cout << '\t' << g.top();
        g.pop();
    }
    cout << '\n';
}

int main() {
    priority_queue <int, vector <int>, greater <int> > q;
    q.push(5);
    q.push(13);
    q.push(4);
    q.push(56);
    q.push(1);

    showpq(q);
    cout << q.top() << endl;
    return 0;
}