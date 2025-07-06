#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct { int x, y; } Point;

typedef struct {
    Point p;
    int f;
} Node;

#define INDEX(x, y, cols) ((y) * (cols) + (x))

static int heuristic(Point a, Point b) {
    return abs(a.x - b.x) + abs(a.y - b.y); // Manhattan distance
}

int main(void) {
    int rows, cols;
    printf("Enter grid size (rows columns): ");
    if (scanf("%d %d", &rows, &cols) != 2 || rows <= 0 || cols <= 0) {
        fprintf(stderr, "Invalid grid size.\n");
        return 1;
    }

    int cells = rows * cols;
    int *grid = malloc((size_t)cells * sizeof(int));
    int *g_cost = malloc((size_t)cells * sizeof(int));
    int *closed = calloc((size_t)cells, sizeof(int));
    Point *parent = malloc((size_t)cells * sizeof(Point));
    Node *open = malloc((size_t)cells * sizeof(Node));
    if (!grid || !g_cost || !closed || !parent || !open) {
        perror("malloc");
        free(grid); free(g_cost); free(closed); free(parent); free(open);
        return 1;
    }

    printf("Enter grid (0 = free, 1 = obstacle):\n");
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            if (scanf("%d", &grid[INDEX(x, y, cols)]) != 1 ||
                (grid[INDEX(x, y, cols)] != 0 && grid[INDEX(x, y, cols)] != 1)) {
                fprintf(stderr, "Invalid grid input.\n");
                free(grid); free(g_cost); free(closed); free(parent); free(open);
                return 1;
            }
        }
    }

    Point start, goal;
    printf("Enter start coordinates (x y): ");
    if (scanf("%d %d", &start.x, &start.y) != 2 ||
        start.x < 0 || start.x >= cols || start.y < 0 || start.y >= rows) {
        fprintf(stderr, "Invalid start coordinates.\n");
        free(grid); free(g_cost); free(closed); free(parent); free(open);
        return 1;
    }
    if (grid[INDEX(start.x, start.y, cols)]) {
        fprintf(stderr, "Start is on an obstacle.\n");
        free(grid); free(g_cost); free(closed); free(parent); free(open);
        return 1;
    }

    printf("Enter goal coordinates (x y): ");
    if (scanf("%d %d", &goal.x, &goal.y) != 2 ||
        goal.x < 0 || goal.x >= cols || goal.y < 0 || goal.y >= rows) {
        fprintf(stderr, "Invalid goal coordinates.\n");
        free(grid); free(g_cost); free(closed); free(parent); free(open);
        return 1;
    }
    if (grid[INDEX(goal.x, goal.y, cols)]) {
        fprintf(stderr, "Goal is on an obstacle.\n");
        free(grid); free(g_cost); free(closed); free(parent); free(open);
        return 1;
    }

    for (int i = 0; i < cells; ++i) {
        g_cost[i] = INT_MAX;
    }

    int open_size = 0;
    g_cost[INDEX(start.x, start.y, cols)] = 0;
    open[open_size++] = (Node){ start, heuristic(start, goal) };

    int found = 0;
    while (open_size > 0) {
        int best = 0;
        for (int i = 1; i < open_size; ++i) {
            if (open[i].f < open[best].f)
                best = i;
        }
        Node current = open[best];
        open[best] = open[--open_size];
        int cidx = INDEX(current.p.x, current.p.y, cols);
        if (closed[cidx])
            continue;
        closed[cidx] = 1;

        if (current.p.x == goal.x && current.p.y == goal.y) {
            found = 1;
            break;
        }

        int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
        for (int d = 0; d < 4; ++d) {
            int nx = current.p.x + dirs[d][0];
            int ny = current.p.y + dirs[d][1];
            if (nx < 0 || nx >= cols || ny < 0 || ny >= rows)
                continue;
            int nidx = INDEX(nx, ny, cols);
            if (grid[nidx] || closed[nidx])
                continue;
            int tentative_g = g_cost[cidx] + 1;
            if (tentative_g < g_cost[nidx]) {
                g_cost[nidx] = tentative_g;
                parent[nidx] = current.p;
                int f = tentative_g + heuristic((Point){nx, ny}, goal);
                open[open_size++] = (Node){ {nx, ny}, f };
            }
        }
    }

    if (!found) {
        printf("No path found.\n");
    } else {
        Point *path = malloc((size_t)cells * sizeof(Point));
        if (!path) {
            perror("malloc");
            free(grid); free(g_cost); free(closed); free(parent); free(open);
            return 1;
        }
        int length = 0;
        Point cur = goal;
        while (cur.x != start.x || cur.y != start.y) {
            path[length++] = cur;
            cur = parent[INDEX(cur.x, cur.y, cols)];
        }
        path[length++] = start;
        printf("Path length: %d\n", length - 1);
        for (int i = length - 1; i >= 0; --i) {
            printf("(%d,%d)%s", path[i].x, path[i].y, i ? " -> " : "\n");
        }
        free(path);
    }

    free(grid); free(g_cost); free(closed); free(parent); free(open);
    return 0;
}

