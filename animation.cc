// animation.cc
#include <iostream> // cout and endl
#include <string> // string manipulation
#include <fstream> // file manipulation
#include <complex> // complex numbers
#include <iomanip> // setw
#include <sys/stat.h> // mkdir
#include "color.h" // color palette

// Constants
constexpr int MAX_FRAMES = 20; // how many frames we will be generating
constexpr int WIDTH = 800; // image width
constexpr int HEIGHT = 800; // image height
constexpr int MAX_ITER = 800; // max number of iterations

// The zoom function which will decrease the range with each frame
void zoom(double &x1, double &x2, double &y1, double &y2) {
  //    The Seahorse Valley: (-0.75, 0.1)
  //    The Elephant Valley: (0.1, 0.1)

  // Set the focus point to correct area (x, y * i)
  double focus_x = -0.75;
  double focus_y = 0.1;

  // Calculate the distances in x and y directions
  double dx = x2 - x1;
  double dy = y2 - y1;

  // Calculate the new ranges
  double zoom_factor = 4;
  x1 = focus_x - dx / zoom_factor;
  x2 = focus_x + dx / zoom_factor;
  y1 = focus_y - dy / zoom_factor;
  y2 = focus_y + dy / zoom_factor;
}


int value(int x, int y, double x1, double y1, double x2, double y2) {
  std::complex<float> point((float)(x*(x2-x1)/WIDTH+x1), (float)(y*(y2-y1)/HEIGHT+y1));
  std::complex<float> z(0, 0);
  int nb_iter = 0;
  while (abs (z) < 2 && nb_iter <= MAX_ITER) {
    z = z * z + point;
    nb_iter++;
  }

  return nb_iter;
}

// Main function
int main() {
  double x1 = -2.5, x2 = 1.5, y1 = -2.0, y2 = 2.0; // These are our starting ranges

  const std::string subfolder = "frames";
  if (mkdir(subfolder.c_str(), 0777) == -1 && errno != EEXIST) {
    std::cerr << "Error" << std::endl;
    return 1;
  }

  for (int frame = 0; frame < MAX_FRAMES; ++frame) {
    std::stringstream ss;
    ss << subfolder << "/mandelbrot_" << std::setw(4) << std::setfill('0') << frame << ".ppm";
    std::ofstream my_Image(ss.str());

    if (!my_Image.is_open()) {
      std::cout << "Could not open file" << std::endl;
      return 1;
    }

    my_Image << "P3\n" << WIDTH << " " << HEIGHT << " 255\n";

    for (int i = 0; i < WIDTH; i++) {
      for (int j = 0; j < HEIGHT; j++)  {
        int iter = value(i, j, x1, y1, x2, y2);
        Color color = getColor(iter);
        my_Image << color.r << ' ' << color.g << ' ' << color.b << "\n";
      }
    }

    my_Image.close();
    zoom(x1, x2, y1, y2); // Zoom in for the next frame

    std::cout << "Frame " << frame << " of " << MAX_FRAMES << " generated." << std::endl;
  }

  std::cout << "Animation frames created. Now use software like ffmpeg to compile these into a video." << std::endl;

  return 0;
}

