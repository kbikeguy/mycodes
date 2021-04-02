from collections import defaultdict


class Graph:

    def __init__(self):
        # default dict to store a graph
        self.graph = defaultdict(list)

    # function to add an edge to the graph
    def addEdge(self, u, v):
        self.graph[u].append(v)

    def BFS(self, source):
        # mark al vertices as not visited
        visited = [False] * (max(self.graph) + 1)

        # create a queue for BFS
        queue = [source]

        # mark source node as visited
        visited[source] = True

        while queue:
            # dequeue a vertex from queue and print it
            source = queue.pop(0)
            print(source, end=" ")

            # Get all adjacent vertices of the
            # dequeued vertex s. If a adjacent
            # has not been visited, then mark it
            # visited and enqueue it
            for i in self.graph[source]:
                if not visited[i]:
                    queue.append(i)
                    visited[i] = True


# Driver code

# Create a graph given in
# the above diagram
g = Graph()
g.addEdge(0, 1)
g.addEdge(0, 2)
g.addEdge(1, 2)
g.addEdge(2, 0)
g.addEdge(2, 3)
g.addEdge(3, 3)

print("Following is Breadth First Traversal"
      " (starting from vertex 2)")
g.BFS(1)
