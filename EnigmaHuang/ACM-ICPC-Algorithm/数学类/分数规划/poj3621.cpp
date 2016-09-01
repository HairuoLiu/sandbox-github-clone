#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>

using namespace std;

#define MaxN 1005
#define MaxE 5050
#define INF  99999999.0 
#define eps  0.0001

struct TEdge
{
    int u,v,w,next;
}edge[MaxE];

int index,nodenum,source,head[MaxN];
int vis[MaxN],cnt[MaxN],happy[MaxN];
double dis[MaxN];

void AddEdge(int src,int trg,int weight)
{
    edge[index].u=src;
    edge[index].v=trg;
    edge[index].w=weight;
    edge[index].next=head[src];
    head[src]=index++;
}

void InitMap(int n,int src)
{
    index=0;
    memset(head,-1,sizeof(head));
    nodenum=n;
    source=src;
}

int SPFA(double mid)
{
    int i,u,v,w;
    double tmp;
    queue<int> q;
    
    for (i=1;i<=MaxN;i++) dis[i]=INF;
    memset(vis,0,sizeof(vis));
    memset(cnt,0,sizeof(cnt));
    
    dis[source]=0.0;
    vis[source]=1;
    q.push(source);
    
    while (!q.empty())
    {
        u=q.front();
        q.pop();
        vis[u]=0;
        for (i=head[u];i!=-1;i=edge[i].next)
        {
            v=edge[i].v;
            w=edge[i].w;
            tmp=mid*w-happy[v];   //������µ�Ȩֵ�����ݶ��ֲ����ó��� 
            if (dis[v]>dis[u]+tmp)
            {
                dis[v]=dis[u]+tmp;
                if (!vis[v])
                {
                    vis[v]=1;
                    q.push(v);
                    cnt[v]++; 
                    if (cnt[v]>nodenum) return 0; //��һ������ӳ���������˵���и���
                }
            }
        }
    }
    return 1;
}

void Solve()
{
    double l,r,mid;
    l=0;r=10000; //10000��Ϊ�Ͻ�Ӧ�ù����ˣ���û����ϸ����
    while (r-l>eps)
    {
        mid=(l+r)/2;
        /*û�и����Ļ�����ǰ�²�ֵ���ڴ𰸣���������
          �෴����ǰ�²�ֵС�ڴ𰸣��������*/
        if (SPFA(mid)) r=mid; else l=mid;
    }
    printf("%.2f\n",mid);
} 

int main()
{
    int n,m,i,u,v,w;
    freopen("poj3621.txt","r",stdin);
    freopen("poj3621ans.txt","w",stdout);
    while (scanf("%d%d",&n,&m)!=EOF)
    {
        for (i=1;i<=n;i++) scanf("%d",&happy[i]);
        InitMap(n,1);
        for (i=1;i<=m;i++) 
        {
       	    scanf("%d%d%d",&u,&v,&w);
       	    AddEdge(u,v,w);
        }
        Solve();
    }
    return 0;
}
