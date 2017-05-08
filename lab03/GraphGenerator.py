from random import randint


class GraphGenerator:
    def __init__(self):
        self.matrix = []
        self.nodes = 0
        self.edges = 0

    def generate(self, nodes):
        #Okreslamy liczbe wierzcholkow i tworzymy odpowiednia macierz wypelniona zerami
        self.nodes = nodes
        self.matrix = [[0 for _ in range(self.nodes)] for _ in range(self.nodes)]

        #Okreslamy max liczbe krawedzi i losujemy liczbe krawedzi z zakresu [nodes - 1, max]
        max_edges = self.nodes * (self.nodes - 1) / 2
        self.edges = randint(self.nodes - 1, max_edges)

        #Przygotowujemy sie do stwozenia ST
        used_edges = [0]
        edge_counter = 0

        #Tworzymy ST (czyli graf spojny)
        while not edge_counter == self.nodes - 1:
            used_edges.append(self.build_tree(used_edges))
            edge_counter += 1

        #Dodajemy losowo pozostale krawedzie
        for i in range(edge_counter, self.nodes):
            while True:
                #Strzelamy koordynaty, jezeli nie maa tam krawedzi to dopisujemy
                #Jesli jest to probujemy do skutku
                shot = (randint(0, self.nodes - 1), randint(0, self.nodes - 1))
                if not self.matrix[shot[0]][shot[1]] and not shot[0] == shot[1]:
                    self.matrix[shot[0]][shot[1]] = 1
                    self.matrix[shot[1]][shot[0]] = 1
                    break

    def build_tree(self, used_edges):
        while True:
            #Strzelamy wierzcholek
            shot = randint(0, self.nodes - 1)
            #Jezeli nie dodalismy go jeszcze, strzelamy wierzcholek z uzytych (used_shot)
            #i do niego dolaczamy nowy strzelony (shot)
            #Jesli nie trafimy to strzelamy do skutku
            if shot not in used_edges:
                used_shot = randint(0, len(used_edges) - 1)
                self.matrix[used_edges[used_shot]][shot] = 1
                self.matrix[shot][used_edges[used_shot]] = 1
                return shot

    def to_file(self, path):
        new_file = open(path, "w")

        print(self.nodes, 0, file=new_file)
        for row in self.matrix:
            for pos in row:
                print(pos, end=' ', file=new_file)
            print(file=new_file)

        new_file.close()
