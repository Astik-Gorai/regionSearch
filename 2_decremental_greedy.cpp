#include <bits/stdc++.h>
using namespace std;

// Structure to represent a node in the graph
struct Node {
  int reward;
};

// Structure to represent an edge in the graph
struct Edge {
  int src;
  int destination;
  int cost;
  bool operator==(const Edge &other) const {
    return src == other.src && destination == other.destination &&
           cost == other.cost;
  }
  bool operator<(const Edge &other) const {
    
    return this->cost < other.cost;
  }
};

// Graph class
class Graph {
  int numNodes;
  vector<Node> nodes;
  vector<vector<Edge>> adjacencyList;
  // vector<Edge>adjacencyList;

public:
  Graph(int n) {
    numNodes = n;
    nodes.resize(n);
    adjacencyList.resize(n);
  }

  // Add an edge to the graph
  void addEdge(int source, int destination, int cost) {
    Edge edge;
    edge.destination = destination;
    edge.cost = cost;
    edge.src = source;
    adjacencyList[source].push_back(edge);
    edge.src = destination;
    edge.destination = source;
    adjacencyList[destination].push_back(edge);
  }

  // Set reward for a node
  void setReward(int node, int reward) { nodes[node].reward = reward; }

  // Get reward for a node
  int getReward(int node) { return nodes[node].reward; }

  // Get cost of an edge between two nodes
  int getEdgeCost(int source, int destination) {
    for (const Edge &edge : adjacencyList[source]) {
      if (edge.destination == destination) {
        return edge.cost;
      }
    }
    return -1; // Edge doesn't exist
  }
  bool isConnected(vector<Edge> &edges) {
    vector<vector<int>> adjacencyList(numNodes);

    // Create adjacency list from the given edges
    for (const Edge &edge : edges) {
      adjacencyList[edge.src].push_back(edge.destination);
      adjacencyList[edge.destination].push_back(edge.src);
    }

    unordered_set<int> visited;
    stack<int> stack;

    int startNode =
        edges[0].src; // Start DFS from the first node in the edges list
    stack.push(startNode);

    while (!stack.empty()) {
      int node = stack.top();
      stack.pop();

      if (visited.count(node) == 0) {
        visited.insert(node);

        // Visit all neighbors of the current node
        for (int neighbor : adjacencyList[node]) {
          if (visited.count(neighbor) == 0) {
            stack.push(neighbor);
          }
        }
      }
    }
    unordered_set<int> uniqueNodes;

    for (const Edge &edge : edges) {
      uniqueNodes.insert(edge.src);
      uniqueNodes.insert(edge.destination);
    }

    // return uniqueNodes.size();

    return visited.size() == uniqueNodes.size();
  }
  bool allNodesVisited(const vector<bool> &visited) {
    for (bool v : visited) {
      if (!v) {
        return false;
      }
    }
    return true;
  }

  int calculateTotalReward(const vector<Edge> &subgraph) {
    int reward = 0;
    unordered_set<int> st;
    for (const Edge &edge : subgraph) {
      st.insert(edge.destination);
      st.insert(edge.src);
    }
    for (int i = 0; i < numNodes; i++) {
      if (st.find(i) != st.end()) {
        reward += nodes[i].reward;
      }
    }
    return reward;
  }
  int calculateTotalCost(const vector<Edge> &subgraph) {
    int cost = 0;
    for (int i = 0; i < subgraph.size(); i++) {
      cost += getEdgeCost(subgraph[i].src, subgraph[i].destination);
    }
    return cost;
  }

  void printGraph() {
    for (int i = 0; i < numNodes; i++) {
      for (int j = 0; j < adjacencyList[i].size(); j++) {
        cout << i << "  " << adjacencyList[i][j].destination << endl;
      }
    }
  }
  // Add this method to your Graph class
  void removeEdge(int src, int dest) {
    // Find the edge in the adjacency list of the source node and remove it
    for (auto it = adjacencyList[src].begin(); it != adjacencyList[src].end();
         ++it) {
      if (it->destination == dest) {
        adjacencyList[src].erase(it);
        break;
      }
    }

    
    for (auto it = adjacencyList[dest].begin(); it != adjacencyList[dest].end();
         ++it) {
      if (it->destination == src) {
        adjacencyList[dest].erase(it);
        break; 
      }
    }
  }
  int findMaxReward(int maxEdgeCapacity, vector<Edge> &subgraph, int index,vector<Edge>& optimalSubgraph,int& ans) {
    if (index == subgraph.size()) {
      if (isConnected(subgraph)) {
        cout << "Total Edge Cost :" << calculateTotalCost(subgraph) << endl;
        int reward =  calculateTotalReward(subgraph);
        if(reward > ans){
          optimalSubgraph.clear();
          ans = reward;
          for(int i=0;i<subgraph.size();i++){
            optimalSubgraph.push_back(subgraph[i]);
          }
          return ans;
        }
      }
      return 0;
    }
    int maxReward = 0;
    Edge curr = subgraph[index];
    int currEdgeCost = getEdgeCost(curr.src, curr.destination);
    int takeReward = 0, notTakeReward = 0;
    if (maxEdgeCapacity >= currEdgeCost) {
      takeReward =
          findMaxReward3(maxEdgeCapacity - currEdgeCost, subgraph, index + 1,optimalSubgraph,ans);
    }
    auto it = find(subgraph.begin(), subgraph.end(), curr);
    subgraph.erase(it);
    
    notTakeReward = findMaxReward3(maxEdgeCapacity, subgraph, index,optimalSubgraph,ans);

    return max(takeReward, notTakeReward);
  }
  // Add this method to your Graph class
  void printSubgraph(const vector<Edge> &subgraph) {
    for (const Edge &edge : subgraph) {
      cout << edge.src << "  " << edge.destination << endl;
    }
  }
};

int main() {
  // Create a graph with 5 nodes

  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int node, edges;
  cin >> node >> edges;
  vector<Edge> subgraph;
  Graph graph(node);
  // Add edges and set rewards
  for (int i = 0; i < edges; i++) {
    Edge temp;
    int n1, n2, w;
    cin >> n1 >> n2 >> w;
    graph.addEdge(n1, n2, w);
    temp.src = n1;
    temp.destination = n2;
    subgraph.push_back(temp);
  }
  for (int i = 0; i < node; i++) {
    int r;
    cin >> r;
    graph.setReward(i, r);
  }
  vector<Edge> ans;
  vector<Edge>optimalSubgraph;
  int maxReward = -1;
  int k = graph.findMaxReward(28, subgraph, 0,optimalSubgraph,maxReward);
  cout << "Optimal Answer Obtained by Greedy Approach is : " << k << endl;
  graph.printSubgraph(optimalSubgraph);

  return 0;
}

