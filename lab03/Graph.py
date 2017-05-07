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
        pass

    def get_centre(self):
        pass

    def get_minimax(self):
        pass

    def get_mst(self):
        pass