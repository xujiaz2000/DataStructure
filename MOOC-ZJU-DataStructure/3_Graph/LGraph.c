#include <stdio.h>
#include <stdlib.h>
#include "LGraph.h"

LGraph CreateGraph(int vertexNum) {
    //初始化一个有vertexNum个顶点没有边的图
    LGraph graph = (LGraph)malloc(sizeof(struct LGNode));
    graph->nv = vertexNum;
    graph->ne = 0;
    
    //初始化邻接表头指针
    for (Vertex i = 0; i < graph->nv; ++i)
        graph->G[i].firstEdge = NULL;
    
    return graph;
}

void InsertEdge(LGraph graph, Edge e) {
    PtrToAdjVNode newNode;
    //插入边<v1, v2>
    //为v2建立新的邻接点
    newNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    newNode->adjv = e->v2;
    newNode->weight = e->weight;
    //将v2插入v1的表头
    newNode->next = graph->G[e->v1].firstEdge;
    graph->G[e->v1].firstEdge = newNode;

    // //若是无向图，还要以同样的方式插入边<v2, v1>
    // PtrToAdjVNode newNode2;
    // newNode2 = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    // newNode2->adjv = e->v1;
    // newNode2->weight = e->weight;
    // //将v2插入v1的表头
    // newNode2->next = graph->G[e->v2].firstEdge;
    // graph->G[e->v2].firstEdge = newNode2;

    ++graph->ne;

    return ;
}

LGraph BuildGraph() {
    //输入：顶点数，边数，边
    //返回：图
    int nv, ne;
    scanf("%d", &nv);  //读入顶点个数
    LGraph graph = CreateGraph(nv);
    scanf("%d", &ne);  //读入边数
    Edge e = (Edge)malloc(sizeof(struct ENode));
    for (int i = 0; i < ne; ++i) {  //读入边
        scanf("%d %d %d", &e->v1, &e->v2, &e->weight);
        InsertEdge(graph, e);
    }
    free(e);

    //如果顶点有数据的话，读入数据
    for (Vertex v = 0; v < graph->nv; ++v)
        scanf("%c", &(graph->G[v].data));
    
    return graph;
}

void Visit(Vertex v) {
    printf("正在访问顶点%d\n", v);
    return ;
}

bool *visited;

void _DFS(LGraph graph, Vertex v, void (*Visit)(Vertex)) {
    Visit(v);
    visited[v] = true;
    for (PtrToAdjVNode p = graph->G[v].firstEdge; p; p = p->next) {  //对V的每个邻接点W->AdjV
        if (!visited[p->adjv])
            _DFS(graph, p->adjv, Visit);
    }
    return ;
}

void DFS(LGraph graph, Vertex v, void (*Visit)(Vertex)) {
    visited = (bool *)malloc(graph->nv * sizeof(bool));
    for (int i = 0; i < graph->nv; ++i)
        visited[i] = false;
    _DFS(graph, v, Visit);
    free(visited);
    return ;
}

//无权图的单源最短路径算法
void Unweighted(LGraph graph, int dist[], int path[], Vertex v) {
    //求顶点v到其他顶点的最短路径，算法类似于BFS
    //dist[]和path[]全部初始化为-1
    //dist[w]：v到w的最短距离（dist[v] = 0）
    //path[w]：v到w的路线经过的最后一个点（利用栈可以得到正序路径）
    for (Vertex i = 0; i < graph->nv; ++i) {
        dist[i] = -1;
        path[i] = -1;
    }
    Vertex *q = (Vertex  *)malloc(graph->nv * sizeof(Vertex));  //队列
    int front = 0, rear = 0;  //队列首、尾后指针
    q[rear++] = v;
    dist[v] = 0;
    while (front != rear) {  //当队列非空
        Vertex currV = q[front++];
        PtrToAdjVNode p = graph->G[currV].firstEdge;
        while (p && dist[p->adjv] == -1) {
            dist[p->adjv] = dist[currV] + 1;
            path[p->adjv] = currV;
            q[rear++] = p->adjv;
            p = p->next;
        }
    }
    free(q);
    return ;
}

