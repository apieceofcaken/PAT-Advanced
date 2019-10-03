/*
A family hierarchy is usually presented by a pedigree tree. Your job is to count those family members who have no child.

Input Specification:
Each input file contains one test case. Each case starts with a line containing 0<N<100, the number of nodes in a tree, and M (<N), the number of non-leaf nodes. Then M lines follow, each in the format:

ID K ID[1] ID[2] ... ID[K]
where ID is a two-digit number representing a given non-leaf node, K is the number of its children, followed by a sequence of two-digit ID's of its children. For the sake of simplicity, let us fix the root ID to be 01.

The input ends with N being 0. That case must NOT be processed.

Output Specification:
For each test case, you are supposed to count those family members who have no child for every seniority level starting from the root. The numbers must be printed in a line, separated by a space, and there must be no extra space at the end of each line.

The sample case represents a tree with only 2 nodes, where 01 is the root and 02 is its only child. Hence on the root 01 level, there is 0 leaf node; and on the next level, there is 1 leaf node. Then we should output 0 1 in a line.

Sample Input:
2 1
01 1 02
Sample Output:
0 1
*/


//使用邻接链表存储结构表示树

#include<stdio.h>
#include<stdlib.h>


#define Max 999

typedef struct Child *Child;
typedef struct Node *Node;


struct Child{ 
    int id;
    Child next;
};

struct Node{
    int level;
    Child first_child;   
};


int main()
{
    struct Node node[120];          //node[]存放树的节点，count[层数]记录每层叶子节点数
    int count[100];
    int n, m, i;
    int id, k, child_id, max_level;
    Child child = NULL;

    scanf("%d %d", &n, &m);         //初始化，node[1]层数为0，所有node[].first_child指空
    node[1].level = 0;
    for(i = 1; i <= n; i++)
    {
        node[i].first_child = NULL;
		    node[i].level = Max;
        count[i - 1] = 0; 
    }
	node[1].level = 0;

    
    for(i = 1; i <= m; i++)     //读取所有节点的孩子信息
    {
        scanf("%d %d", &id, &k);
        
        while(k-- > 0)
        {
            scanf("%d", &child_id); //记录孩子的编号
            child = (Child)malloc(sizeof(struct Child));
            child->id = child_id;

            child->next = node[id].first_child;//将该孩子插入节点的孩子链表
            node[id].first_child = child;
            
        }
    }
//按层号每层遍历一次链表，找到相应层的节点，如果是叶子，则更新count；如果非叶子，则更新孩子的层号
//原本是在建树的时候更新孩子层号，但1，3例无法通过，怀疑是未按节点号增序输入，父节点层号未更新的情况下就更新孩子层号
//分离层号更新部分，重新按层号增序更新就通过了
    int level, flag = n;
    for(level = 0; flag; level++) 
    {
        for(i = 1; i <= n; i++) if(node[i].level == level)
        {
            flag--;
            if(node[i].first_child == NULL)
                count[level]++;
            
            for(child = node[i].first_child; child; child = child->next)
                node[child->id].level = level + 1;
        }
    }

    max_level = level - 1;

    printf("%d", count[0]);                  //输出所有层次无孩子的节点数量
    for(i = 1; i <= max_level; i++) printf(" %d", count[i]);

    return 0;
}
