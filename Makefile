CXX = g++
CXXFLAGS = -O3
DEBUGFLAGS = -g -O0
TARGET1 = mandelbrot
TARGET2 = buddhabrot

all: $(TARGET1) $(TARGET2)

$(TARGET1): $(TARGET1).cc
	$(CXX) $(CXXFLAGS) -o $(TARGET1) $(TARGET1).cc

$(TARGET2): $(TARGET2).cc
	$(CXX) $(CXXFLAGS) -o $(TARGET2) $(TARGET2).cc

debug1: $(TARGET1).cc
	$(CXX) $(DEBUGFLAGS) -o $(TARGET1)_debug $(TARGET1).cc

debug2: $(TARGET2).cc
	$(CXX) $(DEBUGFLAGS) -o $(TARGET2)_debug $(TARGET2).cc

clean:
	rm -f $(TARGET1) $(TARGET1)_debug $(TARGET2) $(TARGET2)_debug
	rm -f *.ppm *.png *.tiff *.txt
