CC = g++
TARGET = quick
CFLAGS = -c -Wall -std=c++11
LDFLAGS = 
OBJS = parser.o tokenizer.o ast.o scope.o variable_mgr.o main.o

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o$@

%.o: %.cpp
	$(CC) $(CFLAGS) $< -o$@

clean:
	rm *.o
	rm quick*
