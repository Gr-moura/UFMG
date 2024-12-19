import networkx as nx
import matplotlib.pyplot as plt

# Define the relation R as a directed graph
R = nx.DiGraph()
R.add_edges_from([("a", "b"), ("a", "c"), ("b", "c")])

# Compute the transitive reduction
Hasse = nx.transitive_reduction(R)

# Draw the Hasse diagram
pos = nx.spring_layout(Hasse)
nx.draw(Hasse, pos, with_labels=True, node_color='lightblue', arrows=False)
plt.show()
