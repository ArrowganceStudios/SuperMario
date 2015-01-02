CXX=g++
CFLAGS=-std=c++11
LDFLAGS=$$(pkg-config --cflags --libs allegro-5.0 allegro_image-5.0 allegro_primitives-5.0)
INCLUDE=-I$(SRC)/.

BIN=./bin
SRC=./src
ASSETS=./assets
OUT=$(BIN)/Mario
OBJS=$(BIN)/Objects.o $(BIN)/Player.o $(BIN)/Map.o $(BIN)/GameStates.o $(BIN)/Game.o $(BIN)/TileManager.o $(BIN)/SpriteManager.o $(BIN)/GameManager.o $(BIN)/main.o

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
