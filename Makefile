CXX = g++
CXXFLAGS = -O3
DEBUGFLAGS = -g -O0
TARGET1 = mandelbrot
TARGET2 = animation

all: $(TARGET1) $(TARGET2) $(TARGET3)

$(TARGET1): $(TARGET1).cc
	$(CXX) $(CXXFLAGS) -o $(TARGET1) $(TARGET1).cc

$(TARGET2): $(TARGET2).cc
	$(CXX) $(CXXFLAGS) -o $(TARGET2) $(TARGET2).cc

clean:
	rm -f $(TARGET1) $(TARGET2)
	rm -f *.ppm *.png *.tiff *.txt *.out
	rm -rf mandelbrot_*
