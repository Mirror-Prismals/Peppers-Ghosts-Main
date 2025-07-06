#include <stdio.h>
#include <math.h>

int main(void) {
    const int width = 80;
    const int height = 24;
    const int max_iter = 100;
    const double x_min = -2.0, x_max = 1.0;
    const double y_min = -1.0, y_max = 1.0;

    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            double cr = x_min + (x_max - x_min) * i / (width - 1);
            double ci = y_min + (y_max - y_min) * j / (height - 1);
            double zr = 0.0, zi = 0.0;
            int iter = 0;
            while (zr * zr + zi * zi <= 4.0 && iter < max_iter) {
                double zr_new = zr * zr - zi * zi + cr;
                zi = 2.0 * zr * zi + ci;
                zr = zr_new;
                ++iter;
            }
            char ch;
            if (iter == max_iter)
                ch = '#';
            else if (iter > max_iter / 2)
                ch = '*';
            else if (iter > max_iter / 4)
                ch = '.';
            else
                ch = ' ';
            putchar(ch);
        }
        putchar('\n');
    }
    return 0;
}
