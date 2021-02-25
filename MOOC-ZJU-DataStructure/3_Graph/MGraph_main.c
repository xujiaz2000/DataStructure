#include <stdio.h>
#include <stdlib.h>
#include "MGraph.h"

void PrintPath(Vertex v, Vertex w, Vertex *path) {
    //打印path对应的v到w的最短路径
    if (v == w) {
        printf("%d到%d的最短路径：%d\n", v, w, v);
        return ;
    }
    if (path[w] < 0) {  //v和w间不存在路径
        printf("%d与%d不连通\n", v, w);
        return ;
    }
    Vertex dst = w;
    Vertex s[MAX_VERTEX_NUM], top = 0;  //栈
    while (w >= 0) {
        s[top++] = w;
        w = path[w];
    }
    printf("%d到%d的最短路径：", s[top - 1], dst);
    while (top != 0)
        printf("%d ", s[--top]);
    putchar(10);
    return ;
}

void PrintPathFromVToW(Vertex v, Vertex w, Vertex path[][MAX_VERTEX_NUM]) {
    //打印v到w的最短路径
    if (v == w) {
        printf("%d到%d的最短路径：%d\n", v, w, v);
        return ;
    }
    if (path[v][w] < 0) {  //v和w间不存在路径
        printf("%d与%d不连通\n", v, w);
        return ;
    }
    printf("%d到%d的最短路径：", v, w);
    Vertex s[MAX_VERTEX_NUM], top = 0;  //栈
    while (w >= 0) {
        s[top++] = w;
        w = path[v][w];
    }
    while (top != 0)
        printf("%d ", s[--top]);
    putchar(10);
    return ;    
}


int main()
{
    MGraph graph = BuildGraph();
    BFS(graph, 0, Visit);

    //单源最短路径算法
    WeightType *dist = (WeightType *)malloc(graph->nv * sizeof(WeightType));
    Vertex *path = (Vertex *)malloc(graph->nv * sizeof(Vertex));
    Vertex src = 1;
    Dijkstra(graph, dist, path, src);  //生成属于顶点v的dist[]和path[]
    printf("dist[]: ");
    for (Vertex i = 0; i < graph->nv; ++i) {
        printf("%d ", dist[i]);
    }putchar(10);
    printf("path[]: ");
    for (Vertex i = 0; i < graph->nv; ++i) {
        printf("%d ", path[i]);
    }putchar(10);

    PrintPath(src, 3, path);
    PrintPath(src, 1, path);
    PrintPath(src, 0, path);

    //多源最短路径算法
    WeightType dist2[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    Vertex path2[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    // MultSrcPath(graph, dist2, path2);
    Floyd(graph, dist2, path2);
    printf("dist2[][]:\n");
    for (Vertex i = 0; i < graph->nv; ++i) {
        for (Vertex j = 0; j < graph->nv; ++j)
            printf("%d\t", dist2[i][j]);
        putchar(10);
    }
    printf("path[][]:\n");
    for (Vertex i = 0; i < graph->nv; ++i) {
        for (Vertex j = 0; j < graph->nv; ++j)
            printf("%d\t", path2[i][j]);
        putchar(10);
    }
    PrintPathFromVToW(0, 3, path2);
    PrintPathFromVToW(1, 6, path2);
    PrintPathFromVToW(6, 6, path2);
    PrintPathFromVToW(5, 6, path2);

    //最小生成树算法：Prim
    MGraph MST = CreateGraph(graph->nv);
    Prim(graph, MST);
    printf("MST的邻接矩阵表示形式：\n");
    for (Vertex i = 0; i < MST->nv; ++i) {
        for (Vertex j = 0; j < MST->nv; ++j)
            printf("%d\t", MST->G[i][j]);
        putchar(10);
    }

    return 0;
}

/*
 * 输入示例：
7 7
1 2 1
2 3 1
1 3 4
2 4 3
4 5 1
4 6 1
0 1 1
abcdefg

    顶点数 边数
    <v1, v2, weight>
    ...
    顶点存储的数据
 
 * 输入示例2（ppt中的Prim算法例子（下标-1），注：InsertEdge函数要改为无向图）：
7 12
0 1 2 
0 3 1
1 3 3
0 2 4
1 4 10
2 3 2
3 4 7
3 6 4
4 6 6
5 6 1
3 5 8
2 5 5
1234567

 *
 */