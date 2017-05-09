from Graph import Graph
from GraphGenerator import GraphGenerator


print("#####################")
print("#  Program: Lab 03  #")
print("#####################")
print("Autorzy:")
print("Daria Siemieniuk")
print("Pawel Talaga")
print("Milosz Swierad")
print("Kamil Turek")
print()
print("AGH WFiIS IS 2017")
print()

try:
    print("Podaj liczbe wierzcholkow:")
    nodes = int(float(input()))
    while nodes < 3:
        print("Zbyt mala liczba wierzcholkow! Podaj inna:")
        nodes = int(input())
except:
    print("Podana zla liczbe wierzcholkow! Przyjeto domyslnie 5")
    nodes = 5

generator = GraphGenerator()
generator.generate(nodes)
generator.to_file("graph.txt")

graph = Graph()
graph.from_file("graph.txt")
graph.set_values(1, 10)

print("Co chcesz zrobic?")
print("1 - Wypisac wszystkie dane")
print("2 - Wypisac dane bez macierzy (gdy liczba wierzcholkow jest duza)")
print("0 - Wyjsc")

try:
    choice = int(float(input()))
except:
    print("Niepoprawny wybor, program zakonczy sie.")
    choice = 0

while(choice):
    if(choice == 1):
        print("################################################################\n")

        print("Wygenerowany, losowy graf spojny")
        graph.show()
        print()

        print("Graf wazony")
        graph.show_value()
        print()

        print("################################################################\n")

        print("Najkrotsze sciezki z wierzcholka 0")
        graph.show_dijkstra_tab(0, graph.dijkstra(0))

        minimal_distances = graph.get_minimal_distances()

        print("################################################################\n")

        print("Macierz odleglosci pomiedzy wierzcholkami")
        graph.show_minimal_distances(minimal_distances)

        print("################################################################\n")

        graph.show_centre(graph.get_centre(minimal_distances))
        graph.show_minimax(graph.get_minimax(minimal_distances))

        print("################################################################\n")

        print("Minimalne drzewo rozpinajace (MST)")
        graph.show_mst(graph.prim())

        print("################################################################\n")

        print("Co chcesz zrobic?")
        print("1 - Wypisac wszystkie dane")
        print("2 - Wypisac dane bez macierzy (gdy liczba wierzcholkow jest duza)")
        print("0 - Wyjsc")

        try:
            choice = int(float(input()))
        except:
            print("Niepoprawny wybor, program zakonczy sie.")
            choice = 0

    elif(choice == 2):
        print("################################################################\n")

        print("Najkrotsze sciezki z wierzcholka 0")
        graph.show_dijkstra_tab(0, graph.dijkstra(0))

        minimal_distances = graph.get_minimal_distances()

        print("################################################################\n")

        graph.show_centre(graph.get_centre(minimal_distances))
        graph.show_minimax(graph.get_minimax(minimal_distances))

        print("################################################################\n")

        print("Co chcesz zrobic?")
        print("1 - Wypisac wszystkie dane")
        print("2 - Wypisac dane bez macierzy (gdy liczba wierzcholkow jest duza)")
        print("0 - Wyjsc")

        try:
            choice = int(float(input()))
        except:
            print("Niepoprawny wybor, program zakonczy sie.")
            choice = 0

    elif(choice == 0):
        pass
    else:
        print("Zly wybor! 2\Co chcesz zrobic?")
        print("1 - Wypisac wszystkie dane")
        print("2 - Wypisac dane bez macierzy (gdy liczba wierzcholkow jest duza)")
        print("0 - Wyjsc")

        try:
            choice = int(float(input()))
        except:
            print("Niepoprawny wybor, program zakonczy sie.")
            choice = 0




