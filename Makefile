CC := g++
CFLAGS := #-Wall -Wextra -std=c++11
TARGET := Connect4

$(TARGET): clear.cpp files.cpp functions.cpp game_mode0.cpp game_mode1.cpp game_mode2.cpp game_mode3.cpp inicial.cpp main.cpp methods.cpp Position.h solver.cpp Solver.h TranspositionTable.h
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(TARGET)
