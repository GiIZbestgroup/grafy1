from random import randint
from zad3 import bellmanford

def potential(graph, nodes):
    #dodanie nowego wierzcholka, polaczonego z kazdym innym sciezkami o wadze 0
    for i in range(nodes):
        graph[i].append('x')
    nodes += 1
    graph.append([0 for _ in range(nodes)])

    #wykonanie algorytmu Bellmana-Forda na tym wierzcholku
    bf = bellmanford(graph, nodes - 1)
    if not bf[0]:
        return False
    else:
        return bf[1]


def johnson(G, n):
    d = potential(G, n)
    if not d:
        return False
    for i in range(n):
        for j in range(n):
            if type(G[i][j]) is int:
                G[i][j] += (d[i] - d[j])

    for i in range(n):
        #zrób Dijkstrę

    for i in range(n):
        for j in range(n):
            if type(G[i][j]) is int:
                G[i][j] += (d[j] - d[i])




path = input("Podaj sciezke pliku: ")
graph = open(path, "r+")
graph_matr = graph.readlines()[1:]
for i in range(len(graph_matr)):
    graph_matr[i] = graph_matr[i].split()

for i in range(len(graph_matr)):
    for j in range(len(graph_matr[i])):
        graph_matr[i][j] = int(graph_matr[i][j])
        graph_matr[i][j] *= randint(-2, 10)

        if not graph_matr[i][j]:
            graph_matr[i][j] = 'x'

graph.close()

