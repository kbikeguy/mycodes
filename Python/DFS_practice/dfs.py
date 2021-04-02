from collections import defaultdict


class Graph:
    # Constructor
    def __init__(self):
        # a default dictionary to store the graph
        self.graph = defaultdict(list)

    # Function to add an edge to the graph
    def addEdge(self, u, v):
        self.graph[u].append(v)

    # a functioin used by the DFS
    def DFSUtil(self, v, visited):
        # mark the current node as visited and print it
        visited.add(v)
        print(v, end=' ')

        # recurse for all verticies ajacent to this vertex
        for neighbor in self.graph[v]:
            if neighbor not in visited:
                self.DFSUtil(neighbor, visited)

    # This function does the DFS traversal and used DFSUtil
    def DFS(self, ):

        # Create a set to store visited vertices
        visited = set()

        # call the recersive helper
        for v in self.graph:
            if v not in visited:
                self.DFSUtil(v, visited)


# Driver code
g = Graph()
g.addEdge(0, 1)
g.addEdge(0, 2)
g.addEdge(1, 2)
g.addEdge(2, 0)
g.addEdge(2, 3)
g.addEdge(3, 3)
print("Following is DFS from (starting from vertex 2)")
g.DFS()
