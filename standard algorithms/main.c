#include "graph.h"

int main (void)
{
    Graph graph = NULLGRAPH;

    for (int i = 0; i < 7; ++i)
        if(!add_vertex(&graph, newVertex('A' + i)))
            printf("failed to add vertex\n");

    add_edge(&graph, newVertex('A'), newVertex('B'), 5, undirected);
    add_edge(&graph, newVertex('A'), newVertex('C'), 2, undirected);
    add_edge(&graph, newVertex('A'), newVertex('D'), 10, undirected);

    add_edge(&graph, newVertex('B'), newVertex('A'), 5, undirected);
    add_edge(&graph, newVertex('B'), newVertex('E'), 2, undirected);

    add_edge(&graph, newVertex('C'), newVertex('A'), 2, undirected);
    add_edge(&graph, newVertex('C'), newVertex('D'), 8, undirected);

    add_edge(&graph, newVertex('D'), newVertex('A'), 10, undirected);
    add_edge(&graph, newVertex('D'), newVertex('C'), 8, undirected);
    add_edge(&graph, newVertex('D'), newVertex('G'), 4, undirected);

    add_edge(&graph, newVertex('E'), newVertex('B'), 2, undirected);
    add_edge(&graph, newVertex('E'), newVertex('F'), 8, undirected);
    add_edge(&graph, newVertex('E'), newVertex('G'), 12, undirected);

    add_edge(&graph, newVertex('F'), newVertex('E'), 8, undirected);
    add_edge(&graph, newVertex('F'), newVertex('G'), 1, undirected);

    add_edge(&graph, newVertex('G'), newVertex('D'), 4, undirected);
    add_edge(&graph, newVertex('G'), newVertex('E'), 12, undirected);
    add_edge(&graph, newVertex('G'), newVertex('F'), 1, undirected);

    printf("\n\n\n");

    printGraph(&graph);

    printf("\n\n\n");

    dfs_recursive(&graph, 'G');

    getchar();
}
/*
    A -> B -> C -> D
    B -> A -> E
    C -> A -> D
    D -> A -> C -> G
    E -> B -> F -> G
    F -> E -> G
    G -> D -> E -> F
*/