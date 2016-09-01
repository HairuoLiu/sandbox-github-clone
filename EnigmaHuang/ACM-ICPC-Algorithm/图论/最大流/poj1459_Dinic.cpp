#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<queue>

using namespace std;

#define min(x,y) ((x<y)?(x):(y))

#define INF 0x3f3f3f3f
#define MaxPoint 110 

struct{
    int src,trg,cap,next,pair;
}edge[MaxPoint*MaxPoint];

int dis[MaxPoint];               //��Դ����룬���ֲ�ͼ      
int n,np,nc,m,ANS;               //NΪ������MΪ����

int ne,source,target;
int head[MaxPoint];

void addedge(int u,int v,int c1,int c2)
{
    edge[ne].src = u;
    edge[ne].trg = v;
    edge[ne].cap = c1;
    edge[ne].next = head[u];
    edge[ne].pair = ne+1;
    head[u] = ne ++;
    edge[ne].src = v;
    edge[ne].trg = u;
    edge[ne].cap = c2;
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

void ReadData()
{
    int src,trg,cap,i,j;
	int c[MaxPoint][MaxPoint];
	memset(c,0,sizeof(c));
	ne=1;
	memset(head,-1,sizeof(head)); 
    for (i=0;i<m;i++)
	{
        scanf(" (%d,%d)%d",&src,&trg,&cap);
        c[src+1][trg+1]+=cap;
        c[trg+1][src+1]+=0;
	}
    
    for (i=0;i<np;++i)
    {
        scanf(" (%d)%d",&src,&cap);
        c[source][src+1]+=cap;
    }
    
    for (i=0;i<nc;++i)
    { 
        scanf(" (%d)%d",&src,&cap);
        c[src+1][target]+=cap;  
    }
    
    for (i=1;i<=n+2;i++)
	    for (j=1;j<=i;j++)
	        if ((c[i][j]>0) || (c[j][i]>0)) 
	            addedge(i,j,c[i][j],c[j][i]);
} 

int main()
{
	freopen("poj1459.txt","r",stdin);
	freopen("poj1459ans.txt","w",stdout);
    int newcap,testcase=0;
    while (scanf("%d %d %d %d",&n,&np,&nc,&m)!=EOF)
    {
		source=n+1;
		target=n+2;
		testcase++;
        ReadData();
	    ANS=0;
        while(BFS())//Ҫ��ͣ�ؽ����ֲ�ͼ,���BFS�������Ž���
        {
	        //һ��BFSҪ��ͣ��������·,ֱ���Ҳ���Ϊֹ
            while(newcap=find(source,INF)) ANS+=newcap;
        }    
        printf("testcase : %d\n",testcase);
        printf("%d %d %d %d\n",n,np,nc,m);
        printf("%d\n",ANS);
    }     
}
