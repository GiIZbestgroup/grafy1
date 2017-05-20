#!/usr/bin/env python3

with open('sequence.txt','r') as sekwencja_plik:

	#Wyciaganie sekwencji z pliku i przerabianie do
	#potrzebnego formatu
	sekwencja_string = sekwencja_plik.read().strip()
	sekwencja_lista_str = list(sekwencja_string.split())
	sekwencja_lista = [ [k,int(x)] for k,x in enumerate(sekwencja_lista_str,start=1)]
	print("Sekwencja w pliku:",sekwencja_string)
	print("Wczytano sekwencję (numer wierzcholka,stopien):")
	print(sekwencja_lista)
			
	#Algorytm sprawdzania
	
	#Sortowanie wzgledem stopni wierzcholkow
	#czyli drugich elementow list
	#[a,b] <- lista  dwuelementowa
	sekwencja_lista.sort(key = lambda x: x[1])
	
	#Pusta macierz sasiedztwa
	adjMat = [[0 for x in range(len(sekwencja_lista))] for y in range(len(sekwencja_lista))]

	length = len(sekwencja_lista)-1

	while length>0:
		
		sekwencja_lista.sort(key = lambda x: x[1])
		element = sekwencja_lista.pop()		
		
		falseflag = False
		
		counter = length - 1

		while True:
			print(sekwencja_lista)
			
			if sekwencja_lista[counter][1]>0 and element[1] != 0 and counter>=0:
				element[1] -= 1
				sekwencja_lista[counter][1] -= 1
				print(element[0],sekwencja_lista[counter][0])
				adjMat[element[0]-1][sekwencja_lista[counter][0]-1] = 1
				adjMat[sekwencja_lista[counter][0]-1][element[0]-1] = 1
			elif element[1] == 0:
				break
			else:
				falseflag = True
				break
			counter -= 1
				
		if falseflag:
			break

		length -= 1
	
	#Jesli ciag jest graficzny to zapisuje do pliku jego macierz sasiedztwa
	if not falseflag:
		print("Ciag jest graficzny")
		with open("adjMat.txt","w") as zapis:
			zapis.write(str(len(adjMat[0]))+' '+str(len(adjMat[0]))+'\n')
			for x in adjMat:
				for y in x:
					zapis.write(str(y)+' ')
				zapis.write('\n')
	else:
		print("Ciag nie jest graficzny")
