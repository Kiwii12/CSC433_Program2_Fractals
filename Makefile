CC = g++
LIBS  = -lGL -lglut -lGLU
FLAGS = -std=c++11
EXECS = fractals

all: $(EXECS)

fractals: Main.o Fractals.o DrawingManager.o View.o Fractal.o Line.o
	$(CC) $(FLAGS) -o $@ $? $(LIBS)

clean:
	$(RM) $(EXECS)
