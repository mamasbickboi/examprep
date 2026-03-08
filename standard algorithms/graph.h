#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

typedef long long i64;

static const int edgeVertexListSize = 2;
const bool directed = true;
const bool undirected = false;

static struct __vertex__
{
    char name;
    struct __vertex__* adjacentVertices;
    size_t adjacentVertexCount;
    size_t graphIndex;
}
NULLVERTEX = {'\0', NULL, 0, 0};
typedef struct __vertex__ Vertex;

Vertex newVertex (char n_name)
{
    Vertex temp = NULLVERTEX;
    temp.name = n_name;

    return temp;
}

static struct __edge__
{
    Vertex* v;
    int val;
}
NULLEDGE = {NULL, -1};
typedef struct __edge__ Edge;

Edge newEdge (Vertex x, Vertex y, int v)
{
    Edge temp = NULLEDGE;
    assert(temp.v = (Vertex*)malloc(sizeof(Vertex) * edgeVertexListSize));
    temp.v[0] = x;
    temp.v[1] = y;
    temp.val = v;

    return temp;
}

static struct __graph__
{
    Edge* edgeArr;
    size_t edgeCount;
    Vertex* adjacenyList;
    size_t vertexCount;
}
NULLGRAPH = {NULL, 0, NULL, 0};
typedef struct __graph__ Graph;

void printGraph (Graph* G)
{
    if (G->vertexCount == 0)
    {
        printf("empty graph\n");
        return;
    }

    for (size_t i = 0; i < G->vertexCount; ++i)
    {
        printf("%c -> ", G->adjacenyList[i].name);
        
        for (size_t j = 0; j < G->adjacenyList[i].adjacentVertexCount; ++j)
            printf("%c -> ", G->adjacenyList[i].adjacentVertices[j].name);
        printf("NULL\n");
    }
}

i64 haveVertex (Graph* G, char v)
{
    for (size_t i = 0; i < G->vertexCount; ++i)
        if (G->adjacenyList[i].name == v)
            return i;

    return -1;
}

//add_vertex(G, x): adds the vertex x, if it is not there;
bool add_vertex (Graph* G, Vertex x)
{
    if (haveVertex(G, x.name) != -1)
    {
        printf("vertex already exists\n");
        return false;
    }

    assert(G->adjacenyList = (Vertex*)realloc(G->adjacenyList, sizeof(Vertex) * (G->vertexCount + 1)));
    x.graphIndex = G->vertexCount;
    G->adjacenyList[G->vertexCount] = x;
    ++G->vertexCount;

    return true;
}


//add_edge(G, x, y, z): adds the edge z from the vertex x to the vertex y, if it is not there;
void add_edge (Graph* G, Vertex from, Vertex to, int z, bool edgeType)
{
    for (size_t i = 0; i < G->edgeCount; ++i)
    {
        if (
            (G->edgeArr[i].v[0].name == from.name) && (G->edgeArr[i].v[1].name == to.name)
            ||
            (G->edgeArr[i].v[0].name == to.name) && (G->edgeArr[i].v[1].name == from.name)
        )
        {
            printf("'%c' to '%c' edge already exists\n", from.name, to.name);
            return;
        }
    }

    assert(G->edgeArr = (Edge*)realloc(G->edgeArr, sizeof(Edge) * (G->edgeCount + 1)));
    G->edgeArr[G->edgeCount] = newEdge(from, to, z);
    ++G->edgeCount;

    bool v1 = false,
         v2 = false;

    for (size_t i = 0; i < G->vertexCount; ++i)
    {
        if (G->adjacenyList[i].name == from.name)
        {
            Vertex* modifier = &G->adjacenyList[i];
            assert(modifier->adjacentVertices = (Vertex*)realloc(modifier->adjacentVertices,
                                                                    sizeof(Vertex) * (modifier->adjacentVertexCount + 1)
                                                                ));
            modifier->adjacentVertices[modifier->adjacentVertexCount] = to;
            ++modifier->adjacentVertexCount;

            v1 = true;
            if (edgeType || (v1 && v2))
                break;
        }

        if ((G->adjacenyList[i].name == to.name) && !edgeType)
        {
            Vertex* modifier = &G->adjacenyList[i];
            assert(modifier->adjacentVertices = (Vertex*)realloc(modifier->adjacentVertices,
                                                                    sizeof(Vertex) * (modifier->adjacentVertexCount + 1)
                                                                ));
            modifier->adjacentVertices[modifier->adjacentVertexCount] = from;
            ++modifier->adjacentVertexCount;
            
            v2 = true;
            if (v1 && v2)
                break;
        }
    }
}

void __dfs_recursive__ (Graph* G, bool* visited, Vertex* v)
{
    visited[v->graphIndex] = true;
    printf("%c - > ", v->name);

    for (size_t i = 0; i < v->adjacentVertexCount; ++i)
        if (!visited[v->adjacentVertices[i].graphIndex])
            __dfs_recursive__(G, visited, &v->adjacentVertices[i]);
}

void dfs_recursive (Graph* G, char start)
{
    i64 idx = haveVertex(G, start);
    if (idx == -1)
    {
        printf("vertex doesn't exist\n");
        return;
    }

    bool* visited;
    assert(visited = (bool*)calloc(G->vertexCount, sizeof(bool)));

    __dfs_recursive__(G, visited, &G->adjacenyList[idx]);
    printf("NULL\n");
}

/*struct dijkstraAns
{
    i64* distances;
    Vertex* previous;
};*/

/*struct dijkstraAns dijkstra (Graph* G, char src)
{
    i64 idx = haveVertex(G, src);
    if (idx == -1)
    {
        printf("vertex doesn't exist\n");
        return;
    }

    i64* dist;
    Vertex* prev;

    assert(dist = (i64*)malloc(G->vertexCount * sizeof(i64)));
    assert(prev = (Vertex*)malloc(G->vertexCount * sizeof(Vertex)));

    Vertex* queue = NULL;
    size_t Q_size = 0;

    for (size_t i = 0; i < G->vertexCount; ++i)
    {
        dist[i] = -1;
        prev[i] = NULLVERTEX;
        
        assert(realloc(queue, (sizeof(Vertex) * Q_size) + 1));
        queue[Q_size] = G->adjacenyList[i];
        ++Q_size;
    }

    dist[idx] = 0;

    while (Q_size)
    {
        size_t minIdx = 0;

        for (size_t i = 0; i < G->vertexCount; ++i)
            if ((dist[i] < minIdx) && (dist[i] > -1))
                minIdx = i;

        Vertex u = G->adjacenyList[minIdx];
        assert(memcpy(queue, queue + 1, sizeof(Vertex) * (Q_size - 1)));
        assert(queue = (Vertex*)realloc(queue, sizeof(Vertex) * (Q_size - 1)));
        --Q_size;

        for (size_t i = 0; i < G->edgeCount; ++i)
        {
            size_t alt = dist[u.graphIndex] + G->

            if (alt < dist[])
            {
                dist[] = alt
                prev[] = //u
            }
        }
    }

    struct dijkstraAns ans;
    ans.distances = dist;
    ans.previous = prev;

    return ans;
}*/


/* TODO
A*
dfs stack
bfs queue
dfs search
bfs search
*/

//potentially use union for undefined / inifitiy / idx