// mandelbrot.cc
#include <iostream> // cout and endl
#include <fstream> // file manipulation
#include <complex> // complex numbers
#include <chrono> // clock
#include <iomanip> // setw

#define WIDTH 4000 // image width
#define HEIGHT 4000 // image height
#define MAX_ITER 50 // max number of iterations
#define PALETTE_SIZE 16 // size of the color palette

// Struct to store the RGB values
struct Color {
  int r, g, b;
};

// Function to create a color from RGB values
Color makeColor(int r, int g, int b) {
  Color color;
  color.r = r;
  color.g = g;
  color.b = b;
  return color;
}

// Color palette
Color palette[PALETTE_SIZE] = {
    makeColor(66, 30, 15),
    makeColor(25, 7, 26),
    makeColor(9, 1, 47),
    makeColor(4, 4, 73),
    makeColor(0, 7, 100),
    makeColor(12, 44, 138),
    makeColor(24, 82, 177),
    makeColor(57, 125, 209),
    makeColor(134, 181, 229),
    makeColor(211, 236, 248),
    makeColor(241, 233, 191),
    makeColor(248, 201, 95),
    makeColor(255, 170, 0),
    makeColor(204, 128, 0),
    makeColor(153, 87, 0),
    makeColor(106, 52, 3)
};

// Function to get the color of a pixel
Color getColor(int iter) {
  // Use the modulo operator to cycle through the palette
  return palette[iter % PALETTE_SIZE];
}

// Function to compute the Mandelbrot sequence
int value(int x, int y) {
  std::complex<float> point((float)x/WIDTH-1.5, (float)y/HEIGHT-0.5);
  std::complex<float> z(0, 0);
  unsigned int nb_iter = 0;
  while (abs (z) < 2 && nb_iter <= MAX_ITER) {
    z = z * z + point;
    nb_iter++;
  }
  return nb_iter;
}

std::string getTimestamp() {
  std::time_t t = std::time(nullptr);
  char buffer[20]; // Buffer to hold the timestamp string

  // Format the time in the "YYYY-MM-DD_HH-MM-SS" format
  std::strftime(buffer, sizeof(buffer), "%F_%H-%M-%S", std::localtime(&t));

  return std::string(buffer);
}


// Main function
int main() {
  std::string timestamp = getTimestamp();
  std::string mandelbrot_output = "mandelbrot_" + timestamp + ".ppm";
  std::ofstream my_Image(mandelbrot_output);

  if (!my_Image.is_open()) {
    std::cout << "Could not open file" << std::endl;
    return 1;
  }

  my_Image << "P3\n" << WIDTH << " " << HEIGHT << " 255\n";

  long totalDuration = 0;
  auto overallStart = std::chrono::high_resolution_clock::now();
  auto start = overallStart;

  for (int i = 0; i < WIDTH; i++) {
    // Print the progress every 100 pixels
    if (i % 100 == 0) {
      auto now = std::chrono::high_resolution_clock::now();
      auto durationSinceLastUpdate = std::chrono::duration_cast<std::chrono::seconds>(now - start).count();
      totalDuration = std::chrono::duration_cast<std::chrono::seconds>(now - overallStart).count();

      double processPercentage = 100.0 * i / WIDTH;
      // Spacing for the output
      int spacingValue = 30;
      if (processPercentage != static_cast<int>(processPercentage)) {
        spacingValue -= 2;
      }

      if (processPercentage >= 10) {
        spacingValue -= 1;
      }

      std::cout << "Processing: " << processPercentage << "%" <<
      std::setw(spacingValue) << "Running for " << totalDuration << " seconds. " <<
      << durationSinceLastUpdate << " seconds elapsed since last update." << std::endl;

      // Reset the start time for the next progress update
      start = std::chrono::high_resolution_clock::now();
    }//if

    for (int j = 0; j < HEIGHT; j++)  {
      int iter = value(i, j);
      Color color = getColor(iter);
      my_Image << color.r << ' ' << color.g << ' ' << color.b << "\n";
    }

  }//for i

  auto final = std::chrono::high_resolution_clock::now();
  totalDuration = std::chrono::duration_cast<std::chrono::seconds>(final - overallStart).count();

  std::cout << "Processing: 100% done" << std::endl;
  my_Image.close();

  // Write the info to a file
  std::ofstream output("infoMandelbrot_" + timestamp + ".txt");
  output << "Mandelbrot set" << std::endl;
  output << "Width: " << WIDTH << std::endl;
  output << "Height: " << HEIGHT << std::endl;
  output << "Max iterations: " << MAX_ITER << std::endl;
  output << "Palette size: " << PALETTE_SIZE << std::endl;
  output << "Total duration: " << totalDuration << " seconds" << std::endl;
  output.close();

  return 0;
}  // main

