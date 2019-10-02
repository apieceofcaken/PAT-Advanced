/*树的层次遍历，每层记录无孩子节点的数量，使用树的链式存储结构
  使用邻接链表
*/
#include<stdio.h>;
#include<stdlib.h>;
#include<stdbool.h>;

#define Max 99;

typedef struct Child *Child;
typedef struct Node *Node;
typedef struct Tree *Tree;

struct Child{ 
    int id;
    Child next;
}

struct Node{
    int level;
    Child first_child;   
}

struct Tree{
    struct Node node[Max];
    int node_count;
    int non_leaf_count;
    int level_leaf[Max];
}

void Read(Tree t)
{
    int id, k;
    Node v = t->node
    Child child;
    scanf("%d %d", &id, &k);
    for(int i = 1; i <= k; i++)
    {
       child = (Child)malloc(sizeof(struct Child));
       v[i].level += 1;
       child->id = i;
       child->next = v[id].first_child;
       v[id].first_child = child;
    }
} 
