CC=g++
GDB=gdb
SRC=main.cpp serial.cpp
OUT=pi-relay
CFLAGS:=

pi-relay: $(SRC)
	$(CC) $(SRC) -o $(OUT)

debug: $(SRC)
	$(CC) $(SRC) -g -o $(OUT)
	$(GDB) $(OUT)

clean:
	rm -f $(OUT)

