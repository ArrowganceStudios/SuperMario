CXX=g++
CFLAGS=-std=c++11
LDFLAGS=$$(pkg-config --cflags --libs allegro-5.0 allegro_image-5.0 allegro_primitives-5.0)
INCLUDE=-I$(SRC)/.

BIN=./bin
SRC=./src
OUT=$(BIN)/Mario
OBJS=$(BIN)/object.o $(BIN)/player.o $(BIN)/map.o $(BIN)/game.o $(BIN)/tilemanager.o $(BIN)/gamemanager.o $(BIN)/main.o

all: $(OUT)

$(OUT): $(OBJS)
	$(CXX) $(OBJS) -o $(OUT) $(INCLUDE) $(CFLAGS) $(LDFLAGS)

$(BIN)/%.o: $(SRC)/%.cpp
	$(CXX) $(CFLAGS) $< -c -o $@

clean:
	rm -rf $(BIN)/*o $(OUT) doc

doc:
	doxygen

