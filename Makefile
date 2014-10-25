CXX = g++
CXXLIBS  = -lGL -lglut -lGLU
CXXFLAGS = -std=c++11 -Wall -g
EXECS = fractals

all: $(EXECS)

fractals: Main.o Fractals.o DrawingManager.o View.o Fractal.o ViewManager.o\
          FractalView.o GeneratorView.o InitiatorView.o Button.o TabButton.o
	$(CXX) $(CXXFLAGS) -o $@ $? $(CXXLIBS)

%.o: %.c
	$(CXX) $(CXXFLAGS) $@ -c $<

clean:
	$(RM) $(EXECS) *.o
