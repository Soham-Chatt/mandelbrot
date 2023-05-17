#include <iostream> // cout and endl
#include <fstream> // file manipulation
#include <complex> // complex numbers
#include <chrono> // clock
#include <iomanip> // setw
#include <cmath> // fmod

#define WIDTH 4000 // image width
#define HEIGHT 4000 // image height
#define MAX_ITER 50 // max number of iterations

struct Color {
  int r, g, b;
};

// Function to convert HSL to RGB
Color hslToRgb(float h, float s, float l) {
  float c = (1 - std::abs(2 * l - 1)) * s;
  float x = c * (1 - std::abs(fmod(h / 60, 2) - 1));
  float m = l - c / 2;

  float r, g, b;
  if (h < 60) {
    r = c;
    g = x;
    b = 0;
  } else if (h < 120) {
    r = x;
    g = c;
    b = 0;
  } else if (h < 180) {
    r = 0;
    g = c;
    b = x;
  } else if (h < 240) {
    r = 0;
    g = x;
    b = c;
  } else if (h < 300) {
    r = x;
    g = 0;
    b = c;
  } else {
    r = c;
    g = 0;
    b = x;
  }

  Color color;
  color.r = static_cast<int>((r + m) * 255);
  color.g = static_cast<int>((g + m) * 255);
  color.b = static_cast<int>((b + m) * 255);
  return color;
}

// Function to get the color of a pixel
Color getColor(int iter) {
  float hue = (360.0f * iter) / MAX_ITER;
  float saturation = 1.0f;
  float lightness = 0.5f;
  return hslToRgb(hue, saturation, lightness);
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


// Main function
int main() {
  std::ofstream my_Image("output.ppm");

  if (!my_Image.is_open()) {
    std::cout << "Could not open file" << std::endl;
    return 1;
  }

  my_Image << "P3\n" << WIDTH << " " << HEIGHT << " 255\n";

  auto start = std::chrono::high_resolution_clock::now();

  for (int i = 0; i < WIDTH; i++) {
    if (i % 100 == 0) {
      auto now = std::chrono::high_resolution_clock::now();
      auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - start).count();

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
      std::setw(spacingValue) << "Running for " << duration << " seconds." << std::endl;
    }//if

    for (int j = 0; j < HEIGHT; j++)  {
      int iter = value(i, j);
      Color color = getColor(iter);
      my_Image << color.r << ' ' << color.g << ' ' << color.b << "\n";
    }

  }//for i

  std::cout << "Processing: 100% done" << std::endl;
  my_Image.close();

  return 0;
}  // main
