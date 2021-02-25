/******************************************************
 * 图（Graph）：表示”多对多“的关系。包含：一组顶点和一组边（不考虑重边和自回路）
 * 
 * 实现方式：
 *  - 邻接矩阵
 *  - 邻接表 *
 ******************************************************/

#ifndef LGRAPH_H
#define LGRAPH_H
#include <stdbool.h>

#define MAX_VERTEX_NUM 100
typedef int Vertex;  //用顶点下标表示顶点
typedef int WeightType;  //边的权值类型
typedef char DataType;  //顶点存储的数据类型

/* 数据对象集 */
//边的定义
typedef struct ENode *PtrToENode;
struct ENode {
    Vertex v1, v2;  //有向边<v1, v2>
    WeightType weight;  //权重
};
typedef PtrToENode Edge;

//邻接点的定义
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode {
    Vertex adjv;  //邻接点下标
    WeightType weight;  //边权重
    PtrToAdjVNode next;  //指向下一个邻接点的指针
};

//顶点表头结点的定义
typedef struct VNode {
    /* 注意：很多情况下，顶点无数据，此时Data可以不用出现 */
    DataType data;  //存顶点的数据
    PtrToAdjVNode firstEdge;  //边表头指针
} AdjList[MAX_VERTEX_NUM];  //AdjList是邻接表类型

//图结点的定义
typedef struct LGNode *PtrToGNode;
struct LGNode {
    int nv;  //顶点数
    int ne;  //边数
    AdjList G;  //邻接表
};
typedef PtrToGNode LGraph;  //以邻接表方式存储的图类型

/* 操作集 */
LGraph CreateGraph(int vertexNum);
void InsertEdge(LGraph graph, Edge e);
LGraph BuildGraph();
void Visit(Vertex v);
void DFS(LGraph graph, Vertex v, void (*Visit)(Vertex));
void Unweighted(LGraph graph, int dist[], int path[], Vertex v);
WeightType Kruskal(LGraph graph, LGraph MST);
bool TopSort(LGraph graph, Vertex topOrder[]);

#endif
