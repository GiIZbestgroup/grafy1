#!/usr/bin/env python3

from random import randrange
import sys

def transpose(graph):
    temp = [[] for _ in range(len(graph[0]))]
    for i in range(len(graph[0])):
        for j in range(len(graph)):
            temp[i].append(graph[j][i])
    return temp

def createRandTabOfNumbers(layers):
	return [randrange(2,layers+1) for _ in range(layers)]

def createGraphMatrix(verticesTab):
	return [[0 for _ in range(sum(verticesTab)+2)] for _ in range(sum(verticesTab)+2) ]


def fillMatrix(graphMatrix,verticesInLayers,probability):

	for k in range(len(graphMatrix)):
		for l in range(len(graphMatrix[0])):
			graphMatrix[k][l] = 0

	layersDone = 0
	for k in range(verticesInLayers[0]):
		graphMatrix[0][k+1] = 1
	layersDone += 1

	verticesDone = 1

	for k in range(len(verticesInLayers)-1):
		for i in range(layersDone,layersDone+verticesInLayers[k]):
			assignededge = False
			while not assignededge:
				for j in range(layersDone+verticesInLayers[k],layersDone+verticesInLayers[k]+verticesInLayers[k+1]):
					graphMatrix[i][j] = int((randrange(101)<=probability))
					if graphMatrix[i][j]:
						assignededge = True
			verticesDone += 1
		layersDone += verticesInLayers[k]

	for k in range(verticesInLayers[len(verticesInLayers)-1]):
		graphMatrix[len(graphMatrix[0])-2-k][len(graphMatrix[0])-1] = 1



def graphIsCorrect(filledGraph):
	
	isCorrect = True

	for row in range(1,len(filledGraph)-1):
		if(sum(filledGraph[row])==0):
			isCorrect = False

	transposedGraph = transpose(filledGraph)

	for row in range(1,len(transposedGraph)-1):
		if(sum(transposedGraph[row])==0):
			isCorrect = False

	return isCorrect

def sumGraph(graph):

	suma = 0

	for k in graph:
		suma += sum(k)

	return suma

def addRandomEdges(canAddBackwardsIfAlreadyExistForwardEdge,graphMatrix,howmany):

	counter = 0

	if canAddBackwardsIfAlreadyExistForwardEdge:
		while counter < howmany and sumGraph(graphMatrix) < len(graphMatrix)*(len(graphMatrix)-2):
			number_x = randrange(1,len(graphMatrix)-1)
			number_y = randrange(1,len(graphMatrix)-1)
			if (graphMatrix[number_x][number_y] == 0) and (number_x != number_y):
				graphMatrix[number_x][number_y] = 1
				counter += 1
	else:
		while counter < howmany and sumGraph(graphMatrix) < (len(graphMatrix)-2)/2*(len(graphMatrix)-2):
			number_x = randrange(1,len(graphMatrix)-1)
			number_y = randrange(1,len(graphMatrix)-1)
			if (graphMatrix[number_x][number_y] == 0 and graphMatrix[number_y][number_x] == 0) and (number_x != number_y):
				graphMatrix[number_x][number_y] = 1
				counter += 1


def saveGraph(graphMatrix,verticesInLayers,name):

	with open(name,"w") as zapis:
				zapis.write(str(len(graphMatrix[0]))+' '+str(len(graphMatrix[0]))+' '+str(len(verticesInLayers))+'\n')
				for x in verticesInLayers:
					zapis.write(str(x)+' ')
				zapis.write('\n')

				for x in graphMatrix:
					for y in x:
						zapis.write(str(y)+' ')
					zapis.write('\n')

	print("Zapisano graf w postaci macierzy sąsiedztwa następującym pliku:",name,'\n')


def addRandomWeight(graphMatrix):

	for k in range(len(graphMatrix)):
		for l in range(len(graphMatrix[0])):
			if graphMatrix[k][l]:
				graphMatrix[k][l] = randrange(1,11)



#główne ciało programu

print("Podaj liczbę warstw pośrednich: ",sep ='',end ='')

layers = int(input())

verticesInLayers = createRandTabOfNumbers(layers)

print("Liczby wierzchołków w warstwach pośrenich: ",verticesInLayers,"\nSuma wierzchołków warstw pośrednich = ",sum(verticesInLayers),"\n",sep='')

graphMatrix = createGraphMatrix(verticesInLayers)

print("Macierz",len(graphMatrix),"x",len(graphMatrix[0]),'\n')

print("1 - zapisz przed dodaniem losowych 2N krawędzi\n2 - zapisz po dodaniu 2N krawędzi, ale przed dodaniem wag\n3 - zapisz z wagami \n")

decision = int(input())

print()

while(not graphIsCorrect(graphMatrix)):
	fillMatrix(graphMatrix,verticesInLayers,50)

suma = 0

for k in graphMatrix:
	print(k)
	suma += sum(k)

print("\nOgólna liczba krawędzi przed dodaniem losowych: ",suma,'\n',sep='')

if decision == 1:
	saveGraph(graphMatrix,verticesInLayers,"adjMat.txt")
	sys.exit(0)

print("Czy dopuszczamy generowanie łuków pomiędzy wierzchołkami, między którymi istnieje łuk, ale w drugą stronę przy generowaniu losowych?(y/n): ",end='')

decision2 = input()

print()

if decision2 == 'y':
	decision2 = True
if decision2 == 'n':
	decision2 = False

addRandomEdges(decision2,graphMatrix,2*layers)

suma = 0

for k in graphMatrix:
	print(k)
	suma += sum(k)

print("\nOgólna liczba krawędzi po dodaniu losowych: ",suma,'\n',sep='')

if decision == 2:
	saveGraph(graphMatrix,verticesInLayers,"adjMat.txt")
	sys.exit(0)

addRandomWeight(graphMatrix)

print("Macierz po dodaniu losowych przepustowości z przedziału [1,10]:",'\n')

for k in graphMatrix:
	print(k)

print('')

if decision == 3:
	saveGraph(graphMatrix,verticesInLayers,"adjMat.txt")
	sys.exit(0)
