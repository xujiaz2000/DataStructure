#include <stdio.h>
#include <stdlib.h>
#include "MGraph.h"

MGraph CreateGraph(int vertexNum) {
    //初始化一个有vertexNum个顶点但没有边的图
    MGraph graph = (MGraph)malloc(sizeof(struct MGNode));
    graph->nv = vertexNum;
    graph->ne = 0;
    for (Vertex v = 0; v < graph->nv; ++v)
        for (Vertex w = 0; w < graph->nv; ++w)
            graph->G[v][w] = INF;  //不存在的边权重被初始化为INF

    for (Vertex v = 0; v < graph->nv; ++v)
        graph->G[v][v] = 0;

    return graph;
}

void InsertEdge(MGraph graph, Edge e) {
    //插入边<v1,vv2>
    graph->G[e->v1][e->v2] = e->weight;
    //若是无向图，还要插入边<v2, v1>
    graph->G[e->v2][e->v1] = e->weight;

    ++graph->ne;
}

MGraph BuildGraph() {
    //输入：顶点数，边数，边
    //返回：对应的图
    int nv, ne;
    scanf("%d", &nv);  //输入顶点数
    MGraph graph = CreateGraph(nv);
    scanf("%d", &ne);  //输入边数
    Edge e = (Edge)malloc(sizeof(struct ENode));
    for (int i = 0; i < ne; ++i) {
        scanf("%d %d %d", &e->v1, &e->v2, &e->weight);
        InsertEdge(graph, e);
    }
    free(e);

    /* 如果顶点有数据的话，读入数据 */
    for (Vertex v = 0; v < graph->nv; ++v)
        scanf("%c", &(graph->data[v]));

    return graph;
}

bool IsEdge(MGraph graph, Vertex v, Vertex w) {
    return graph->G[v][w] < INF ? true : false;
}

void Visit(Vertex v) {
    printf("正在访问顶点%d\n", v);
}

void BFS(MGraph graph, Vertex v, void (*Visit)(Vertex)) {
    Vertex *q = (Vertex *)malloc(graph->nv * sizeof(Vertex));  //队列
    int front = 0, rear = 0;
    bool * visited = (bool *)malloc(graph->nv * sizeof(bool));
    for (int i = 0; i < graph->nv; ++i)
        visited[i] = false;

    Visit(v);
    visited[v] = true;
    q[rear++] = v;
    while (front != rear) {  //当队列不空
        Vertex tmp = q[front++];  //取出队列首顶点
        for (Vertex w = 0; w < graph->nv; ++w) {
            if (!visited[w] && IsEdge(graph, tmp, w)) {
                Visit(w);
                visited[w] = true;
                q[rear++] = w;
            }
        }
    }
    free(q);
    free(visited);
    return ;
}

Vertex FindMinDistNotCollected(MGraph graph, WeightType dist[], bool collected[]) {
    //找到未收录顶点中dist最小者v
    Vertex minV;
    WeightType minDist = INF;
    for (Vertex v = 0; v < graph->nv; ++v) {
        if (!collected[v] && dist[v] < minDist) {
            minV = v;
            minDist = dist[v];
        }
    }
    if (minDist < INF)  //若找到dist最小的顶点
        return minV;
    else  //若这样的顶点不存在，返回错误标记
        return ERROR;

}

/* 有权图的单源最短路径算法：Dijkstra
 *  初始化：（设算法求顶点v到其他顶点的最短路径）
 *      dist[w]的初始化：若v到w有路，dist[w]为<v,w>的weight，否则dist[w]=INF 
 *      path[]的初始化：-1
 *  算法（贪心）：
 *      令S={源点s + 已确定了最短路径的顶点v}
 *      对任一未收录的顶点v，定义dist[v]为s到v的最短路径长度，但该路径仅经过s中的顶点
 *      1. 找到未收录顶点中dist最小者v，若不存在表示全收录，算法结束
 *      2. 收录v，重新计算与v相邻且未收录的点w的dist和path，回到第1步
 *  注意：
 *      查找未收录顶点dist最小者的方法：
 *          1. 扫描所有————T=O(|V|^2+|E|)，对稠密图效果好
 *          2. 将dist存入最小堆————T=O(|V|log|V|+|E|log|V|)=O(|E|log|V|)，对稀疏图效果好
 */
bool Dijkstra(MGraph graph, WeightType dist[], Vertex path[], Vertex v) {
    bool *collected = (bool *)malloc(graph->nv * sizeof(bool));
    //初始化dist[]和path
    for(Vertex w = 0; w < graph->nv; ++w) {
        dist[w] = graph->G[v][w];
        if (dist[w] < INF && dist[w] != 0)  //若v和w间有路，且v和w不是同一点
            path[w] = v;
        else
            path[w] = -1;
        collected[w] = false;
    }
    //先将起点收入集合S
    dist[v] = 0;
    collected[v] = true;

    while (1) {
        Vertex w = FindMinDistNotCollected(graph, dist, collected);  //w=未被收录顶点中dist最小者
        if (w == ERROR) {  //若这样的顶点不存在
            break;  //算法结束
        }
        collected[w] = true;  //收录w
        for (Vertex i = 0; i < graph->nv; ++i) {  //重新计算与v相邻且未收录的点w的dist和path
            if (!collected[i] && graph->G[w][i] < INF) {
                if (graph->G[w][i] < 0)  //若有负边
                    return false;  //不能正确解决，返回错误标记
                if (dist[w] + graph->G[w][i] < dist[i]) {
                    dist[i] = dist[w] + graph->G[w][i];  //更新dist[i]
                    path[i] = w;  //更新v到i的路径
                }
            }
        }
    }
    free(collected);
    return true;  //算法执行完毕，返回正确标记
}

