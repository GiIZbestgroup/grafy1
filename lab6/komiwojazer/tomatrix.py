#!/usr/bin/env python3

from math import sqrt

def giveDistance(point1,point2):
	return sqrt( pow(point1[1]-point2[1],2) + pow(point1[2]-point2[2],2))

with open("komiwojazer2.dat","r") as data_raw:
	data = []
	for row in data_raw:
		data.append([int(k) for k in row.strip('\n\r').split(' ') if k!=' ' and k!='' and k!='\n'])

print("Wczytano dane:")

for t in range(len(data)):
	print(data[t])
	data[t][0] -= 1

adjMat = [ [0 for _ in range(len(data))] for _ in range(len(data))]


for i in range(len(data)):
	for j in range(len(data)):
		adjMat[i][j] = giveDistance(data[i],data[j])

for t in adjMat:
	print(t)

with open("adjMat.txt","w") as zapis:
	zapis.write(str(len(adjMat[0]))+' '+str(len(adjMat[0]))+'\n')
	for x in adjMat:
		print(sum(x),end=' ')
		for y in x:
			zapis.write(str(y)+' ')
		zapis.write('\n')