CXX=g++
CFLAGS=-std=c++11
LDFLAGS=$$(pkg-config --cflags --libs allegro-5.0 allegro_image-5.0 allegro_primitives-5.0)
INCLUDE=-I$(SRC)/.

BIN=./bin
SRC=./src
ASSETS=./assets
OUT=$(BIN)/Mario
OBJS=$(BIN)/object.o $(BIN)/player.o $(BIN)/map.o $(BIN)/game.o $(BIN)/tilemanager.o $(BIN)/spritemanager.o $(BIN)/gamemanager.o $(BIN)/main.o

all: prebuild $(OUT)

$(OUT): $(OBJS)
	$(CXX) $(OBJS) -o $(OUT) $(INCLUDE) $(CFLAGS) $(LDFLAGS)

$(BIN)/%.o: $(SRC)/%.cpp
	$(CXX) $(CFLAGS) $< -c -o $@

prebuild:
	mkdir -p $(BIN)
	cp -r $(ASSETS) $(BIN)

clean:
	rm -rf $(BIN)/*o $(BIN)/$(ASSETS) $(OUT) doc

doc:
	doxygen
