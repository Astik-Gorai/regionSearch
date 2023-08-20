import networkx as nx
import random

# We have to pass the <node no> and <density>
G = nx.gnp_random_graph(100, 0.4)

# Add random weights to the edges
for (u, v) in G.edges():
    G.edges[u, v]['weight'] = random.randint(1, 100)


with open("/Users/goraiastik2000/Desktop/Final Project/02_MostInfluReg/input18.txt", "w") as f:
    f.write(str(len(G.nodes()))+"  ")
    f.write(str(len(G.edges()))+"\n")
    # Write edges to file
    for (u, v, w) in G.edges(data='weight'):
        f.write("{}\t{}\t{}\n".format(u, v, w))
    
    f.flush()
# Print a message indicating that the file was written
print("Output written to output.txt")

with open("/Users/goraiastik2000/Desktop/Final Project/02_MostInfluReg/input18.txt", "a") as f:
    for u in G.nodes():
        f.write(str(random.randint(1, 100)) + "\n")
    
