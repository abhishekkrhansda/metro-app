#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <climits>
#include <string>

using namespace std;

// Structure to represent an edge in the graph
struct Edge {
    int destination;
    int weight;
};

// Comparator for priority queue to get the minimum distance
struct Compare {
    bool operator()(const pair<int, int>& p1, const pair<int, int>& p2) {
        return p1.second > p2.second; // Min-heap
    }
};

// Class to represent the Graph
class Graph {
private:
    unordered_map<string, int> stationIndex;
    vector<string> indexStation;
    vector<vector<Edge>> adjacencyList;

public:
    // Add a vertex to the graph
    void addVertex(const string& station) {
        if (stationIndex.find(station) == stationIndex.end()) {
            int index = stationIndex.size();
            stationIndex[station] = index;
            indexStation.push_back(station);
            adjacencyList.resize(index + 1);
        }
    }

    // Add an edge to the graph
    void addEdge(const string& src, const string& dest, int weight) {
        if (stationIndex.find(src) != stationIndex.end() && stationIndex.find(dest) != stationIndex.end()) {
            int srcIndex = stationIndex[src];
            int destIndex = stationIndex[dest];
            adjacencyList[srcIndex].push_back({destIndex, weight});
            adjacencyList[destIndex].push_back({srcIndex, weight}); // Assuming bidirectional graph
        }
    }

    // Dijkstra's algorithm to find the shortest path from start to end
    vector<int> dijkstra(int start, int n) {
        vector<int> distances(n, INT_MAX);
        vector<int> parents(n, -1);
        priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq;

        distances[start] = 0;
        pq.push({start, 0});

        while (!pq.empty()) {
            int u = pq.top().first;
            pq.pop();

            for (const Edge& edge : adjacencyList[u]) {
                int v = edge.destination;
                int weight = edge.weight;

                if (distances[u] + weight < distances[v]) {
                    distances[v] = distances[u] + weight;
                    parents[v] = u;
                    pq.push({v, distances[v]});
                }
            }
        }

        return parents;
    }

    // Function to print the path from start to end
    void printPath(const vector<int>& parents, int end) {
        if (end == -1) return;
        printPath(parents, parents[end]);
        cout << indexStation[end] << " ";
    }

    // Get index of a station
    int getStationIndex(const string& station) {
        return stationIndex[station];
    }

    // Get the number of stations
    int getNumberOfStations() const {
        return stationIndex.size();
    }
};

// Main function to demonstrate the functionality
int main() {
    Graph g;

    // Add vertices (stations)
    g.addVertex("MG Road");
    g.addVertex("Bangalore Cantt");
    g.addVertex("Madiwala");
    g.addVertex("Bangalore East");
    g.addVertex("Jayanagar");
    g.addVertex("Kormangala");
    g.addVertex("Indiranagar");
    g.addVertex("Whitefield");
    g.addVertex("Electronic City");
    g.addVertex("Hosur Road");

    // Add edges (connections with weights)
    g.addEdge("MG Road", "Bangalore Cantt", 10);
    g.addEdge("Bangalore Cantt", "Madiwala", 15);
    g.addEdge("Madiwala", "Bangalore East", 10);
    g.addEdge("Bangalore East", "Jayanagar", 20);
    g.addEdge("Jayanagar", "Kormangala", 5);
    g.addEdge("Kormangala", "Indiranagar", 10);
    g.addEdge("Indiranagar", "Whitefield", 25);
    g.addEdge("Whitefield", "Electronic City", 30);
    g.addEdge("Electronic City", "Hosur Road", 15);
    g.addEdge("Hosur Road", "MG Road", 50);

    string startStation ;
    cout << "starting station"<<" ";
    cin>>startStation;

    string endStation ;
    cout<< "ending station" << " ";
    cin>>endStation;

    int startIndex = g.getStationIndex(startStation);
    int endIndex = g.getStationIndex(endStation);

    vector<int> parents = g.dijkstra(startIndex, g.getNumberOfStations());

    cout << "Shortest path from " << startStation << " to " << endStation << ": ";
    g.printPath(parents, endIndex);
    cout << endl;

    return 0;
}

