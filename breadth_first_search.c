#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int vertex;
    struct Node *next;
} Node;

typedef struct {
    int num_vertices;
    Node **adj_lists;
} Graph;

static Node *create_node(int v) {
    Node *node = malloc(sizeof(Node));
    if (!node) {
        perror("malloc");
        exit(1);
    }
    node->vertex = v;
    node->next = NULL;
    return node;
}

static Graph *create_graph(int vertices) {
    Graph *graph = malloc(sizeof(Graph));
    if (!graph) {
        perror("malloc");
        exit(1);
    }
    graph->num_vertices = vertices;
    graph->adj_lists = calloc((size_t)vertices, sizeof(Node *));
    if (!graph->adj_lists) {
        perror("calloc");
        free(graph);
        exit(1);
    }
    return graph;
}

static void add_edge(Graph *graph, int src, int dest) {
    Node *node = create_node(dest);
    node->next = graph->adj_lists[src];
    graph->adj_lists[src] = node;
}

static void free_graph(Graph *graph) {
    for (int i = 0; i < graph->num_vertices; ++i) {
        Node *curr = graph->adj_lists[i];
        while (curr) {
            Node *tmp = curr;
            curr = curr->next;
            free(tmp);
        }
    }
    free(graph->adj_lists);
    free(graph);
}

static void bfs(Graph *graph, int start) {
    int *visited = calloc((size_t)graph->num_vertices, sizeof(int));
    if (!visited) {
        perror("calloc");
        exit(1);
    }
    int *queue = malloc((size_t)graph->num_vertices * sizeof(int));
    if (!queue) {
        perror("malloc");
        free(visited);
        exit(1);
    }

    int front = 0, rear = 0;
    visited[start] = 1;
    queue[rear++] = start;

    printf("BFS order:");
    while (front < rear) {
        int v = queue[front++];
        printf(" %d", v);
        Node *adj = graph->adj_lists[v];
        while (adj) {
            int dest = adj->vertex;
            if (!visited[dest]) {
                visited[dest] = 1;
                queue[rear++] = dest;
            }
            adj = adj->next;
        }
    }
    putchar('\n');
    free(queue);
    free(visited);
}

int main(void) {
    int vertices, edges;
    printf("Enter number of vertices: ");
    if (scanf("%d", &vertices) != 1 || vertices <= 0) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    printf("Enter number of edges: ");
    if (scanf("%d", &edges) != 1 || edges < 0) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    Graph *graph = create_graph(vertices);
    for (int i = 0; i < edges; ++i) {
        int src, dest;
        printf("Edge %d (src dest): ", i + 1);
        if (scanf("%d %d", &src, &dest) != 2 ||
            src < 0 || src >= vertices || dest < 0 || dest >= vertices) {
            fprintf(stderr, "Invalid edge.\n");
            free_graph(graph);
            return 1;
        }
        add_edge(graph, src, dest);
        add_edge(graph, dest, src);
    }
    int start;
    printf("Enter start vertex: ");
    if (scanf("%d", &start) != 1 || start < 0 || start >= vertices) {
        fprintf(stderr, "Invalid start vertex.\n");
        free_graph(graph);
        return 1;
    }
    bfs(graph, start);
    free_graph(graph);
    return 0;
}

