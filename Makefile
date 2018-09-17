CC=g++-5
LFLAGS=-lcrypto -lpthread -lssl
CFLAGS=-std=c++11 -Wall

all:
	mkdir src/o
	$(CC) $(CFLAGS) -c src/game.cpp -o src/o/game.o $(LFLAGS)
	$(CC) $(CFLAGS) -c src/server.cpp -o src/o/server.o $(LFLAGS)
	$(CC) $(CFLAGS) -c src/nanny.cpp -o src/o/nanny.o $(LFLAGS)
	$(CC) $(CFLAGS) -c src/playermanager.cpp -o src/o/playermanager.o $(LFLAGS)
	$(CC) $(CFLAGS) -c src/command.cpp -o src/o/command.o $(LFLAGS)
	$(CC) $(CFLAGS) -c src/areamanager.cpp -o src/o/areamanager.o $(LFLAGS)
	$(CC) $(CFLAGS) -c src/util.cpp -o src/o/util.o $(LFLAGS)
	$(CC) $(CFLAGS) -c src/area.cpp -o src/o/area.o $(LFLAGS)
	$(CC) $(CFLAGS) -c src/player.cpp -o src/o/player.o $(LFLAGS)
	$(CC) $(CFLAGS) -c src/item.cpp -o src/o/item.o $(LFLAGS)
	$(CC) $(CFLAGS) -c src/itemmanager.cpp -o src/o/itemmanager.o $(LFLAGS)
	$(CC) $(CFLAGS) -c src/help.cpp -o src/o/help.o

	$(CC) -o game \
		src/o/game.o \
		src/o/server.o \
		src/o/nanny.o \
		src/o/command.o \
		src/o/util.o \
		src/o/player.o \
		src/o/playermanager.o \
		src/o/area.o \
		src/o/areamanager.o \
		src/o/item.o \
		src/o/itemmanager.o \
		src/o/help.o \
		$(LFLAGS)
clean:
	rm -rf src/o

test:
	$(CC) $(CFLAGS) -o src/tests/player_test src/player.cpp src/tests/player_test.cpp $(LFLAGS)
	./src/tests/player_test
