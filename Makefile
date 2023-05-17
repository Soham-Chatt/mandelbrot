CXX = g++
CXXFLAGS = -O3
DEBUGFLAGS = -g -O0
TARGET = mandelbrot

all: $(TARGET)

$(TARGET): $(TARGET).cc
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(TARGET).cc

debug: $(TARGET).cc
	$(CXX) $(DEBUGFLAGS) -o $(TARGET)_debug $(TARGET).cc

clean:
	rm -f $(TARGET) $(TARGET)_debug
