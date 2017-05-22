def DFSstack(v, visited, S, graph):
    visited[v] = True
    for u in range(len(graph[v])):
        if graph[v][u] != 0 and not visited[u]:
            DFSstack(u, visited, S, graph)
    S.append(v)


def DFSprint(v, visited, graph):
    visited[v] = True
    print(str(v) + " ", end='')
    for u in range(len(graph[v])):
        if graph[v][u] == 1 and not visited[u]:
            DFSprint(u, visited, graph)


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
        DFSprint(v, visited, graph)
        print('\n')


path = input("Podaj sciezke pliku: ")
graph = open(path, "r+")
graph_matr = graph.readlines()[1:]
for i in range(len(graph_matr)):
    graph_matr[i] = graph_matr[i].split()

for i in range(len(graph_matr)):
    for j in range(len(graph_matr[i])):
        graph_matr[i][j] = int(graph_matr[i][j])

kosaraju(len(graph_matr), graph_matr)

graph.close()