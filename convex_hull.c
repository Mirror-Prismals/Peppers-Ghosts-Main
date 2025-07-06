#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Point;

static Point origin;
static int compare_points(const void *a, const void *b) {
    const Point *p1 = a;
    const Point *p2 = b;
    double dx1 = p1->x - origin.x;
    double dy1 = p1->y - origin.y;
    double dx2 = p2->x - origin.x;
    double dy2 = p2->y - origin.y;
    double angle1 = atan2(dy1, dx1);
    double angle2 = atan2(dy2, dx2);
    if (angle1 < angle2) return -1;
    if (angle1 > angle2) return 1;
    double dist1 = dx1*dx1 + dy1*dy1;
    double dist2 = dx2*dx2 + dy2*dy2;
    if (dist1 < dist2) return -1;
    if (dist1 > dist2) return 1;
    return 0;
}

static double cross(const Point *o, const Point *a, const Point *b) {
    return (a->x - o->x) * (b->y - o->y) - (a->y - o->y) * (b->x - o->x);
}

int main(void) {
    int n;
    printf("Enter number of points: ");
    if (scanf("%d", &n) != 1 || n < 3) {
        fprintf(stderr, "Need at least 3 points\n");
        return 1;
    }
    Point *points = malloc(n * sizeof(Point));
    if (!points) {
        perror("malloc");
        return 1;
    }
    for (int i = 0; i < n; ++i) {
        if (scanf("%lf %lf", &points[i].x, &points[i].y) != 2) {
            fprintf(stderr, "Invalid input\n");
            free(points);
            return 1;
        }
    }

    int lowest = 0;
    for (int i = 1; i < n; ++i) {
        if (points[i].y < points[lowest].y ||
            (points[i].y == points[lowest].y && points[i].x < points[lowest].x)) {
            lowest = i;
        }
    }
    Point temp = points[0];
    points[0] = points[lowest];
    points[lowest] = temp;

    origin = points[0];
    qsort(points + 1, n - 1, sizeof(Point), compare_points);

    Point *stack = malloc(n * sizeof(Point));
    if (!stack) {
        perror("malloc");
        free(points);
        return 1;
    }
    int top = 0;
    stack[top++] = points[0];
    stack[top++] = points[1];

    for (int i = 2; i < n; ++i) {
        while (top >= 2 && cross(&stack[top-2], &stack[top-1], &points[i]) <= 0) {
            --top;
        }
        stack[top++] = points[i];
    }

    printf("Convex hull:\n");
    for (int i = 0; i < top; ++i) {
        printf("%lf %lf\n", stack[i].x, stack[i].y);
    }

    free(points);
    free(stack);
    return 0;
}

