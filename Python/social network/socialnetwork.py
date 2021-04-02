"""
Authors: Riley Campbell, Lane Moseley
Class: CSC-372 Analysis of Algorithms, Fall 2020
Description: Strongly Connected Components for Social Networks
"""
from collections import deque
import networkx as nx
import matplotlib.pyplot as plt


class Vertex:
    """
    Graph vertex.
    """

    def __init__(self, value, neighbors=None):
        """
        Initialize the vertex with a value and a set of neighbors.

        Args:
            value:
            neighbors:
        """
        # neighbors=[] is mutable, avoid that
        if neighbors is None:
            neighbors = []

        self.index = -1
        self.lowlink = -1
        self.on_stack = False

        self.neighbors = neighbors
        self.value = value


def buildEdges(friends, G):
    for key, values in friends.items():
        for value in values:
            G.add_edge(key, value)


def printSCC(dictionary, scc):
    G = nx.DiGraph()
    # filter out anything not in the scc
    if len(scc) > 1:
        for name in list(dictionary):
            if name not in scc:
                del dictionary[name]
            else:
                dictionary[name] = [x for x in dictionary[name] if x in scc]

        buildEdges(dictionary, G)
    else:
        G.add_node(scc[0])
    # print graph
    plt.figure()
    nx.draw_networkx(G, with_labels=True, node_color='green')
    plt.show()


class SocialNetwork:
    """
    Social network graph. The graph is presumed to be un-directed.
    """

    def __init__(self, dictionary):
        """
        Initialize the graph with a set of vertices.

        Args:
            dictionary: { vertex: [neighbors] }
        """
        self.__index = 0  # global index for SCC
        self.__path = []  # list to track dfs path
        self.__S = deque()  # stack for SCC

        # build a list of vertices and edges
        self.__vertices = [Vertex(key, value) for key, value in dictionary.items()]
        self.__edges = self.__edge_list()
        self.__origDict = dictionary
        self.__global_components = []

    def __edge_list(self):
        """Build an edge list from a list of Vertices.

        Returns:
            edges: [(v, w)] where v, w are Vertex instances
        """
        edges = []

        for v in self.__vertices:
            for w_value in v.neighbors:
                # w is just a value, find the associated Vertex instance
                w_vertex = next(vertex for vertex in self.__vertices if vertex.value == w_value)
                edges.append((v, w_vertex))

        return edges

    def connected_components(self, show_plot=True):
        # Pseudocode from
        # https://en.wikipedia.org/wiki/Tarjan%27s_strongly_connected_components_algorithm#The_algorithm_in_pseudocode

        self.__global_components = []

        # input is self.__vertices
        self.__S = deque()  # create an empty stack
        self.__index = 0  # index starts at zero
        for v in self.__vertices:
            if v.index == -1:
                self.connected_components_helper(v, show_plot)

        return self.__global_components

    def connected_components_helper(self, vertex, show_plot=True):
        # Pseudocode from
        # https://en.wikipedia.org/wiki/Tarjan%27s_strongly_connected_components_algorithm#The_algorithm_in_pseudocode

        vertex.index = self.__index
        vertex.lowlink = self.__index
        self.__index += 1
        vertex.on_stack = True
        self.__S.append(vertex)

        for _, w in self.__edges:
            if w.index == -1:
                self.connected_components_helper(w, show_plot)
                vertex.lowlink = min(vertex.lowlink, w.lowlink)
            elif w.on_stack is True:
                vertex.lowlink = min(vertex.lowlink, w.index)

        if vertex.lowlink == vertex.index:
            component = []

            w = self.__S.pop()
            w.on_stack = False
            component.append(w.value)

            while w != vertex:
                w = self.__S.pop()
                w.on_stack = False
                component.append(w.value)

            if show_plot is True:
                # display result of SCC
                printSCC(self.__origDict.copy(), component)

            self.__global_components.append(component)

    def dfs(self, value):
        """
        Perform depth first search. This function is not used for the SCC, but
        was added for reference and as build-up to the SCC functions.

        Args:
            value: starting node

        Returns:
            [ ]: depth first search traversal
        """

        # check for empty list
        if value is None:
            return

        # reset the path from any prior iteration
        self.__path = []

        # given some value, find the vertex with that value
        vertex = next(v for v in self.__vertices if v.value == value)

        # start the dfs
        visited = []
        self.dfs_helper(vertex, visited)

        return self.__path

    def dfs_helper(self, vertex, visited):
        """
        Recursive helper function for depth first search. This function is not
        used for the SCC, but was added for reference and as build-up to the
        SCC functions.

        Args:
            vertex: current node
            visited: list of visited nodes

        Returns:
            None
        """
        # add the vertex to the visited list
        visited.append(vertex.value)

        # add the vertex to the path
        self.__path.append(vertex.value)

        for neighbor in vertex.neighbors:
            if neighbor not in visited:
                # given some neighboring value, find the vertex with that value
                next_vertex = next(v for v in self.__vertices if v.value == neighbor)

                # recurse through the neighbors neighbors
                self.dfs_helper(next_vertex, visited)

    def getHead(self):
        if len(self.__vertices) > 0:
            return self.__vertices[0].value
        else:
            return None
