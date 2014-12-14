CXX=g++
CFLAGS=-std=c++11
LDFLAGS=$$(pkg-config --cflags --libs allegro-5.0 allegro_image-5.0 allegro_primitives-5.0)
INCLUDE=-I$(SRC)/.

BIN=./bin
SRC=./src
OUT=$(BIN)/Mario
OBJS=$(BIN)/main.o

all: $(OUT)

$(OUT): $(OBJS)
	$(CXX) $(OBJS) -o $(OUT) $(INCLUDE) $(CFLAGS) $(LDFLAGS)

$(BIN)/%.o: $(SRC)/%.cpp
	$(CXX) $(CFLAGS) $< -c -o $@

clean:
	rm -rf $(BIN)/*o $(OUT)

