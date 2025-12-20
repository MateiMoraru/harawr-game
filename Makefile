LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

main:
	g++ src/*.cpp -o bin/main  -Iheaders $(LIBS)

run: main
	./bin/main
