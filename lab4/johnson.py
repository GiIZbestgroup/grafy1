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


def remove(matr):
    for i in range(len(matr)):
        matr[i].pop()
    matr.pop()


def johnson(graph):
    d = potential(graph)
    if not d[0]:
        print("Cykl ujemny, koncze dzialanie.")
        return False

    remove(graph.adjacencyMatrix)
    remove(graph.valueMatrix)
    graph.nodes -= 1
    d[1].pop()

    for i in range(graph.nodes):
        for j in range(graph.nodes):
            if graph.adjacencyMatrix[i][j]:
                graph.valueMatrix[i][j] += (d[1][i] - d[1][j])

    # graph.show()
    # print()
    # graph.show_value()
    #
    # for i in range(graph.nodes):
    #     graph.show_dijkstra_tab(i, graph.dijkstra(i))

    dist = graph.get_minimal_distances()

    for i in range(graph.nodes):
        for j in range(graph.nodes):
            if graph.adjacencyMatrix[i][j]:
                dist[i][j] -= (d[1][i] - d[1][j])

    graph.show_minimal_distances(dist)

##########################################

Graph1 = Graph()

path = input("Podaj sciezke pliku: ")
Graph1.from_file(path)
Graph1.set_values(-2, 10)

print("Macierz sasiedztwa:")
Graph1.show()
print("Macierz wag:")
Graph1.show_value()
print("Macierz sciezek:")
johnson(Graph1)
