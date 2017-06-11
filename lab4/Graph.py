from random import randint, randrange


class Graph:
    def __init__(self):
        self.adjacencyMatrix = []
        self.valueMatrix = []
        self.nodes = 0
        self.edges = 0

    def from_file(self, path):
        new_file = open(path, "r")

        self.nodes = int(new_file.readline().split(" ")[0])

        i = 0
        data = new_file.readlines()
        for row in data:
            self.adjacencyMatrix.append([])
            for pos in row.split(" "):
                if not pos == '\n':
                    self.adjacencyMatrix[i].append(int(pos))
            i += 1

        new_file.close()

        for row in self.adjacencyMatrix:
            for pos in row:
                if pos:
                    self.edges += 1

    def set_values(self, min, max):
        i = 0
        #Gdy krawedz istnieje to przypisujemy losowa wage z zakresu min, max
        for row in self.adjacencyMatrix:
            self.valueMatrix.append([])
            for pos in row:
                if int(pos):
                    if(randrange(90)%15==0):
                        self.valueMatrix[i].append(randint(min, 0))
                    else:
                        self.valueMatrix[i].append(randint(0, max))
                else:
                    self.valueMatrix[i].append(0)
            i += 1

        #Gdy chcemy uzyskac graf nieskierowany
#        for i in range(self.nodes):
#            for j in range(i, self.nodes):
#                self.valueMatrix[j][i] = self.valueMatrix[i][j]

    def show(self):
        for row in self.adjacencyMatrix:
            print("| ", end="")
            for pos in row:
                print(pos, "", end="")
            print("|\n", end="")

    def show_value(self):
        for row in self.valueMatrix:
            print("| ", end="")
            for pos in row:
                print(pos, "", end="")
            print("|\n", end="")

    def dijkstra(self, node):
        #Przygotowujemy tablice (dystans, poprzednik)
        dijkstra_tab = [[999, -1] for _ in range(self.nodes)]
        dijkstra_tab[node][0] = 0

        #Kolejka sasiadow
        neigh_queue = [node]
        q_index = 0

        while q_index < len(neigh_queue):
            j = 0
            for neighbour in range(len(self.valueMatrix[neigh_queue[q_index]])):
                if self.adjacencyMatrix[neigh_queue[q_index]][neighbour]:
                    #Jesli sasiada nie ma w kolejce to dodajemy go
                    if j not in neigh_queue:
                        neigh_queue.append(j)
                    #Jezeli dotychczasowy dystans do sasiada jest wiekszy niz
                    #dystans do aktualnie badanego wierzcholka + waga do sasiada
                    if dijkstra_tab[j][0] > dijkstra_tab[neigh_queue[q_index]][0] + self.valueMatrix[neigh_queue[q_index]][neighbour]:
                        dijkstra_tab[j][0] = dijkstra_tab[neigh_queue[q_index]][0] + self.valueMatrix[neigh_queue[q_index]][neighbour]
                        dijkstra_tab[j][1] = neigh_queue[q_index]
                j += 1
            #Bedziemy sprawdzac nastepnego sasiada z kolejki
            q_index += 1

            #Odkomentowac jezeli chcemy sprawdzic stan tabel w kolejnych iteracjach
            #print(dijkstra_tab)

        #Zwracamy tablice dijkstry do innych metod
        return dijkstra_tab

    def show_dijkstra_tab(self, node, dijkstra_tab):
        #Ustalamy sciezki + dlugosci
        for i in range(self.nodes):
            path = []
            distance = dijkstra_tab[i][0]
            prev = i
            #Jezeli jest jeszcze poprzednik
            #czyli nie dotarlismy do punktu startowego
            while not prev == -1:
                path.append(prev)
                prev = dijkstra_tab[prev][1]

            #Wypisujemy
            if distance == 999:
                print("Brak sciezki z", node+1, "do", i+1)
            else:
                print("Odleglosc z", node+1, "do", i+1, "wynosi:", distance)
                print("Sciezka:", node+1, "--> ", end="")

                for i in range(len(path) - 2):
                    print(path[(len(path) - 2) - i]+1, "--> ", end="")
            print(path[0]+1, end="\n\n")



    def get_minimal_distances(self):
        #Tworzymy pusta macierz odleglosci
        distance_matrix = []
        #Dla kazdego wierzcholka robimy dijkstre
        for node in range(self.nodes):
            distance_matrix.append([])
            dijkstra_tab = self.dijkstra(node)
            #Z otrzymanych tablic odczytujemy i przepisujemy odleglosci
            for data in dijkstra_tab:
                distance_matrix[node].append(data[0])

        return distance_matrix

    def show_minimal_distances(self, distance_matrix):
        for node in distance_matrix:
            print("| ", end="")
            for distance in node:
                if distance == 999:
                    distance = "X"
                print(distance, "", end="")
            print("|\n", end="")
        print(end="\n")

    def get_centre(self, distance_matrix):
        minimal_distance_sum = sum(distance_matrix[0])
        centre = 0

        it = 0
        #Szukamy minimalnej sumy po wierszach macierzy
        for node in distance_matrix:
            if sum(node) < minimal_distance_sum:
                minimal_distance_sum = sum(node)
                centre = it
            it += 1

        #Zwracamy krotke (centrum, suma_dystansow)
        return centre, minimal_distance_sum

    def show_centre(self, data):
        print("Centrum grafu:", data[0])
        print("Suma odleglosci do pozostalych wierzcholkow:", data[1])
        print(end="\n")

    def get_minimax(self, distance_matrix):
        min_max_distance = max(distance_matrix[0])
        minimax = 0

        it = 0
        #Szukamy minimalnej najwiekszej odleglosci po wierszach macierzy
        for node in distance_matrix:
            if max(node) < min_max_distance:
                min_max_distance = max(node)
                minimax = it
            it += 1

        # Zwracamy krotke (centrum_minimax, najdluzszy_dystans)
        return minimax, min_max_distance

    def show_minimax(self, data):
        print("Centrum minimax grafu:", data[0])
        print("Najdluzsza odleglosc:", data[1])
        print(end="\n")

    def prim(self):
        #Tworzymy pusta liste odwiedzonych wierzcholkow i wybieramy startowy
        visited = []
        visited.append(0)

        #Tworzymy macierz sasiedztwa dla drzewa rozpinajacego
        mst_three_matrix = [[0 for _ in range(self.nodes)] for _ in range(self.nodes)]

        #Dopoki nie odwiedzilismy wszystkich wierzcholkow
        while not len(visited) == self.nodes:
            #Szukamy najkrotszej krawedzi
            data = self.get_minimal_edge(visited)
            #Wpisujemy do macierzy
            mst_three_matrix[data[1]][data[2]] = data[0]
            mst_three_matrix[data[2]][data[1]] = data[0]
            #Dodajemy nowy wierzcholek do listy odwiedzonych
            visited.append(data[2])

        #Zwracamy macierz sasiedztwa minimalnego drzewa rozpinajacego
        return mst_three_matrix

    def get_minimal_edge(self, nodes):
        #Przyjmuje sobie jakas poczatkowa "nieskonczona" wage
        min_edge = (999999, -1, -1)
        #Idac po wierzcholkach w liscie dostepnych
        for node in nodes:
            j = 0
            for edge in self.valueMatrix[node]:
                #Jezeli krawedz istnieje, jest mniejsza, niz aktualna minimalna
                #oraz nie laczy z wierzcholkiem, do ktorego juz mamy polaczenie
                if edge and edge < min_edge[0] and j not in nodes:
                    #Przepisujemy wartosc
                    #Krotka (waga, z, dokad (NOWY WIERZCHOLEK))
                    min_edge = (edge, node, j)
                j += 1
        return min_edge

    def show_mst(self, mst_matrix):
        for node in mst_matrix:
            print("| ", end="")
            for distance in node:
                print(distance, "", end="")
            print("|\n", end="")
        print(end="\n")
        print("Waga drzewa:", sum([sum(row) for row in mst_matrix])//2, end="\n")
        print(end="\n")
