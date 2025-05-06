/*
# "The Travel Planner" is a console-based application developed in C++ 
that utilizes Dijkstra’s algorithm to calculate the shortest path 
between cities.  It simulates a basic navigation system by accepting 
city names and route distances, storing them in an adjacency matrix,
 and allowing the user to select a source city to calculate the
 shortest distance to all other cities.
Concepts Used
- Arrays
- 2D matrices (Adjacency matrix)
- Dijkstra’s algorithm (Greedy approach)
- Graphs
- Basic I/O operations
How to Use
1. Run the program or Execute the program
2. Enter number of cities and their names.
3. Enter route details (indices of cities and distance).
4. Choose a city to find the shortest distances from it.
## Sample Input
Cities: 4
Names: Hyderabad, Bangalore, Chennai, Mumbai
Routes:
0 1 500
1 2 350
0 2 800
2 3 700
## Output
Shortest distances from Hyderabad:  
To Hyderabad : 0 km  
To Bangalore : 500 km  
To Chennai : 850 km  
To Mumbai : 1550 km

## Limitations
- Maximum of 10 cities.
- Only supports undirected routes or one directional routes
- Doesn't support real-time map integration
*/
#include <iostream>
#include <string>
#include <climits>
using namespace std;

const int MAX = 10;

string cities[MAX];
int graph[MAX][MAX];
int n = 0;

int minDist(int dist[], bool visited[]) {
    int min = INT_MAX;
    int index = -1;
    for (int i = 0; i < n; i++) {
        if (!visited[i] && dist[i] < min) {
            min = dist[i];
            index = i;
        }
    }
    return index;
}

void shortestPath(int src) {
    int dist[MAX];
    bool visited[MAX];

    for (int i = 0; i < n; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
    }

    dist[src] = 0;

    for (int i = 0; i < n - 1; i++) {
        int u = minDist(dist, visited);
        if (u == -1) break;
        visited[u] = true;

        for (int v = 0; v < n; v++) {
            if (!visited[v] && graph[u][v] > 0 && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    cout << "\nFrom: " << cities[src] << endl;
    for (int i = 0; i < n; i++) {
        cout << "To " << cities[i] << ": ";
        if (dist[i] == INT_MAX) cout << "unreachable" << endl;
        else cout << dist[i] << " km" << endl;
    }
}

int main() {
    cout << "Total cities  (up to " << MAX << "): ";
    cin >> n;

    if (n < 1 || n > MAX) {
        cout << "Invalid. Try again.\n";
        return 0;
    }

    cin.ignore();

    for (int i = 0; i < n; i++) {
        cout << "City " << i << ": ";
        getline(cin, cities[i]);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = 0;
        }
    }

    int r;
    cout << "No. of routes: ";
    cin >> r;

    for (int i = 0; i < r; i++) {
        int a, b, d;
        cout << "Route " << i + 1 << " (from to dist): ";
        cin >> a >> b >> d;
        if (a >= 0 && a < n && b >= 0 && b < n && d > 0) {
            graph[a][b] = d;
            graph[b][a] = d;
        } else {
            cout << "Bad input or Invalid input. Try again!.\n";
            i--;
        }
    }

    while (true) {
        cout << "\nList of cities:\n";
        for (int i = 0; i < n; i++) {
            cout << i << " - " << cities[i] << "\n";
        }

        int start;
        cout << "\nSource index (-1 to quit): ";
        cin >> start;

        if (start == -1) break;
        if (start >= 0 && start < n) {
            shortestPath(start);
        } else {
            cout << "Invalid index or Not valid index \n";
        }
    }

    cout << "\nDone.\n";
    return 0;
}
