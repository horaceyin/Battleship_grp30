flag = -pedantic-errors -std=c++11

tutorial: tutorial.cpp tutorial.h
	g++ $(flag) -c $<

menu: menu.cpp menu.h tutorial.h
	g++ $(flag) -c $<

gameboard: gameboard.cpp menu.h tutorial.h
	g++ $(flag) -c $<

battleship_grp30: gameboard.o tutorial.o menu.o
	g++ $(flag) $^ -o $@
	
clean:
	rm -f battleship_grp30 gameboard.o tutorial.o menu.o

.PHONY: clean
