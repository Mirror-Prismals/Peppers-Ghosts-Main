#include <stdio.h>
#include <math.h>

int main(void) {
    const int samples = 360; // number of samples from 0 to 2*pi
    for (int i = 0; i <= samples; ++i) {
        double angle = (2.0 * M_PI * i) / samples; // radians
        printf("%d,%f\n", i, sin(angle));
    }
    return 0;
}
