#include <stdio.h>
#include <stdlib.h>

// Structura pentru nodul din lista de adiacență
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Structura pentru graf
typedef struct Graph {
    int vertices;
    int *visited;
    Node **adjacency_lists;
} Graph;

// Funcție pentru crearea unui nod nou
Node *create_node(int v) {
    Node *new_node = malloc(sizeof(Node));
    new_node->data = v;
    new_node->next = NULL;
    return new_node;
}

// Funcție pentru crearea unui graf nou
Graph *create_graph(int vertices) {
    Graph *graph = malloc(sizeof(Graph));
    graph->vertices = vertices;
    graph->adjacency_lists = malloc(vertices * sizeof(Node *));
    graph->visited = malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

// Funcție pentru adăugarea unei muchii între două noduri
void add_edge(Graph *graph, int src, int dest) {
    // Adăugare nod dest în lista de adiacență a lui src
    Node *new_node = create_node(dest);
    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;

    // Adăugare nod src în lista de adiacență a lui dest (pentru graf neorientat)
    new_node = create_node(src);
    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;
}

// Funcție pentru parcurgerea grafului folosind DFS
void DFS(Graph *graph, int vertex) {
    graph->visited[vertex] = 1;
    printf("%d -> ", vertex);

    Node *adj_list = graph->adjacency_lists[vertex];
    while (adj_list != NULL) {
        int connected_vertex = adj_list->data;
        if (graph->visited[connected_vertex] == 0) {
            DFS(graph, connected_vertex);
        }
        adj_list = adj_list->next;
    }
}

// Funcție pentru parcurgerea grafului folosind BFS
void BFS(Graph *graph, int start) {
    Node *queue = NULL;

    graph->visited[start] = 1;
    printf("%d -> ", start);
    enqueue(&queue, start);

    while (!is_empty(queue)) {
        int current = dequeue(&queue);

        Node *adj_list = graph->adjacency_lists[current];
        while (adj_list != NULL) {
            int adj_vertex = adj_list->data;
            if (graph->visited[adj_vertex] == 0) {
                graph->visited[adj_vertex] = 1;
                printf("%d -> ", adj_vertex);
                enqueue(&queue, adj_vertex);
            }
            adj_list = adj_list->next;
        }
    }
}

// Funcție pentru verificarea dacă coada este goală
int is_empty(Node *queue) {
    return queue == NULL;
}

// Funcție pentru adăugarea unui element în coadă
void enqueue(Node **queue, int data) {
    Node *new_node = create_node(data);
    if (is_empty(*queue)) {
        *queue = new_node;
    } else {
        Node *temp = *queue;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

// Funcție pentru extragerea unui element din coadă
int dequeue(Node **queue) {
    int data = (*queue)->data;
    Node *temp = *queue;
    *queue = (*queue)->next;
    free(temp);
    return data;
}

// Funcție pentru resetarea listei de noduri vizitate
void reset_visited(Graph *graph) {
    for (int i = 0; i < graph->vertices; i++) {
        graph->visited[i] = 0;
    }
}

// Funcție pentru afișarea listei de adiacență a grafului
void print_graph(Graph *graph) {
    for (int i = 0; i < graph->vertices; i++) {
        printf("Lista de adiacenta pentru nodul %d: ", i);
        Node *temp = graph->adjacency_lists[i];
        while (temp != NULL) {
            printf("%d -> ", temp->data);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

int main() {
    int nr_of_vertices, nr_of_edges, src, dest, starting_vertex;

    printf("Cate noduri are graful? ");
    scanf("%d", &nr_of_vertices);

    Graph *graph = create_graph(nr_of_vertices);

    printf("Cate muchii are graful? ");
    scanf("%d", &nr_of_edges);

    printf("Adauga %d muchii (de la 0 la %d):\n", nr_of_edges, nr_of_vertices - 1);
    for (int i = 0; i < nr_of_edges; i++) {
        scanf("%d %d", &src, &dest);
        add_edge(graph, src, dest);
    }

    printf("De unde plecam în DFS? ");
    scanf("%d", &starting_vertex);
    printf("Parcurgere DFS: ");
    DFS(graph, starting_vertex);
    reset_visited(graph);
    printf("\n");

    printf("De unde plecam în BFS? ");
    scanf("%d", &starting_vertex);
    printf("Parcurgere BFS: ");
    BFS(graph, starting_vertex);
    printf("\n");

    return 0;
}
