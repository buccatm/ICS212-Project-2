all : project_debug project
project: llist.cpp user-interface.cpp record.h llist.h
	g++ -ansi -pedantic-errors -Wall -c llist.cpp
	g++ -ansi -pedantic-errors -Wall -c user-interface.cpp
	g++ -o project llist.o user-interface.o
project_debug: llist.cpp user-interface.cpp record.h llist.h
	g++ -DDEBUG -ansi -pedantic-errors -Wall -c llist.cpp
	g++ -DDEBUG -ansi -pedantic-errors -Wall -c user-interface.cpp
	g++ -o project_debug llist.o user-interface.o
