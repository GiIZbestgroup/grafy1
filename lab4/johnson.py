from zad3 import bellmanford
from Graph import Graph


def potential(graph):
    #dodanie nowego wierzcholka, polaczonego z kazdym innym sciezkami o wadze 0
    for i in range(graph.nodes):
        graph.adjacencyMatrix[i].append(0)
    graph.nodes += 1
    graph.adjacencyMatrix.append([1 for _ in range(graph.nodes)])

    for i in range(len(graph.valueMatrix[0])):
        graph.valueMatrix[i].append(0)
    graph.valueMatrix.append([0 for _ in range(graph.nodes)])

    #wykonanie algorytmu Bellmana-Forda na tym wierzcholku
    bf = bellmanford(graph.adjacencyMatrix, graph.nodes - 1)
    if not bf[0]:
        return False
    else:
        return bf[1]

def remove(graph):
    pass


def johnson(graph):
    d = potential(graph)
    if not d:
        return False
    for i in range(graph.nodes):
        for j in range(graph.nodes):
            if graph.adjacencyMatrix[i][j]:
                graph.valueMatrix[i][j] += (d[i] - d[j])

    for i in range(graph.nodes-1):
        graph.show_dijkstra_tab(i, graph.dijkstra(i))

    for i in range(graph.nodes):
        for j in range(graph.nodes):
            if graph.adjacencyMatrix[i][j]:
                graph.valueMatrix[i][j] += (d[i] - d[j])

    return d

##########################################

Graph1 = Graph()

path = input("Podaj sciezke pliku: ")
Graph1.from_file(path)
Graph1.set_values(-3, 10)

Graph1.show()
print()
Graph1.show_value()
print()
johnson(Graph1)
