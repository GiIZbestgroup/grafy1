# ustawiamy kompilator
CXX=g++
# ustawiamy flagi do kompilacji
CXXFLAGS+= -Wall -O0 $(GXX_FLAGS) -g

# ustawiamy flagi dla kompilatora, żeby automatycznie wygenerował zależności
DEP_FLAGS=-MMD -MP

# pobieramy wszystkie pliki z rozszerzeniem .cpp z folderu w którym jest makefile
SRC=$(wildcard *.cpp)
# do tej zmiennej zapisujemy nazwy plików obiektowych jakie mają być zrobione
OBJ=$(SRC:.cpp=.o)
#nazwy plików z zależnościami
DEP=$(OBJ:.o=.d)

#nazwa programu
NAME = main

#nazwa folderu dla plików obiektowych i zależności
OBJDIR := obj

#tworzymy listę plików obiektowych z odpowiednim adresem
OBJS := $(addprefix $(OBJDIR)/,$(OBJ))




# dopisujemy flagi do znajdowania zależności
CXXFLAGS+=$(DEP_FLAGS)


# najpierw upewniamu się czy mamy folder na pliki obiektowe, potem kompilujemy
all: $(OBJDIR) $(NAME)

# to chyba jasne main zależy od plików obiektowych( odpowiednia ścieżka)
# kompilacja z flagami do linkowania ( domyślnie ustawione) wszystkie pliki obiektowe i generuj plik wynikowy do pliku o nazwie takiej jak nazwa etykiety( w tym przypadku main)	
main: $(OBJS)
	$(CXX) $(LFLAGS) $^ -o $@ -lsfml-graphics -lsfml-window -lsfml-system

# tu tworzymy pliki obiektowe i pliki zależności 
$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $*.cpp -o $@

# tworzymy katalog dla plików obiektowych
$(OBJDIR):
	mkdir $(OBJDIR)

.PHONY: clean run

# ważne żeby zadziały automatyczne zależności
-include $(OBJDIR)/$(DEP)

clean:
	@rm -rf $(NAME) obj/
run:
	./$(NAME)
gdb:
	gdb ./$(NAME)
valgrind:
	valgrind ./$(NAME)
help:
	@clear
	@echo '-----------------------------------------------------'
	@echo 'make             - kompilacja i linkowanie projektu 	'
	@echo 'make help        - wyświetla ten komunikat			'
	@echo 'make clean       - czyszczenie projektu 				'
	@echo 'make run	        - uruchamia program					'
	@echo 'make gdb	        - uruchamia gdb						'
	@echo 'make valgrind    - uruchamia valgrind 				'
	@echo '-----------------------------------------------------'
	@echo ' make tworzy osobny katalog dla plików tymczasowych  '
