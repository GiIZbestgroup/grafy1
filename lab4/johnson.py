from zad3 import bellmanford
from Graph import Graph


def potential(graph):
    # dodanie nowego wierzcholka, polaczonego z kazdym innym sciezkami o wadze 0
    for i in range(graph.nodes):
        graph.adjacencyMatrix[i].append(0)
    graph.nodes += 1
    graph.adjacencyMatrix.append([1 for _ in range(graph.nodes-1)])
    graph.adjacencyMatrix[-1].append(0)

    for i in range(len(graph.valueMatrix[0])):
        graph.valueMatrix[i].append(0)
    graph.valueMatrix.append([0 for _ in range(graph.nodes)])

    # wykonanie algorytmu Bellmana-Forda na tym wierzcholku
    bf = bellmanford(graph, graph.nodes - 1)

    return bf


def johnson(graph):
    d = potential(graph)
    if not d[0]:
        print("Cykl ujemny, koncze dzialanie.")
        return False
    for i in range(graph.nodes):
        for j in range(graph.nodes):
            if graph.adjacencyMatrix[i][j]:
                graph.valueMatrix[i][j] += (d[1][i] - d[1][j])

    for i in range(graph.nodes-1):
        graph.show_dijkstra_tab(i, graph.dijkstra(i))

    dist = graph.get_minimal_distances()
    for row in dist:
        row.pop()
    dist.pop()

    graph.show_minimal_distances(dist)

    for i in range(graph.nodes):
        for j in range(graph.nodes):
            if graph.adjacencyMatrix[i][j]:
                graph.valueMatrix[i][j] += (d[1][i] - d[1][j])

##########################################

Graph1 = Graph()

path = input("Podaj sciezke pliku: ")
Graph1.from_file(path)
Graph1.set_values(-2, 10)

Graph1.show()
print()
Graph1.show_value()
print()
johnson(Graph1)
