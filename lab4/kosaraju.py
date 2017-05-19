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


def kosaraju(nodes, graph):
    visited = [False for _ in range(nodes)]
    S = []
    for v in range(nodes):
        if not visited[v]:
            DFStack(v, visited, S, graph)
    visited = [False for _ in range(nodes)]
    cn = 0
    while S:
        v = S.pop()
        if visited[v]:
            continue
        cn += 1
        print("SCC " + str(cn) + ": ")
        DFSprint(v, visited, graph)


path = input("Podaj ścieżkę pliku: ")
graph = open(path, "r+")
matrix = graph.readlines()
for i in range(len(matrix)):
    matrix[i] = matrix[i].split()

# for i in range(len(matrix)):
#     print(matrix[i])

#visited = [False for _ in range(len(matrix))]

kosaraju(len(matrix), matrix)

graph.close()
