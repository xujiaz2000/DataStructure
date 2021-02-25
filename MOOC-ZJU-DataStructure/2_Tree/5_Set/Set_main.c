//有n台电脑，用网线连接后可以通信
#include <stdio.h>
#include <stdlib.h>
#include "Set.h"

//输入并连接两台电脑
void InputConnect(Set s) {
    ElementType x1, x2;
    scanf("%d %d", &x1, &x2);
    Union(s, x1, x2);
}

//输入并检查是否有连接
void CheckConnect(Set s) {
    ElementType x1, x2;
    scanf("%d %d", &x1, &x2);
    int root1, root2;
    root1 = Find(s, x1);
    root2 = Find(s, x2);
    if (root1 == root2) printf("yes\n");
    else printf("no\n");
}

//输出当前并查集中有几个集合
void CheckNetwork(Set s) {
    int count = 0;
    for (int i = 0; i < s->size; ++i) {
        if (s->data[i].parent < 0)
            ++count;
    }
    if (count == 1)
        printf("The network is connected.\n");
    else    
        printf("There are %d components.\n", count);
    return ;
}

int main()
{
    int n;
    scanf("%d", &n);
    Set s = CreateSet(n);
    char inp;
    do {
        scanf("%c", &inp);
        switch (inp) {
            case 'I':
                InputConnect(s);
                break;
            case 'C':
                CheckConnect(s);
                break;
            case 'S':
                CheckNetwork(s);
                break;
        }
    } while (inp != 'S');
    return 0;
}