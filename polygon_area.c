#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Point;

double polygon_area(const Point *p, int n) {
    double sum = 0.0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        sum += p[i].x * p[j].y - p[j].x * p[i].y;
    }
    return fabs(sum) / 2.0;
}

int main(void) {
    int n;
    printf("Enter number of vertices: ");
    if (scanf("%d", &n) != 1 || n < 3) {
        fprintf(stderr, "Invalid number of vertices.\n");
        return 1;
    }
    Point *points = malloc((size_t)n * sizeof(Point));
    if (!points) {
        perror("malloc");
        return 1;
    }
    printf("Enter x and y coordinates of the vertices:\n");
    for (int i = 0; i < n; ++i) {
        if (scanf("%lf %lf", &points[i].x, &points[i].y) != 2) {
            fprintf(stderr, "Invalid input.\n");
            free(points);
            return 1;
        }
    }
    double area = polygon_area(points, n);
    printf("Area of polygon: %g\n", area);
    free(points);
    return 0;
}
