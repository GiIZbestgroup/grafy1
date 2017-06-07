from random import randrange as random
from Graph import Graph

def DFSstack(v, visited, S, graph):
    visited[v] = True
    for u in range(len(graph[v])):
        if graph[v][u] != 0 and not visited[u]:
            DFSstack(u, visited, S, graph)
    S.append(v)


def DFSprint(v, visited, graph, tabela):
    visited[v] = True
    tabela.append(int(v))
    print(str(v) + " ", end='')
    for u in range(len(graph[v])):
        if graph[v][u] == 1 and not visited[u]:
            DFSprint(u, visited, graph, tabela)


def transpose(graph):
    temp = [[] for _ in range(len(graph[0]))]
    for i in range(len(graph[0])):
        for j in range(len(graph)):
            temp[i].append(graph[j][i])
    return temp


def kosaraju(nodes, graph):
    tabela2 = []
    visited = [False for _ in range(nodes)]
    S = []
    for v in range(nodes):
        if not visited[v]:
            DFSstack(v, visited, S, graph)
    graph = transpose(graph)
    visited = [False for _ in range(nodes)]
    cn = 0
    while S:
        v = S.pop()
        if visited[v]:
            continue
        cn += 1
        print("SCC " + str(cn) + ": ", end='')
        tabela = []
        DFSprint(v, visited, graph, tabela)
        if (len(tabela) > len(tabela2)):
            tabela2 = tabela[:]
        print('\n')
    return tabela2


def makegraphof(graph_matr, tabela2):
    listawierzcholkow = {j: i for i, j in enumerate(tabela2)}

    # print(listawierzcholkow)

    new_matr = [[0 for _ in range(len(listawierzcholkow))] for _ in range(len(listawierzcholkow))]

    for j in range(len(graph_matr)):
        for indeks in range(len(graph_matr[0])):
            if graph_matr[j][indeks] == 1:
                if indeks in listawierzcholkow and j in listawierzcholkow:
                    new_matr[listawierzcholkow[j]][listawierzcholkow[indeks]] = 1

    return new_matr


def bellmanford(graph, starting_point_number):
    d = [999 for _ in range(len(graph.valueMatrix))]
    p = [-1 for _ in range(len(graph.valueMatrix))]
    d[starting_point_number] = 0

    for i in range(1, len(graph.valueMatrix)):
        test = True
        for x in range(len(graph.valueMatrix)):
            for y in range(len(graph.valueMatrix)):
                if graph.adjacencyMatrix[x][y] != 0:
                    if d[y] < (d[x] + graph.valueMatrix[x][y]):
                        continue
                    else:
                        test = False
                        d[y] = d[x] + graph.valueMatrix[x][y]
                        p[y] = x
        if test:
            return (True, d, p)

    for x in range(len(graph.valueMatrix)):
        for y in range(len(graph.valueMatrix)):
            if graph.adjacencyMatrix[x][y] != 0:
                if d[y] > (d[x] + graph.valueMatrix[x][y]):
                    return (False, d, p)
    return (True, d, p)

