LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

main:
	g++ src/*.cpp -o bin/main $(LIBS)

run: main
	./bin/main
