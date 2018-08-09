CC=g++-5
LFLAGS=-lcrypto -lpthread
CFLAGS=-std=c++11

all:
	mkdir src/o
	$(CC) $(CFLAGS) -c src/game.cpp -o src/o/game.o $(LFLAGS)
	$(CC) $(CFLAGS) -c src/server.cpp -o src/o/server.o $(LFLAGS)
	$(CC) $(CFLAGS) -c src/nanny.cpp -o src/o/nanny.o $(LFLAGS)
	$(CC) $(CFLAGS) -c src/playermanager.cpp -o src/o/playermanager.o $(LFLAGS)
	$(CC) $(CFLAGS) -c src/areamanager.cpp -o src/o/areamanager.o $(LFLAGS)
	$(CC) $(CFLAGS) -c src/command.cpp -o src/o/command.o $(LFLAGS)
	$(CC) $(CFLAGS) -c src/areamanager.cpp -o src/o/areamanager.o $(LFLAGS)
	$(CC) $(CFLAGS) -c src/util.cpp -o src/o/util.o $(LFLAGS)
	$(CC) $(CFLAGS) -c src/area.cpp -o src/o/area.o $(LFLAGS)

	$(CC) -o game src/o/*.o $(LFLAGS)
clean:
	rm -rf src/o
