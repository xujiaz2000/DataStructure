/******************************************************
 * 图（Graph）：表示”多对多“的关系。包含：一组顶点和一组边（不考虑重边和自回路）
 * 
 * 实现方式：
 *  - 邻接矩阵 *
 *  - 邻接表
 * 
 * 注：生成有向图和无向图的转换可在InsertEdge函数中修改
 ******************************************************/

#ifndef MGRAPH_H
#define MGRAPH_H
#include <stdbool.h>

/* 数据对象集 */
#define MAX_VERTEX_NUM 100  //最大顶点数
#define INF 65535  //双字节无符号数的最大值，表示两条边间没有路
typedef int Vertex;  //用顶点下标表示顶点
typedef int WeightType;  //边的权值类型
typedef char DataType;  //顶点存储的数据类型
#define ERROR -1  //错误标记，找不到未收录顶点中dist最小者时返回的；无法形成最小生成树时返回

//边的定义
typedef struct ENode *PtrToENode;
struct ENode {
    Vertex v1, v2;  //有向边<v1, v2>
    WeightType weight;  //权重
};
typedef PtrToENode Edge;

//图结点的定义
typedef struct MGNode *PtrToGNode;
struct MGNode {
    int nv;  //顶点数
    int ne;  //边数
    WeightType G[MAX_VERTEX_NUM][MAX_VERTEX_NUM];  //邻接矩阵
    DataType data[MAX_VERTEX_NUM];  //存顶点的数据
    /* 注意：很多情况下，顶点无数据，此时Data[]可以不用出现 */
};
typedef PtrToGNode MGraph;  //指向以邻接矩阵存储的图的类型

/* 操作集 */
MGraph CreateGraph(int vertexNum);
void InsertEdge(MGraph graph, Edge e);
MGraph BuildGraph();
void Visit(Vertex v);
void BFS(MGraph graph, Vertex v, void (*Visit)(Vertex));
bool Dijkstra(MGraph graph, WeightType dist[], Vertex path[], Vertex v);
bool MultSrcPath(MGraph graph, WeightType dist[][MAX_VERTEX_NUM], Vertex path[][MAX_VERTEX_NUM]);
bool Floyd(MGraph graph, WeightType dist[][MAX_VERTEX_NUM], Vertex path[][MAX_VERTEX_NUM]);
WeightType Prim(MGraph graph, MGraph MST);

#endif
