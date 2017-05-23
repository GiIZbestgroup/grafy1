#!/usr/bin/env python3

from random import randrange as random

def DFSstack(v, visited, S, graph):
    visited[v] = True
    for u in range(len(graph[v])):
        if graph[v][u] != 0 and not visited[u]:
            DFSstack(u, visited, S, graph)
    S.append(v)


def DFSprint(v, visited, graph,tabela):
    visited[v] = True
    tabela.append(int(v))
    print(str(v) + " ", end='')
    for u in range(len(graph[v])):
        if graph[v][u] == 1 and not visited[u]:
            DFSprint(u, visited, graph,tabela)


def transpose(graph):
    temp = [[] for _ in range(len(graph[0]))]
    for i in range(len(graph[0])):
        for j in range(len(graph)):
            temp[i].append(graph[j][i])
    return temp

tabela2 = []

def kosaraju(nodes, graph):
    global tabela2
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
        DFSprint(v, visited, graph,tabela)
        if(len(tabela)>len(tabela2)):
            tabela2 = tabela[:]
        print('\n')

def makegraphof(graph_matr,tabela2):

    listawierzcholkow = { j:i for i,j in enumerate(tabela2)}
    
    #print(listawierzcholkow)

    new_matr = [[0 for _ in range(len(listawierzcholkow))] for _ in range(len(listawierzcholkow))]

    for j in range(len(graph_matr)):
        for indeks in range(len(graph_matr[0])):
            if graph_matr[j][indeks] == 1:
                if indeks in listawierzcholkow and j in listawierzcholkow:
                    new_matr[listawierzcholkow[j]][listawierzcholkow[indeks]] = 1

    return new_matr


def bellmanford(graph_matr,starting_point_number):
    d = [999 for _ in range(len(graph_matr))]
    p = [-1 for _ in range(len(graph_matr))]
    d[starting_point_number] = 0;

    for i in range(2,len(graph_matr)+1):
        test = True
        for x in range(len(graph_matr)):
            for y in range(len(graph_matr)):
                if graph_matr[x][y] != 0:
                    if d[y]<=(d[x]+graph_matr[x][y]):
                        continue
                    else:
                        test = False
                        d[y] = d[x]+graph_matr[x][y]
                        p[y] = x
        if test:
            return (True,d,p)

    for x in range(len(graph_matr)):
                for y in range(len(graph_matr)):
                    if graph_matr[x][y] != 0:
                        if d[y] > (d[x] + graph_matr[x][y]):
                            return (False,d,p)
    return (True,d,p)


#losowanie

print("Podaj wielkość grafu źródłowego")

length = int(input())

graph_matr = [[0 for _ in range(length)] for _ in range(length)]

for i in range(len(graph_matr)):
    for j in range(len(graph_matr[i])):
        graph_matr[i][j] = random(2)
        if i == j:
            graph_matr[i][j] = 0

for k in graph_matr:
    print(k)
print('')

kosaraju(len(graph_matr), graph_matr)

tmptab = [x+1 for x in tabela2]

print("Digraf silnie spójny zostanie utworzony z wierzchołków o numerach:",tmptab,"\n")

print("Oto on:")

graph_new = makegraphof(graph_matr,tabela2)

for k in graph_new:
    print(k)

with open("adjMat.txt","w") as zapis:
    zapis.write(str(len(graph_new[0]))+' '+str(len(graph_new[0]))+'\n')
    for x in graph_new:
        for y in x:
            zapis.write(str(y)+' ')
        zapis.write('\n')


print("\nPrzypisano losowe wagi krawędziom:")

for x in graph_new:
    for y in range(len(x)):
        if x[y] == 1:
            x[y] = random(1,11)
            if(random(14)%7 == 0):
                x[y] = random(-5,-1)

for k in graph_new:
    print(k)

print("\nPodaj wierzchołek startowy dla Bellmana-Forda:",end=' ')

starting_point_number = int(input())

wynik = bellmanford(graph_new,starting_point_number-1)

print("\nWynik:")

if(wynik[0]):
    print("Udało się odnaleźć najkrótsze ścieżki")
    print("Tablice kosztów dojścia do wierzchołka n z wierzchołka",starting_point_number,"\n")
    print([(i+1,k) for i,k in enumerate(wynik[1])])
    print([(i+1,k+1) for i,k in enumerate(wynik[2])])
    print("\nŚcieżki:\n")
    lista = [[] for _ in range(len(graph_new))]
    for k in range(len(graph_new)):
        current = k
        while current != -1:
            lista[k].append(current)
            current = wynik[2][current]
        counter = 0
        for l in reversed(lista[k]):
            if counter != 0:
                print("->",l+1,sep='',end='')
            else:
                print(l+1,sep='',end='')
                counter = 1
        print('\n')


else:
    print("Wystąpił cykl ujemny, istnieje dowolnie tania ścieżka")
