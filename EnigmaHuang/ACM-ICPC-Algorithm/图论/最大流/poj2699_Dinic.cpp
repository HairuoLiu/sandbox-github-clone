#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<queue>
using namespace std;

#define INF 0x3f3f3f3f
#define MaxPoint 60

struct{
    int src,trg,cap,next,pair;
}edge[MaxPoint*MaxPoint];
int dis[MaxPoint];    
int head[MaxPoint];
int ne,source,target;

int n,m,gamenum,ans,a[10],id[MaxPoint][MaxPoint];               

void AddEdge(int u, int v, int c)
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
        }
    }
    if (dis[target]>0) return 1; else return 0; //����DISС����,����BFS�������
}
 
//find����һ������,�������ر������������,����0��ʾ�޷�����   
//low��Դ�㵽������խ��(ʣ��������С)�ıߵ�ʣ������     
int Find(int x,int low)
{
    int i,newcap=0;
    if (x==target) return low; //�ǻ�㣬ֱ�ӷ���
    for (i=head[x];i>0;i=edge[i].next) 
    {
        if (edge[i].cap>0 && dis[edge[i].trg]==dis[x]+1 && (newcap=Find(edge[i].trg,min(low,edge[i].cap))))
        //   ��ͨ        ��         �Ƿֲ�ͼ����һ��    ��    �ܵ����(��������newcap<>0)    
        {
            edge[i].cap-=newcap;
            edge[edge[i].pair].cap+=newcap;
            return newcap;
        }
    }
    return 0;
}

int Dinic()
{
    int ret,newcap;
    ret=0;
    while(BFS())//Ҫ��ͣ�ؽ����ֲ�ͼ,���BFS�������Ž���
    {
        //һ��BFSҪ��ͣ��������·,ֱ���Ҳ���Ϊֹ
        while(newcap=Find(source,INF)) ret+=newcap;
    }
	return(ret); 	
} 

void ReadData()
{
    int i,j;
    char s[255],len=1,c;
    scanf("%c",&c);
    n=0; 
    while (c!='\n')
    {
        s[len++]=c;
        scanf("%c",&c);
    }
    //��ʤ���������α��浽a[] 
    for (i=1;i<=len;i++)
        if (s[i]>=48 && s[i]<=57) a[++n]=s[i]-48;
    gamenum=0;
    //id[i][j]��ʾi��j��ı����ĳ��α�� 
    for (i=1;i<=n;i++)
      for (j=i+1;j<=n;j++)
        id[i][j]=++gamenum;
    source=1+gamenum+n;
    target=source+1;
}

void BuildMap(int num)
{
    int i,j,flag[MaxPoint];
    memset(head,-1,sizeof(head));
    memset(flag,0,sizeof(flag));
    ne=1;
    //Դ�������е�ѡ����һ���ߣ�����Ϊ���ʤ���� 
    for (i=1;i<=n;i++) AddEdge(source,i,a[i]);
    //���еı���������һ���ߣ�����Ϊ1 
    for (i=n+1;i<=n+gamenum;i++) AddEdge(i,target,1);
    //���i,jͬΪ��ǿʤ�ߣ���i��ʤ��������j����i����Ӯj 
	//����i��id[i][j]��������һ������Ϊ1�ı� 
	for (i=n-num+1;i<=n;i++)
        for (j=i+1;j<=n;j++)
            if (a[j]>a[i])
            {
                flag[id[i][j]]=1;
            	AddEdge(i,id[i][j]+n,1);
            }
    //���������£���ȷ��һ����˭Ӯ�ģ���i��j������һ��������һ������Ϊ1�ı� 
    for (i=1;i<=n;i++)
        for (j=i+1;j<=n;j++)
            if (!flag[id[i][j]])
            {
                AddEdge(i,id[i][j]+n,1);
                AddEdge(j,id[i][j]+n,1);
            }
}

void Solve()
{
    int i,flow;
    for (i=n;i>1;i--)
    {
        BuildMap(i);
        flow=Dinic();
        if (flow==gamenum) break;
    }
    printf("%d\n",i);
}

int main()
{
    scanf("%d\n",&m);
    while (m--)
    {
    	ReadData();
        Solve();
    }     
}
