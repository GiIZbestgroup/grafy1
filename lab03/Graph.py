from random import randint


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

        for row in self.adjacencyMatrix:
            for pos in row:
                if pos:
                    self.edges += 1

    def set_values(self, min, max):
        i = 0
        for row in self.adjacencyMatrix:
            self.valueMatrix.append([])
            for pos in row:
                if int(pos):
                    self.valueMatrix[i].append(randint(min, max))
                else:
                    self.valueMatrix[i].append(0)
            i += 1

    def show(self):
        for row in self.adjacencyMatrix:
            print("| ", end="")
            for pos in row:
                print(pos, " ", end="")
            print("|\n", end="")

    def show_value(self):
        for row in self.valueMatrix:
            print("| ", end="")
            for pos in row:
                print(pos, " ", end="")
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
            for neighbour in self.valueMatrix[neigh_queue[q_index]]:
                if neighbour:
                    #Jesli sasiada nie ma w kolejce to dodajemy go
                    if j not in neigh_queue:
                        neigh_queue.append(j)
                    #Jezeli dotychczasowy dystans do sasiada jest wiekszy niz
                    #dystans do aktualnie badanego wierzcholka + waga do sasiada
                    if dijkstra_tab[j][0] > dijkstra_tab[neigh_queue[q_index]][0] + neighbour:
                        dijkstra_tab[j][0] = dijkstra_tab[neigh_queue[q_index]][0] + neighbour
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
            print("Odleglosc z", node, "do", i, "wynosi:", distance)
            print("Sciezka:", node, "--> ", end="")
            for i in range(len(path) - 2):
                print(path[(len(path) - 2) - i], "--> ", end="")
            print(path[0], end="\n\n")

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
                print(distance, " ", end="")
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

    def get_mst(self):
        pass