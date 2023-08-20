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
};

// Graph class
class Graph {
  int numNodes;
  vector<Node> nodes;
  vector<vector<Edge>> adjacencyList;

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

    return visited.size() == numNodes;
  }

  bool allNodesVisited(const vector<bool> &visited) {
    for (bool v : visited) {
      if (!v) {
        return false;
      }
    }
    return true;
  }
 
  int findMaxReward(int edgeCapacity) { // edgeCost
    int maxReward = 0;
    // vector<bool> visited(numNodes, false);
    pair<int, vector<Edge>> ans;
    vector<Edge> finalSubgraph;
    for (int i = 0; i < numNodes; i++) {

      // if (!visited[i]) {
      vector<Edge> subgraph;
      int tempReward = 0;
      vector<bool> visited(numNodes, false);
      exploreComponent(i, edgeCapacity, visited, subgraph, tempReward,
                       finalSubgraph);
      // maxReward = max(maxReward, tempReward);
      if (tempReward > maxReward) {
        maxReward = tempReward;
      }
   
      subgraph.clear();
      // }
    }
    for (int i = 0; i < finalSubgraph.size(); i++) {
      cout << finalSubgraph[i].src << "  " << finalSubgraph[i].destination
           << endl;
    }
    return maxReward;
    // return subgraph;
  }

  void exploreComponent(int node, int edgeCapacity, vector<bool> &visited,
                        vector<Edge> &subgraph, int &maxReward,
                        vector<Edge> &finalSubgraph) {
    visited[node] = true;

    for (const Edge &edge : adjacencyList[node]) {
      if (!visited[edge.destination]) {
        subgraph.push_back(edge);
        int cumulativeCost = calculateCumulativeCost(subgraph);

        if (cumulativeCost <= edgeCapacity) {
          // cout<<"Hi2"<<endl;
          if (!isConnected(subgraph)) {
            // cout<<"Hi"<<endl;
            int reward = calculateTotalReward(subgraph);
            if (reward > maxReward) {
              maxReward = reward;
              // Update the final subgraph here
              finalSubgraph = subgraph;
            }
            // maxReward = max(maxReward, reward);
            // maxReward += reward;
            exploreComponent(edge.destination, edgeCapacity - cumulativeCost,
                             visited, subgraph, maxReward, finalSubgraph);
          }
        }

        subgraph.pop_back();
      }
    }
  }

  int calculateCumulativeCost(const vector<Edge> &subgraph) {
    int cumulativeCost = 0;
    for (const Edge &edge : subgraph) {
      cumulativeCost += edge.cost;
    }
    return cumulativeCost;
  }

  // Reward and edge cost --> Ratio reward to cost ratio of evry subgraph
  bool isEdgeInSubgraph(const vector<Edge> &subgraph, const Edge &edge) {
    for (const Edge &subEdge : subgraph) {
      if (subEdge.destination == edge.destination &&
          subEdge.cost == edge.cost) {
        return true;
      }
    }
    return false;
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

  void printGraph() {
    for (int i = 0; i < numNodes; i++) {
      // cout << i << " --> ";
      // for (int j = 0; j < adjacencyList[i].size(); j++) {
      //   cout << adjacencyList[i][j].destination << " ";
      // }
      // cout << endl;
      for (int j = 0; j < adjacencyList[i].size(); j++) {
        cout << i << "  " << adjacencyList[i][j].destination << endl;
      }
    }
  }
};

int main() {
  // Create a graph with 5 nodes

  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int node, edges;
  cin >> node >> edges;
  Graph graph(node);
  // Add edges and set rewards
  for (int i = 0; i < edges; i++) {
    int n1, n2, w;
    cin >> n1 >> n2 >> w;
    graph.addEdge(n1, n2, w);
    // graph.addEdge(n2, n1, w);
  }
  // graph.addEdge(0, 1, 1);
  // graph.addEdge(1, 3, 10);
  // graph.addEdge(1, 2, 2);
  // graph.addEdge(3, 4, 0);
  for (int i = 0; i < node; i++) {
    int r;
    cin >> r;
    graph.setReward(i, r);
  }

  int k = graph.findMaxReward(100);
  cout << "Optimal Answer Obtained by Greedy Approach is : " << k << endl;
  // Print The Subgraph
  // graph visualization tool
  return 0;
}
