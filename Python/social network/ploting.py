import matplotlib.pyplot as plt
import networkx as nx
from main import randomFriendGenerator, getPeople


def buildEdges(friends, G):
    for key, values in friends.items():
        for value in values:
            G.add_edge(key, value)


def main():
    G = nx.DiGraph()
    names = getPeople()
    G.add_nodes_from(names)
    friendsDict = randomFriendGenerator(names)
    buildEdges(friendsDict, G)

    plt.figure()

    nx.draw_networkx(G, with_labels=True, node_color='green')
    plt.show()


if __name__ == "__main__":
    main()
