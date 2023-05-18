// color.h
#ifndef MANDELBROTCPP_COLOR_H
#define MANDELBROTCPP_COLOR_H

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

#endif //MANDELBROTCPP_COLOR_H
