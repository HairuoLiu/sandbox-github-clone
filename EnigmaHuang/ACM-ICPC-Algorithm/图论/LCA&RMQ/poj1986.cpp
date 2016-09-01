#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<queue>

using namespace std;

#define MaxN 50005
#define MaxE 100005

int dis[MaxN];  //dis[u]=u�����ڵ�ľ��� 

/*----------LCA Tarjan Template Start----------*/

struct TEdge
{
    int u,v,w,next;
}edge[MaxE];
int head[MaxN],index;

int father[MaxN],vis[MaxN]; //����ĸ��ڵ㣬���ʱ��
int root,n;                 //���ڵ㣬����

struct TQuery
{
    int v,index;            //��ѯ����һ�㣬��ѯ����� 
};
vector<TQuery> q[MaxN];     //q[x]��ʾ��ѯ����x������в�ѯ 
int ans[MaxN];              //��ѯ�Ĵ� 

void InitEdge()
{
    index=0;
    memset(head,-1,sizeof(head));
}

void AddEdge(int u,int v,int w)
{
    edge[index].u=u;
    edge[index].v=v;
    edge[index].w=w;
    edge[index].next=head[u];
    head[u]=index++;
}

int GetFather(int x)
{
    if (father[x]==x) return x;
    father[x]=GetFather(father[x]);
    return father[x];
}

void Union(int x,int y)
{
    int fx,fy;
    fx=GetFather(x);
    fy=GetFather(y);
    if (fx==fy) return; else father[y]=fx;
}

void DFS(int u,int depth)
{
    int i,fa,v,index;
    dis[u]=depth;
    vis[u]=1;
    father[u]=u;
    for (i=head[u];i!=-1;i=edge[i].next) if (!vis[edge[i].v]) 
    {
        DFS(edge[i].v,depth+edge[i].w);
        Union(u,edge[i].v);
    }
    for (i=0;i<q[u].size();i++) //���ڰ�����ǰ������в�ѯ 
    {
        v=q[u][i].v;
        index=q[u][i].index;
        if (vis[v])             //�������һ����Ҳ���������ˣ��õ���� 
        {
            fa=GetFather(v);
            ans[index]=dis[u]+dis[v]-2*dis[GetFather(v)];
        }
    }
}

void LCATarjan(int n)
{
    memset(vis,0,sizeof(vis));
    DFS(1,0);
}

/*----------LCA Tarjan Template Over----------*/

int main()
{
    int u,v,w,k,i,j,t,m;
    char c;
    TQuery que;
    freopen("poj1986.txt","r",stdin);
    freopen("poj1986ans.txt","w",stdout);
    while (scanf("%d%d",&n,&m)!=EOF)
    {
        InitEdge();
        for (i=1;i<=m;i++)
        {
            scanf("%d %d %d %c\n",&u,&v,&w,&c);
            AddEdge(u,v,w);  //������������ͼ 
            AddEdge(v,u,w);  //����Ҫ��˫��� 
        }
        scanf("%d",&t);
        for (i=1;i<=t;i++)
        {
            scanf("%d%d",&u,&v);
            que.index=i;
            que.v=v;
            q[u].push_back(que);  //�����ѯ 
            que.v=u;
            q[v].push_back(que);  //ͬ��ҲҪ��˫��
        }
        LCATarjan(n);
        for (i=1;i<=t;i++) printf("%d\n",ans[i]);
    }
    return 0;
}
