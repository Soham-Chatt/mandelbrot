// buddhabrot.cc
#include <iostream> // cout and endl
#include <fstream> // file manipulation
#include <complex>  // complex numbers
#include <chrono> // clock
#include <iomanip> // setw
#include <vector> // vector
#include "color.h" // color palette

#define WIDTH 2000
#define HEIGHT 2000
#define MAX_ITER 200
#define Z_LIMIT 1000.0

std::vector<int> histogram(WIDTH * HEIGHT, 0);
int max_hits = 0;

void buddhabrot(std::complex<float> point) {
  std::complex<float> z(0, 0);
  std::vector<int> path;
  path.reserve(MAX_ITER);

  for (unsigned int i = 0; i < MAX_ITER; i++) {
    z = z * z + point;
    if (abs(z) > Z_LIMIT) {
      for (int idx : path) {
        histogram[idx]++;
        if (histogram[idx] > max_hits) max_hits = histogram[idx];
      }
      break;
    }

    int x = (real(z) + 2.0) / 3.0 * WIDTH;
    int y = (imag(z) + 1.5) / 3.0 * HEIGHT;
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
      path.push_back(y * WIDTH + x);
    }
  }
}

std::string getTimestamp() {
  std::time_t t = std::time(nullptr);
  char buffer[20]; // Buffer to hold the timestamp string

  // Format the time in the "YYYY-MM-DD_HH-MM-SS" format
  std::strftime(buffer, sizeof(buffer), "%F_%H-%M-%S", std::localtime(&t));

  return std::string(buffer);
}


int main() {
  std::string timestamp = getTimestamp();
  std::string buddhabrot_output = "buddhabrot_" + timestamp + ".ppm";
  std::ofstream my_Image(buddhabrot_output);

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
      auto durationSinceLastUpdate = std::chrono::duration_cast<std::chrono::seconds>(
          now - start).count();
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
                << " seconds. "
                << durationSinceLastUpdate
                << " seconds elapsed since last update." << std::endl;

      start = std::chrono::high_resolution_clock::now();
    }

    for (int j = 0; j < HEIGHT; j++) {
      std::complex<float> point((float) i / WIDTH * 3.0 - 2.0,
                                (float) j / HEIGHT * 3.0 - 1.5);
      buddhabrot(point);
    }
  }

  // Output the image data.
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      // Normalizing the color based on the max hits for better visibility
      int val = 255 * sqrt((float)histogram[i*WIDTH + j] / (float)max_hits);
      my_Image << val << ' ' << val << ' ' << val << "\n";
    }
  }

  auto final = std::chrono::high_resolution_clock::now();
  totalDuration = std::chrono::duration_cast<std::chrono::seconds>(final - overallStart).count();

  std::cout << "Processing: 100% done" << std::endl;
  my_Image.close();

  // Write the info to a file
  std::ofstream output("infoBuddhabrot_" + timestamp + ".txt");
  output << "Buddhabrot set" << std::endl;
  output << "Width: " << WIDTH << std::endl;
  output << "Height: " << HEIGHT << std::endl;
  output << "Max iterations: " << MAX_ITER << std::endl;
  output << "Total duration: " << totalDuration << " seconds" << std::endl;
  output.close();

  return 0;
}  // main