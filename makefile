CC = g++
TARGET = quick
CFLAGS = -c -Wall -std=c++11
LDFLAGS = 
OBJS = temp/ast.o temp/scope.o temp/variable_mgr.o temp/main.o

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o$@

temp/%.o: code/%.cpp
	$(CC) $(CFLAGS) $< -o$@

clean:
	rm temp/*.o
	rm quick
