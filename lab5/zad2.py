#!/usr/bin/env python3

from random import randrange
from collections import deque as doublequeue

def transpose(graph):
    temp = [[] for _ in range(len(graph[0]))]
    for i in range(len(graph[0])):
        for j in range(len(graph)):
            temp[i].append(graph[j][i])
    return temp


def BFS(graph,parent,source,sink):

	visitedlist = [False for _ in range(len(graph))]
	priorityqueue = doublequeue()
	priorityqueue.append(source)
	visitedlist[source] = True

	while len(priorityqueue)>0:

		last_vertice = priorityqueue.popleft()
		for i,value in enumerate(graph[last_vertice]):
			if value > 0 and visitedlist[i]==False:
				priorityqueue.append(i)
				visitedlist[i] = True
				parent[i] = last_vertice

	return visitedlist[sink]




def Fulkerson(graph,source,sink):

	parent = [None for _ in range(len(graph))]
	maximalFlow = 0

	while BFS(graph,parent,source,sink):

		maximalFlowCurrentPath = 99999999
		vertice = sink
		while vertice != source:
			maximalFlowCurrentPath = min(maximalFlowCurrentPath,graph[parent[vertice]][vertice])
			vertice = parent[vertice]
		maximalFlow += maximalFlowCurrentPath

		vertice = sink
		while vertice != source:
			graph[parent[vertice]][vertice] -= maximalFlowCurrentPath
			graph[vertice][parent[vertice]] += maximalFlowCurrentPath
			vertice = parent[vertice]

	return maximalFlow




path = input("\nPodaj sciezke pliku: ")
graph = open(path, "r+")
t = graph.readline()
graph.readline()
graph_matr = []

i = 0
data = graph.readlines()
for row in data:
    graph_matr.append([])
    for pos in row.split(" "):
        if not pos == '\n':
            graph_matr[i].append(int(pos))
    i += 1

print("\nWczytano graf:\n")
for k in graph_matr:
	print(k)


print("\nPrzepływ maksymalny:",Fulkerson(graph_matr,0,len(graph_matr)-1),"\n")

