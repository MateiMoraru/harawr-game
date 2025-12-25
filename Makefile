CXX = g++
CXXFLAGS = -std=c++20 -O2 -Iheaders -IC:/SFML/include
LDFLAGS = -LC:/SFML/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

SRC = src/*.cpp
OUT = bin/main.exe

all:
	$(CXX) $(SRC) -o $(OUT) $(CXXFLAGS) $(LDFLAGS)

clean:
	rm -f $(OUT)