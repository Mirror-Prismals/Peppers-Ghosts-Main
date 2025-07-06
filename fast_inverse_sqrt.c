#include <stdio.h>
#include <stdint.h>
#include <math.h>

typedef union {
    float f;
    uint32_t i;
} FloatInt;

static float fast_inverse_sqrt(float number) {
    const float threehalfs = 1.5F;
    FloatInt conv;
    conv.f = number;
    float x2 = number * 0.5F;
    conv.i = 0x5f3759df - (conv.i >> 1);
    conv.f = conv.f * (threehalfs - x2 * conv.f * conv.f);
    return conv.f;
}

int main(void) {
    float input;
    printf("Enter a positive float: ");
    if (scanf("%f", &input) != 1 || input <= 0.0f) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    float approx = fast_inverse_sqrt(input);
    float actual = 1.0f / sqrtf(input);
    printf("Fast inverse sqrt: %f\n", approx);
    printf("Actual inverse sqrt: %f\n", actual);
    printf("Relative error: %f%%\n", fabsf(approx - actual) / actual * 100.0f);
    return 0;
}
