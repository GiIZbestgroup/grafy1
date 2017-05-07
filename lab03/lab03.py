from Graph import Graph


graph = Graph()
graph.from_file("graph.txt")
graph.set_values(1, 10)
graph.show()
print()
graph.show_value()
print()
graph.show_dijkstra_tab(0, graph.dijkstra(0))
graph.show_minimal_distances(graph.get_minimal_distances())
graph.show_centre(graph.get_centre(graph.get_minimal_distances()))
graph.show_minimax(graph.get_minimax(graph.get_minimal_distances()))