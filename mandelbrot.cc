// mandelbrot.cc
#include <iostream> // cout and endl
#include <string> // string manipulation
#include <fstream> // file manipulation
#include <complex> // complex numbers
#include <chrono> // clock
#include "color.h" // color palette

// Constants
constexpr int WIDTH = 1000; // image width
constexpr int HEIGHT = 1000; // image height
constexpr int MAX_ITER = 20; // max number of iterations
constexpr char DELIMITER = '\t'; // delimiter for the output

// Function to compute the Mandelbrot sequence
int value(int x, int y) {
  std::complex<float> point((float)x/WIDTH-1.5f, (float)y/HEIGHT-0.5f);
  std::complex<float> z(0, 0);
  int nb_iter = 0;
  while (abs (z) < 2 && nb_iter <= MAX_ITER) {
    z = z * z + point;
    nb_iter++;
  }

  return nb_iter;
}

// Function to get the current time in the format YYYY-MM-DD_HH-MM-SS
std::string getTimestamp() {
  std::time_t t = std::time(nullptr);
  char buffer[20];

  // Format the time in the "YYYY-MM-DD_HH-MM-SS" format
  std::strftime(buffer, sizeof(buffer), "%F_%H-%M-%S", std::localtime(&t));

  return buffer;
}

// Function to get the current time in the format HH:MM:SS DD/MM/YYYY and return a std::string
std::string getTime() {
  std::time_t t = std::time(nullptr);
  char buffer[20];

  // Format the time in the "HH:MM:SS DD:MM" format
  std::strftime(buffer, sizeof(buffer), "%T \t %D", std::localtime(&t));

  return buffer;
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

  long totalDuration;
  auto overallStart = std::chrono::high_resolution_clock::now();

  for (int i = 0; i < WIDTH; i++) {
    if (i % 100 == 0) {
      auto now = std::chrono::high_resolution_clock::now();
      totalDuration = std::chrono::duration_cast<std::chrono::seconds>(
          now - overallStart).count();

      double processPercentage = 100.0 * i / WIDTH;
      std::cout << processPercentage << DELIMITER <<  totalDuration << DELIMITER << getTime() << std::endl;
    }

    for (int j = 0; j < HEIGHT; j++)  {
      int iter = value(i, j);
      Color color = getColor(iter);
      my_Image << color.r << ' ' << color.g << ' ' << color.b << "\n";
    }

  }//for i

  auto final = std::chrono::high_resolution_clock::now();
  totalDuration = std::chrono::duration_cast<std::chrono::seconds>(final - overallStart).count();

  std::cout << "100" << DELIMITER <<  totalDuration << DELIMITER << getTime() << std::endl;


  my_Image.close();

  // Write the info to a file
  std::ofstream output("info_" + timestamp + ".txt");
  output << "Mandelbrot set" << std::endl;
  output << "Width: " << WIDTH << std::endl;
  output << "Height: " << HEIGHT << std::endl;
  output << "Max iterations: " << MAX_ITER << std::endl;
  output << "Palette size: " << PALETTE_SIZE << std::endl;
  output << "Total duration: " << totalDuration << " seconds" << std::endl;
  output.close();

  return 0;
}  // main

