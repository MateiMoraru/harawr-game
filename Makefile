LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

main:
	@echo "Time took for compiling:"
	@/usr/bin/time -f "%e" g++ src/*.cpp -o bin/main.exe -Iheaders $(LIBS)

	@echo "\n\n"
	@echo "Running game:\n"

run: main
	@./bin/main.exe
