// mandelbrot.cc
#include <iostream> // cout and endl
#include <fstream> // file manipulation
#include <complex> // complex numbers
#include <chrono> // clock
#include <iomanip> // setw
#include "color.h" // color palette

#define WIDTH 4000 // image width
#define HEIGHT 4000 // image height
#define MAX_ITER 50 // max number of iterations

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
    if (i % 100 == 0) {
      auto now = std::chrono::high_resolution_clock::now();
      totalDuration = std::chrono::duration_cast<std::chrono::seconds>(
          now - overallStart).count();

      double processPercentage = 100.0 * i / WIDTH;
      int spacingValue = 30;
      if (processPercentage != static_cast<int>(processPercentage)) {
        spacingValue -= 2;
      }

      if (processPercentage >= 10) {
        spacingValue -= 1;
      }

      std::cout << "Processing: " << processPercentage << "%" <<
                std::setw(spacingValue) << "Running for " << totalDuration
                << " seconds." << std::endl;
    }

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

