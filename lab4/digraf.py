import random


def digraph(nodes, edges):
    file = open("matrix.txt", "w")
    for _ in range(nodes):
        matr = [[0 for _ in range(nodes)] for _ in range(nodes)]
    counter = 0

    while counter < edges:
        x = random.randint(0, nodes - 1)
        y = random.randint(0, nodes - 1)
        if not matr[x][y] and x != y:
            matr[x][y] = 1
            counter += 1

    file.write(str(nodes) + " " + str(edges) + "\n")
    for i in range(nodes):
        for j in range(nodes):
            file.write(str(matr[i][j]) + ' ')
        file.write('\n')

nodes = input("Liczba wezlow: ")
edges = input("Liczba krawedzi: ")

digraph(int(nodes), int(edges))

print("Zapisano do amtrix.txt")


