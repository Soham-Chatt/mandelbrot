#include <iostream> // cout and endl
#include <fstream> // file manipulation
#include <complex> // complex numbers
#include <chrono> // clock
#include <iomanip> // setw

#define WIDTH 4000
#define HEIGHT 4000
#define MAX_ITER 50

struct Color {
  int r, g, b;
};

Color colors[5] = {
    {  255,   0,   0},  // Red
    {  0, 255,   0},  // Green
    {  0,   0, 255},  // Blue
    { 255, 255,   0},  // Yellow
    { 255,   0, 255}   // Magenta
};



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

Color getColor(int iter) {
  int index = (iter * 5) / MAX_ITER;
  if (index >= 5) index = 4;
  return colors[index];
}

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
