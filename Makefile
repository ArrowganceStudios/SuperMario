CXX	= $(CROSS)g++
PKG	= $(CROSS)pkg-config
ALLEG	= allegro-5 allegro_font-5 allegro_ttf-5 allegro_image-5 allegro_primitives-5
LDFLAGS	= $(LDFLAGS_CUSTOM) $$($(PKG) --libs $(ALLEG))
CFLAGS	= $(CFLAGS_CUSTOM) $$($(PKG) --cflags $(ALLEG)) -std=c++11

BIN	= ./bin
SRC	= ./src
ASSETS	= ./assets
OUT	= $(BIN)/Mario
OBJS	= $(BIN)/Objects.o $(BIN)/Player.o $(BIN)/Map.o $(BIN)/GameStates.o $(BIN)/Game.o $(BIN)/TileManager.o $(BIN)/SpriteManager.o $(BIN)/SplashScreenManager.o $(BIN)/GameManager.o $(BIN)/main.o

all: prebuild $(OUT)

$(OUT): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(CFLAGS) $(LDFLAGS)

$(BIN)/%.o: $(SRC)/%.cpp
	$(CXX) $(CFLAGS) $< -c -o $@

prebuild:
	mkdir -p $(BIN)
	cp -r $(ASSETS) $(BIN)

clean:
	rm -rf $(BIN)/*o $(BIN)/$(ASSETS) $(OUT) doc

doc:
	doxygen
