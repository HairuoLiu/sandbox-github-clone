#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<queue>

using namespace std;

#define min(x,y) ((x<y)?(x):(y))

#define INF 0x7fffffff
#define MaxPoint 250

struct{
    int src,trg,cap,next,pair;
}edge[MaxPoint*MaxPoint];

int dis[MaxPoint];               //��Դ����룬���ֲ�ͼ      
int N,M,ANS;                     //NΪ������MΪ����

int ne,source,target;
int head[MaxPoint];

void addedge(int u, int v, int c)
{
    edge[ne].src = u;
    edge[ne].trg = v;
    edge[ne].cap = c;
    edge[ne].next = head[u];
    edge[ne].pair = ne+1;
    head[u] = ne ++;
    edge[ne].src = v;
    edge[ne].trg = u;
    edge[ne].cap = 0;
    edge[ne].next = head[v];
    edge[ne].pair = ne-1;
    head[v] = ne ++;
}

int BFS()   
{
    int i,j;
    queue<int> q;
    memset(dis,0xff,sizeof(dis));  //��-1�����Ϊδ���ʵı��   
    dis[source]=0;                 //Դ��ķֲ�Ϊ0
    q.push(source);
    while (!q.empty())
    {
        i=q.front();
        q.pop();
        for (i=head[i];i>0;i=edge[i].next) if (dis[edge[i].trg]<0 && edge[i].cap>0)
        {
            dis[edge[i].trg]=dis[edge[i].src]+1;
            q.push(edge[i].trg);
            if (edge[i].trg==target) break; 
        }
    }
    if (dis[target]>0) return 1; else return 0; //����DISС����,����BFS�������
}
 
//find����һ������,�������ر������������,����0��ʾ�޷�����   
//low��Դ�㵽������խ��(ʣ��������С)�ıߵ�ʣ������     
int find(int x,int low)
{
    int i,newcap=0;
    if (x==target) return low; //�ǻ�㣬ֱ�ӷ���
    for (i=head[x];i>0;i=edge[i].next) 
    {
        if (edge[i].cap>0 && dis[edge[i].trg]==dis[x]+1 && (newcap=find(edge[i].trg,min(low,edge[i].cap))))
        //   ��ͨ        ��         �Ƿֲ�ͼ����һ��    ��    �ܵ����(��������newcap<>0)    
        {
            edge[i].cap-=newcap;
            edge[edge[i].pair].cap+=newcap;
            return newcap;
        }
    }

    return 0;
}

int main()
{
    freopen("poj1273.txt" ,"r",stdin);
    freopen("poj1273ans.txt","w",stdout);
    int i,src,trg,cap,newcap;
    while (scanf("%d%d",&M,&N)!=EOF)
    {
        memset(head,-1,sizeof(head));
		ne=1;
        for (i=1;i<=M;i++)
        {
            scanf("%d%d%d",&src,&trg,&cap);
            addedge(src,trg,cap);
        }
	    ANS=0;
	    source=1;
	    target=N;
        while(BFS())//Ҫ��ͣ�ؽ����ֲ�ͼ,���BFS�������Ž���
        {
	    //һ��BFSҪ��ͣ��������·,ֱ���Ҳ���Ϊֹ
            while(newcap=find(1,INF)) ANS+=newcap;
        }    
        printf("%d\n",ANS);
    }     
}
