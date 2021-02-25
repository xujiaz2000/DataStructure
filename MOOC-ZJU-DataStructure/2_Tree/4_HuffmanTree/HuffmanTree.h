/******************************************************
 * 哈夫曼树：又称为最优二叉树，是WPL最小的二叉树
 *  - 作用：根据结点不同的查找频率构造出的更加有效的搜索树
 *  - 带权路径长度（WPL）：WPL是每个叶子结点的带权路径长度之和，即 WPL = the sigma of (w_k * l_k) from k=1 to n, 
 *      - n为二叉树中的叶子结点数，l_k为从根结点到第k个叶子结点的路径长度，w_k为第k个叶子结点的权值
 *  - 哈夫曼树的构造：每次把权值最小的两棵二叉树合并，新的二叉树权值为它们的和
 ******************************************************/

#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H
#include "../3_Heap/Heap.h"

/*  数据对象集 */
typedef struct TreeNode *HuffmanTree;
struct TreeNode {
    int weight;
    HuffmanTree left;
    HuffmanTree right;
};

/* 操作集 */
HuffmanTree BuildHuffmanTree(Heap h);

#endif
