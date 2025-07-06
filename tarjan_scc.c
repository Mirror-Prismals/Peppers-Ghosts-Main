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

static void scc_util(Graph *graph, int u, int *disc, int *low, int *stack,
                     int *stack_index, int *stack_member, int *time) {
    disc[u] = low[u] = ++(*time);
    stack[(*stack_index)++] = u;
    stack_member[u] = 1;

    for (Node *adj = graph->adj_lists[u]; adj; adj = adj->next) {
        int v = adj->vertex;
        if (disc[v] == -1) {
            scc_util(graph, v, disc, low, stack, stack_index, stack_member, time);
            if (low[v] < low[u]) {
                low[u] = low[v];
            }
        } else if (stack_member[v] && disc[v] < low[u]) {
            low[u] = disc[v];
        }
    }

    if (low[u] == disc[u]) {
        printf("SCC:");
        int w;
        do {
            w = stack[--(*stack_index)];
            stack_member[w] = 0;
            printf(" %d", w);
        } while (w != u);
        putchar('\n');
    }
}

static void tarjan_scc(Graph *graph) {
    int n = graph->num_vertices;
    int *disc = malloc((size_t)n * sizeof(int));
    int *low = malloc((size_t)n * sizeof(int));
    int *stack = malloc((size_t)n * sizeof(int));
    int *stack_member = calloc((size_t)n, sizeof(int));
    if (!disc || !low || !stack || !stack_member) {
        perror("malloc");
        free(disc);
        free(low);
        free(stack);
        free(stack_member);
        return;
    }
    for (int i = 0; i < n; ++i) {
        disc[i] = -1;
    }
    int time = 0;
    int stack_index = 0;
    for (int i = 0; i < n; ++i) {
        if (disc[i] == -1) {
            scc_util(graph, i, disc, low, stack, &stack_index, stack_member, &time);
        }
    }
    free(disc);
    free(low);
    free(stack);
    free(stack_member);
}

int main(void) {
    int vertices, edges;
    printf("Enter number of vertices: ");
    if (scanf("%d", &vertices) != 1 || vertices <= 0) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    printf("Enter number of directed edges: ");
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
    }
    tarjan_scc(graph);
    free_graph(graph);
    return 0;
}

