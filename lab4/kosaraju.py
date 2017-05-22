#import numpy as np

def DFStack(start, visited, S, graph):
    visited[start] = True
    for i in range(len(graph[start])):
        if graph[start][i] and not visited[i]:
            DFStack(i, visited, S, graph)
    S.append(start)


def DFSprint(start, visited, graph):
    visited[start] = True
    print(start)
    for i in range(len(graph[start])):
        if graph[start][i] and not visited[i]:
            DFSprint(i, visited, graph)


def transpose(graph):
    temp = [[] for _ in range(len(graph[0]))]
    for i in range(len(graph[0])):
        for j in range(len(graph)):
            temp[i].append(graph[j][i])
    return temp


def kosaraju(nodes, graph):
    visited = [False for _ in range(nodes)]
    S = []
    for v in range(nodes):
        if not visited[v]:
            DFStack(v, visited, S, graph)
    graph = transpose(graph)
    visited = [False for _ in range(nodes)]
    cn = 0
    while S:
        v = S.pop()
        if visited[v]:
            continue
        cn += 1
        print("SCC " + str(cn) + ": ")
        DFSprint(v, visited, graph)


path = input("Podaj œcie¿kê pliku: ")
graph = open(path, "r+")
graph_matr = graph.readlines()[1:]
for i in range(len(graph_matr)):
    graph_matr[i] = graph_matr[i].split()

#graph_matr = np.matrix(graph_matr)

kosaraju(len(graph_matr), graph_matr)

graph.close()