/* 多源最短路径算法一：直接将单元最短路径算法调用|V|遍 
 *  - T = O(|V|^3 + |E|*|V|)
 */
bool MultSrcPath(MGraph graph, WeightType dist[][MAX_VERTEX_NUM], Vertex path[][MAX_VERTEX_NUM]) {
    bool res = false;
    for (Vertex v = 0; v < graph->nv; ++v) {
        res = Dijkstra(graph, dist[v], path[v], v);
        if (res == false)
            return false;
    }
    return true;
        
}

/* 多源最短路径算法二：Floyd
 *  dist_k[i][j] = 路径 {i -> {l <=k} -> j} 的最小长度     
 *  算法：不断由 dist_k-1 递推 dist_k
 *      - dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])  
 *  - T = O(|V|^3)
 */
bool Floyd(MGraph graph, WeightType dist[][MAX_VERTEX_NUM], Vertex path[][MAX_VERTEX_NUM]) {
    //初始化
    for (Vertex i = 0; i < graph->nv; ++i) 
        for (Vertex j = 0; j < graph->nv; ++j) {
            dist[i][j] = graph->G[i][j];
            if (dist[i][j] < INF && dist[i][j] != 0)  //若i和j间有路，且i和j不是同一点
                path[i][j] = i;
            else
                path[i][j] = -1;
        }
    
    for (Vertex k = 0; k < graph->nv; ++k)
        for (Vertex i = 0; i < graph->nv; ++i)
            for (Vertex j = 0; j < graph->nv; ++j)
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = k;
                    if (i == j && dist[i][j] < 0)  //若发现负边圈
                        return false;  //不能正确解决，返回错误标记
                }
    return true;  //算法执行完毕，返回正确标记
}

Vertex FindMinDist(MGraph graph, WeightType dist[]) {
    //返回未收录顶点中dist最小者（已收录的顶点dist值为0）
    Vertex minV;
    WeightType minDist = INF;
    for (Vertex v = 0; v < graph->nv; ++v) {
        if (dist[v] != 0 && dist[v] < minDist) {  //若顶点v未收录，且dist[v]更小
            minV = v;  //更新最小顶点
            minDist = dist[v];  //更新最小距离
        }
    }
    if (minDist < INF)  //若找到dist最小者
        return minV;  //返回对应顶点的下标
    else  //若这样的顶点不存在
        return ERROR;  //返回错误标记
}

/* 最小生成树(MST)算法：Prim 
 *      ————开局一个点，让一棵小树慢慢长大（类似于Dijstra，也是贪心算法）
 *  最小生成树：
 *      - 生成树：包含全部顶点的树，向其中任加一条边都一定构成回路
 *      - 最小：边的权重和最小
 *  贪心算法：
 *      1. 收录未收录顶点中到MST距离最小的顶点，若找不到，算法结束
 *      2. 更新与刚收录顶点相邻的顶点的dist[]和parent[]，重复第1步
 *  T = O(|V|^2)
 */
WeightType Prim(MGraph graph, MGraph MST) {
    //MST用于保存产生的最小生成树
    //返回最小权重和
    WeightType *dist = (WeightType *)malloc(graph->nv * sizeof(WeightType));
    Vertex *parent = (Vertex *)malloc(graph->nv * sizeof(Vertex));
    int vCount;  //记录MST收录的顶点数
    WeightType totalWeight;  //权重和

    //初始化，默认初始点下标为0
    for (Vertex v = 0; v < graph->nv; ++v) {
        dist[v] = graph->G[0][v];
        parent[v] = 0;  //暂且定义所有结点的父结点都是初始点0
    }
    vCount = 0;  //初始化收录的顶点数
    totalWeight = 0;  //初始化权重和
    //建立包含所有顶点但没有边的图（本来应该用图的邻接表版本的，但奈何MGraph.h和LGraph.h中的同名函数太多，难以共用）
    // MST = CreateGraph(graph->nv);  //应该在主函数中创建好作为形参传入

    //将初始点0收录进MST
    dist[0] = 0;
    parent[0] = -1;
    ++vCount;

    while (1) {
        Vertex v = FindMinDist(graph, dist);  //v=未被收录顶点中dist最小者
        if (v == ERROR)  //若这样的顶点不存在
            break;  //算法结束
        
        //将v及其与MST相连的边<parent[v], v>收录进MST
        Edge e = (Edge)malloc(sizeof(struct ENode));
        e->v1 = parent[v];
        e->v2 = v;
        e->weight = dist[v];
        InsertEdge(MST, e);
        dist[v] = 0;
        ++vCount;
        totalWeight += dist[v];

        //更新与刚收录顶点相邻的顶点的dist[]和parent[]
        for (Vertex w = 0; w < graph->nv; ++w) {
            if (dist[w] != 0 && graph->G[v][w] < INF) {  //若w未收录，且与v相邻
                if (graph->G[v][w] < dist[w]) {  //若收录v使得dist[w]变小
                    dist[w] = graph->G[v][w];  //更新dist[w]
                    parent[w] = v;  //更新树
                }
            }
        }
    }

    if (vCount < graph->nv)  //若MST中的顶点数不到|V|，说明图不连通，无法形成生成树
        totalWeight = ERROR;
    free(dist);
    free(parent);
    return totalWeight;  //算法执行完毕，返回最小权重和或错误标记
}