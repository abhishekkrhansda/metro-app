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
   g.addVertex("Deepanjali Nagar");
    g.addVertex("Magadi Road");
    g.addVertex("Nagasandra");
    g.addVertex("Dasarahalli");
    g.addVertex("Jalahalli");
    g.addVertex("Peenya");
    g.addVertex("Peenya Industry");
    g.addVertex("Yeshwanthpur");
    g.addVertex("Sandal Soap Factory");
    g.addVertex("Mahalakshmi");
    g.addVertex("Rajajinagar");
    g.addVertex("Kuvempu Road");
    g.addVertex("Srirampura");
    g.addVertex("Mantri Square Sampige Road");
    g.addVertex("Kempegowda Majestic");
    g.addVertex("Chickpete");
    g.addVertex("Krishna Rajendra Market");
    g.addVertex("National College");
    g.addVertex("Lalbagh");
    g.addVertex("South End Circle");
    g.addVertex("Jayanagar");
    g.addVertex("Rashtreeya Vidyalaya Road");
    g.addVertex("Banashankari");
    g.addVertex("JP Nagar");
    g.addVertex("Yelachenahalli");

    // Add edges (connections with weights)
    g.addEdge("MG Road", "Trinity", 2);
    g.addEdge("Trinity", "Halasuru", 2);
    g.addEdge("Halasuru", "Indiranagar", 2);
    g.addEdge("Indiranagar", "Swami Vivekananda Road", 2);
    g.addEdge("Swami Vivekananda Road", "Baiyappanahalli", 3);
    g.addEdge("MG Road", "Kempegowda Majestic", 7);
    g.addEdge("Kempegowda Majestic", "Mysore Road", 8);
    g.addEdge("Mysore Road", "Deepanjali Nagar", 2);
    g.addEdge("Deepanjali Nagar", "Magadi Road", 3);
    g.addEdge("Nagasandra", "Dasarahalli", 2);
    g.addEdge("Dasarahalli", "Jalahalli", 2);
    g.addEdge("Jalahalli", "Peenya", 2);
    g.addEdge("Peenya", "Peenya Industry", 1);
    g.addEdge("Peenya Industry", "Yeshwanthpur", 3);
    g.addEdge("Yeshwanthpur", "Sandal Soap Factory", 2);
    g.addEdge("Sandal Soap Factory", "Mahalakshmi", 2);
    g.addEdge("Mahalakshmi", "Rajajinagar", 1);
    g.addEdge("Rajajinagar", "Kuvempu Road", 2);
    g.addEdge("Kuvempu Road", "Srirampura", 2);
    g.addEdge("Srirampura", "Mantri Square Sampige Road", 2);
    g.addEdge("Kempegowda Majestic", "Chickpete", 1);
    g.addEdge("Chickpete", "Krishna Rajendra Market", 1);
    g.addEdge("Krishna Rajendra Market", "National College", 2);
    g.addEdge("National College", "Lalg.addVertex("MG Road");
    g.addVertex("Trinity");
    g.addVertex("Halasuru");
    g.addVertex("Indiranagar");
    g.addVertex("Swami Vivekananda Road");
    g.addVertex("Baiyappanahalli");
    g.addVertex("Mysore Road");
    g.addVebagh", 2);
    g.addEdge("Lalbagh", "South End Circle", 1);
    g.addEdge("South End Circle", "Jayanagar", 2);
    g.addEdge("Jayanagar", "Rashtreeya Vidyalaya Road", 1);
    g.addEdge("Rashtreeya Vidyalaya Road", "Banashankari", 2);
    g.addEdge("Banashankari", "JP Nagar", 2);
    g.addEdge("JP Nagar", "Yelachenahalli", 3);

    string startStation ;
    cout << "starting station"<<" ";
    cin>>startStation;

    string endStation ;
    cout<< "ending station" << " ";
    cin>>endStation;

    int startIndex = g.getStationIndex(startStation);
    int endIndex = g.getStationIndex(endStation);

    vector<int> parents = g.dijkstra(startIndex, g.getNumberOfStations());

    cout << "Shortest path from " << startStation << " to " << endStation << " ----> " << "    ";
    g.printPath(parents, endIndex);
    cout << endl;

    return 0;
}

