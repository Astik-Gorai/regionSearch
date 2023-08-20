import networkx as nx
import matplotlib.pyplot as plt

# Read input from the main graph file
with open('input18.txt', 'r') as file:
    lines = file.readlines()

total_nodes, total_edges = map(int, lines[0].split())

# Create a graph using NetworkX
G = nx.Graph()

# Add nodes to the graph
for i in range(total_nodes):
    G.add_node(i)

# Add edges to the graph
for line in lines[1:]:
    parts = line.strip().split()
    if len(parts) == 3:
        start_vertex, end_vertex, cost = map(int, parts)
        G.add_edge(start_vertex, end_vertex, weight=cost)
        G.add_edge(start_vertex, end_vertex)

# Read input from the subgraph file
subgraph_edges = []
with open('subgraph.txt', 'r') as subgraph_file:
    subgraph_lines = subgraph_file.readlines()

for line in subgraph_lines:
    parts = line.strip().split()
    if len(parts) == 2:
        start_vertex, end_vertex = map(int, parts)
        subgraph_edges.append((start_vertex, end_vertex))

# Drawing the graph using spring layout
pos = nx.spring_layout(G)
nx.draw(G, pos, with_labels=True, node_size=1000, font_size=10)

# Highlight subgraph nodes with a different color
subgraph_nodes = set()
for start, end in subgraph_edges:
    subgraph_nodes.add(start)
    subgraph_nodes.add(end)

nx.draw_networkx_nodes(G, pos, nodelist=subgraph_nodes, node_color='r', node_size=1000)

# Highlight subgraph edges with a different color
nx.draw_networkx_edges(G, pos, edgelist=subgraph_edges, edge_color='r', width=2)

edge_labels = nx.get_edge_attributes(G, 'weight')
nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels)

# Show the graph
plt.show()
