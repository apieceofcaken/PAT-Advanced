/*
感谢：https://github.com/OliverLew/PAT/blob/master/PATAdvanced/1003.c

给定一无向图，包含边权与点权，找到某两点间（边权）最短路径的条数，并且输出所有最短路径中点权和最大值。 
输入示例：
       5 6 0 2      顶点个数、边个数、起始点编号、终点编号
       1 2 1 5 3    各顶点权
       0 1 1        边连接的两顶点编号、边的权值，每行代表一条边
       0 2 2
       0 3 1
       1 2 1
       2 4 1
       3 4 1
输出示例：
       2 4          最短路径条数 最短路径中点权和最大值     

思路：
  修改图的存储结构与dijiastra算法，记录起点到当前节点最短路径条数。

代码结构：
  一、创建图的邻接表存储数据结构，节点中增加npath、totalrescue以记录给定起点到该点的最短路径条数与最短路径上点权和最大值。
  二、Read(Graph G) -- 从输入数据第二行开始，建立图。
  三、ModifiedDijkstra(Graph G) -- 修改后的dijkstra，以求最短路径条数，修改后的dijkstra不记录路径上点的顺序。
  四、main() -- 输入第一行并分配空间--->Read(Graph G)--->ModifiedDijkstra(Graph G)--->输出
---------------------------------------------代码部分-----------------------------------------------------
*/

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>  //各基本数据结构的边界值
#include<stdbool.h> //包含bool数据类型，true , false

#define INF INT_MAX

typedef struct Vertex *Vertex, *Vertexes;
typedef struct Adj *Adj, *Adjs;
typedef struct Graph *Graph, *Graph;

struct Vertex{          //顶点结构体
    int id;             //顶点编号
    bool collected;     //结点是否被收录
    int dist;           //起点到该点的最短路径长度，传统Dijiastra用一个dist[]来记录，这里绑定在了结构体中，很好
    int localrsc;       //当前节点权值（城市救援队数量）
    int totrsc;         //最短路径中最大点权值和
    int npath;          //最短路径条数（不记录具体路径，只进行计算）
    Adj firstarc;       //该点相连的第一条边，初始为空
};

struct Adj{             //边的结构体，存储有向边，无向图需要建立两条
    int id;             //边的另一端点
    int length;         //边的权值（长度）
    Adj iter;           //共起点的另一条边，若是最后一条，则值为NULL
};

struct Graph{           //图的结构体
       Vertexes vs;     //顶点集基址（使用时分配存储空间）
       Adjs es;         //边集基址（使用时分配存储空间）
       int nvertex;     //顶点数量
       int nadj;        //边数量
};

void Read(Graph G)      //初始化图中顶点信息及边信息，从第二行开始读
{
    //输入点权
    int localrsc;
    for(int i = 0; i < G->nvertex; i++)
    {
        Vertex v = G->vs + i;    //等价于 v = G->vs[i]
        scanf("%d", &localrsc);  //第二行数据
        v->id           = i;
        v->collected    = false;
        v->dist         = INF;
        v->localrsc     = localrsc;
        v->totrsc       = localrsc;
        v->npath        = 0;
        v->firstarc     = NULL;
    }
    
    //输入边
    int id1, id2, length;
    for(int i = 0; i < G->nadj; i++)
    {
        scanf("%d %d %d", &id1, &id2, &length);     //输入一条无向边的信息，需要按有向边更新两次
        //从id1到id2
        Adj e = G->es + i;
        e->id           = id2; //终点
        e->length       = length;
        e->iter         = G->vs[id1].firstarc;      //id1为起点，将e1（id1到id2）插入点id1的出边的单链表中
        G->vs[id1].firstarc = e;
        e++; i++;
        //从id2到id1
        e->id           = id1; //终点
        e->length       = length;                   
        e->iter         = G->vs[id2].firstarc;      //id2为起点，将e2（id2到id1）插入点id2的出边的单链表中
        G->vs[id2].firstarc = e;
    }
    
}

//用Dijiastra算法思想寻找最短路，并用顶点中的npath保存起始点到该点最短路的条数，
//totrsc保存所有最短路中点权和最大值
void ModifiedDijkstra(Graph G)
{
    Vertex v, w;
    int minUnknownDist;
    while(true)
    {
        //找未收录顶点中dist最小者
        v = NULL;
        minUnknownDist = INF;
        for(w = G->vs; w < &G->vs[G->nvertex]; w++) //遍历G的所有顶点
            if(!w->collected && w->dist < minUnknownDist)
            {
                minUnknownDist = w->dist;
                v = w;
            }
        if(v == NULL) break; //程序完成，跳出
        
        v->collected = true;
        for(Adj e = v->firstarc; e!=NULL; e = e->iter) if(!G->vs[e->id].collected)
        {
            w = G->vs + e->id;
            if(v->dist + e->length < w->dist)
            {
                w->npath = v->npath;
                w->totrsc = w->localrsc + v->totrsc;
                w->dist = v->dist + e->length;
            }
            //最短距离相同的边，更新npath和totrsc
            else if(v->dist + e->length == w->dist)
            {
                w->npath += v->npath;
                if(w->totrsc < w->localrsc + v->totrsc)
                    w->totrsc = w->localrsc + v->totrsc;
            }
        }
    }
}

int main()
{   
    int N, M, C1, C2;
    scanf("%d %d %d %d", &N, &M, &C1, &C2);
    
    //创建图变量
    Vertexes vs = (Vertexes)malloc(N * sizeof(struct Vertex));
    Adjs es = (Adjs)malloc(2 * M * sizeof(struct Adj));
    struct Graph sG = {.vs = vs, .es = es, .nvertex = N, .nadj = 2 * M};
    Graph G = &sG;
    
    //读取所有数据，建立图
    Read(G);
    G->vs[C1].dist = 0;
    G->vs[C1].npath = 1;
    
    //找最短路径数 和 最大点权和
    ModifiedDijkstra(G);
    
    printf("%d %d", G->vs[C2].npath, G->vs[C2].totrsc);
    
    return 0;
}
    
                    
                
        
        
        
        
        
        


    
    
       
  
