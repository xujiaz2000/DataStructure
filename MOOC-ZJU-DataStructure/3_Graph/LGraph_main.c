#include <stdio.h>
#include <stdlib.h>
#include "LGraph.h"

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

int main()
{
    LGraph graph = BuildGraph();
    DFS(graph, 0, Visit);

    //单源最短路径算法
    WeightType *dist = (WeightType *)malloc(graph->nv * sizeof(WeightType));
    Vertex *path = (Vertex *)malloc(graph->nv * sizeof(Vertex));
    Vertex src = 1;
    Unweighted(graph, dist, path, src);  //生成属于顶点v的dist[]和path[]
    printf("dist[]: ");
    for (Vertex i = 0; i < graph->nv; ++i) {
        printf("%d ", dist[i]);
    }putchar(10);
    printf("path[]: ");
    for (Vertex i = 0; i < graph->nv; ++i) {
        printf("%d ", path[i]);
    }putchar(10);

    PrintPath(src, 0, path);
    PrintPath(src, 4, path);
    PrintPath(src, 2, path);

    //最小生成树算法：Kruskal
    LGraph MST = CreateGraph(graph->nv);
    Kruskal(graph, MST);
    printf("MST的邻接表形式：\n");
    for (Vertex v = 0; v < MST->nv; ++v) {
        for (PtrToAdjVNode w = MST->G[v].firstEdge; w; w = w->next) 
            printf("%d\t", w->adjv);
        putchar(10);
    }

    //拓扑排序
    int *topOrder = (Vertex *)malloc(graph->nv * sizeof(Vertex));
    TopSort(graph, topOrder);
    printf("拓扑序（注：需以有向图建图，也就是说，要修改InsertEdge函数）：\n");
    for (Vertex v = 0; v < graph->nv; ++v)
        printf("%d ", topOrder[v]);
    putchar(10);

    return 0;
}

/*
 * 输入示例：
7 7
1 2 1
2 3 1
1 3 1
2 4 1
4 5 1
4 6 1
0 1 1
abcdefg

    顶点数 边数
    <v1, v2, weight>
    ...
    顶点存储的数据

 * 输入示例2（ppt中的Prim算法例子（下标-1），注：InsertEdge函数要改为无向图，注：此示例会导致单源最短路径算法输出错误，因为该算法适用于无权图）：
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

 */