/* 最小生成树算法：Kruskal
 *      ————开局先将每个结点看作一棵树，通过不断地收录符合要求的最小边，将森林合并成树
 *  最小生成树：
 *      - 生成树：包含全部顶点的树，向其中任加一条边都一定构成回路
 *      - 最小：边的权重和最小
 *  贪心算法：
 *      1. （当MST中不到|V|-1条边，且eSet中还有边）从eSet中取权重最小的边e（最小堆），将e从eSet中删除
 *      2. 若e不在MST构成的回路中（并查集），将e加入MST，否则彻底无视e
 *      3. 重复第1步
 *  （算法用到了最小堆和并查集，都在后面有实现）
 * - T = O(|E|log|E|)
 */

/*-------------------- 顶点并查集定义 --------------------*/
typedef Vertex ElementType;  //并查集的元素类型是顶点，默认元素可以用非负整数表示
typedef Vertex SetName;      //集合名称默认用根结点的下标表示
typedef ElementType SetType[MAX_VERTEX_NUM];  //并查集，用数组表示，假设集合元素下标从0开始 
/* 并查集用数组表示，数组下标为data，对应的值为parent */

void InitVSet(SetType s, int n) {
    //初始化顶点并查集
    for (ElementType x = 0; x < n; ++x)
        s[x] = -1;
}

void Union(SetType s, SetName root1, SetName root2) {
    //并查集的“并”操作
    //默认root1和root2不是同一个集合的根结点
    //保证小集合并入大集合
    if (s[root1] < s[root2]) {  //若集合1较大，应将集合2并入集合1
        s[root1] += s[root2];
        s[root2] = root1;
    }
    else {  //若集合2较大，应将集合1并入集合2
        s[root2] += s[root1];
        s[root1] = root2;
    }
    return ;
}

SetName Find(SetType s, ElementType x) {
    if (s[x] < 0)  //找到集合的根
        return x;
    else
        return s[x] = Find(s, s[x]);  //路径压缩
}

bool CheckCycle(SetType s, Vertex v1, Vertex v2) {
    //若连接v1和v2的边能在现有的最小生成树子集中构成回路，返回true
    //即在顶点v1和顶点v2属于一个连通集时，返回true
    Vertex root1 = Find(s, v1);  //得到v1所属的连通集名称
    Vertex root2 = Find(s, v2);  //得到v2所属的连通集名称
    if (root1 == root2)  //若v1和v2已连通，则该边不能要
        return false;
    else {  //否则允许收录该边
        Union(s, root1, root2);  //并将v1和v2并入同一个连通集
        return true;
    }
}
/*-------------------- 并查集定义结束 --------------------*/

/*-------------------- 边的最小堆定义 --------------------*/
void PercDown(Edge eSet, int p, int n) {
    //Edge是指向边数组首元素的指针，p是要调整为最小堆的根结点所对应的下标，n是边数组的长度
    //将有n个元素的边数组中以eSet[p]为根的子堆调整为关于weight的最小堆
    //（假设其左右子树已是最小堆）只需下滤边eSet[p]即可
    struct ENode e = eSet[p];  //取出根结点存储的值
    //p用来存储根结点e应该在的位置
    while (2 * p + 1 < n) {  //当左孩子存在
        //注：边数组下标从0开始，故左结点对应下标为：2 * i + 1
        p = 2 * p + 1;  //p暂时取左孩子
        if (p + 1 < n && eSet[p + 1].weight < eSet[p].weight)  //若右孩子存在，且右孩子weight较小
            ++p;  //p取左右孩子中较小者
        if (e.weight <= eSet[p].weight) { //若e不大于左右孩子，即找到合适位置
            p = (p - 1) / 2;
            break;
        } 
        else 
            eSet[(p - 1) / 2] = eSet[p];  //下滤
    }
    eSet[p] = e;
    return ;
}

void InitESet(LGraph graph, Edge eSet) {
    //将图的边存入边数组eSet，并初始化为最小堆
    int eCount = 0;

    //图的边存入数组eSet
    for (Vertex v = 0; v < graph->nv; ++v) 
        for (PtrToAdjVNode w = graph->G[v].firstEdge; w; w = w->next)
            if (v < w->adjv) { //避免重复收录无向图的边，只收v1<v2的边
                eSet[eCount].v1 = v;
                eSet[eCount].v2 = w->adjv;
                eSet[eCount].weight = w->weight;
                ++eCount;
            }
    
    //将eSet初始化为最小堆
    for (eCount = graph->ne / 2; eCount >= 0; --eCount)
        PercDown(eSet, eCount, graph->ne);

    return ;
}

int GetMinEdge(Edge eSet, int currSize) {
    //给定当前堆的大小currSize，返回将最小的边位置下标，并将其从最小堆中弹出
    
    //将最小边与当前最小堆中的最后一个位置互换
    struct ENode tmp = eSet[0];
    eSet[0] = eSet[currSize - 1];
    eSet[currSize - 1] = tmp;
    
    //将剩下的边数组继续调整成最小堆
    PercDown(eSet, 0, currSize - 1);

    return currSize - 1;  //返回最小边所在的位置
}
/*-------------------- 最小堆定义结束 --------------------*/

WeightType Kruskal(LGraph graph, LGraph MST) {
    //将最小生成树保存为邻接表存储的图MST，返回最小权重和
    WeightType totalWeight;  //权重和
    int eCount;  //收录的边数
    SetType vSet;  //顶点数组，并查集
    Edge eSet;  //边数组，最小堆

    //初始化
    totalWeight = 0;  //初始化权重和
    eCount = 0;  //初始化收录的边数
    InitVSet(vSet, graph->nv);  //初始化顶点并查集
    eSet = (Edge)malloc(graph->ne * sizeof(struct ENode));
    InitESet(graph, eSet);  //初始化边的最小堆
    
    int nextEdge = graph->ne;  //原始边集的规模
    while (eCount < graph->nv - 1) {  //若MST中不到|V|-1条边
        nextEdge = GetMinEdge(eSet, nextEdge);
        if (nextEdge < 0)  //若边集为空
            break;
        //若该边不会在现有的MST子集中构成回路，即改边的两点不属于同一连通集
        if (CheckCycle(vSet, eSet[nextEdge].v1, eSet[nextEdge].v2) == true) {
            InsertEdge(MST, eSet + nextEdge);  //将该边插入MST
            totalWeight += eSet[nextEdge].weight;  //累计权重
            ++eCount;  //生成树中边数加1
        }
        //else 彻底无视该边（它已被弹出最小堆）
    }
    if (eCount < graph->nv - 1)  //若生成树不存在
        totalWeight = -1;  //设置错误标记，表示生成树不存在
    return totalWeight;
}

/* 拓扑排序 */
bool TopSort(LGraph graph, Vertex topOrder[]) {
    //对Graph进行拓扑排序,  TopOrder[]顺序存储排序后的顶点下标
    int *indegree = (int *)malloc(graph->nv * sizeof(int));  //入度数组，用于记录每个顶点的入度
    Vertex *q = (Vertex *)malloc(graph->nv * sizeof(Vertex));  //队列
    int front = 0, rear = 0;  //队列首、尾后指针

    //初始化indegree[]
    for (int i = 0; i < graph->nv; ++i)
        indegree[i] = 0;
    
    //遍历图，得到indegree[]
    for (Vertex v = 0; v < graph->nv; ++v)
        for (PtrToAdjVNode w = graph->G[v].firstEdge; w; w = w->next)
            ++indegree[w->adjv];  //对有向边<v, w->adjV>累计终点的入度
    
    //将所有入度为0的顶点入队列
    for (Vertex v = 0; v < graph->nv; ++v)
        if (indegree[v] == 0)
            q[rear++] = v;
    
    //拓扑排序
    int cnt = 0;
    while (front != rear) {  //若队列不空
        Vertex v = q[front++];  //取出队首顶点
        topOrder[cnt++] = v;  //将之存为结果序列的下一个元素
        for (PtrToAdjVNode w = graph->G[v].firstEdge; w; w = w->next)  //对V的每个邻接点
            if (--indegree[w->adjv] == 0)  //若删除v使得w入度为0 
                q[rear++] = w->adjv;  //则该顶点入列
    }

    free(indegree);
    free(q);

    if (cnt != graph->nv)
        return false;  //说明图中有回路, 返回不成功标志
    else
        return true;
}