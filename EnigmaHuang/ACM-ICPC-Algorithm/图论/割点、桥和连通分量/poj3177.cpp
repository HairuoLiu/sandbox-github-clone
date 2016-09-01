#include <cstring>
#include <cstdio>

#define min(a,b) (a<b)?a:b;

using namespace std;

const int MaxN = 5001;
const int MaxE = 20005;

int EdgeVis[MaxE];
/*----------Tarjan Template Start----------*/

struct TEdge
{
    int u,v,next,pair;
}Edge[MaxE];
int head[MaxN],index;

int dfn[MaxN];  //dfn[u]:������u���ʱ��; 
int low[MaxN];  //low[u]:u��u�������ܹ�׷�ݵ��������ջ�нڵ�Ĵ����
int grp[MaxN];  //grp[u]:u���ڵ���ͨ�����ı��
int vis[MaxN];  //v�Ƿ���ջ��
int ind[MaxN],oud[MaxN],inc,ouc; //�����Ⱥͳ�����

int stack[MaxN],top,scc,cnt;

void AddEdge(int u, int v)
{
    index++;
    Edge[index].u=u;
    Edge[index].v=v;
    Edge[index].pair=index+1;
    Edge[index].next=head[u];
    head[u]=index;
    index++;
    Edge[index].v=u;
    Edge[index].u=v;
    Edge[index].pair=index-1;
    Edge[index].next=head[v];
    head[v]=index;
}

void Tarjan(int u)
{
    int v,i;
    dfn[u]=low[u]=++cnt;//��ʼʱdfn[u]==low[u]
    stack[top++]=u;     //��ǰ���ջ
    vis[u]=1;
    for (i=head[u];i!=-1;i=Edge[i].next)
    {
        v=Edge[i].v;
        if (EdgeVis[i]) continue;
        EdgeVis[i]=EdgeVis[Edge[i].pair]=1;
        if (dfn[v]==0) //���v�㻹δ����
        {
            Tarjan(v); //���±���
            low[u]=min(low[u],low[v]) //ȷ��low[u]��С
        }
        else if (vis[v] && low[u]>dfn[v]) low[u] = dfn[v];
        //v��ջ�У��޸�low[u]          
    }
    if (dfn[u]==low[u])     //uΪ��ǿ��ͨ�����б����������ĸ�
    {
        scc++;
        do
        {
            v=stack[--top]; //ջ�����е�u�ĵ㶼���ڸ�ǿ��ͨ��������ջ
            vis[v]=0;
            grp[v]=scc;
        } while (u!=v);
    }
}

void InitEdge()
{
    index=0;
    memset(head,-1,sizeof(head));
    memset(EdgeVis,0,sizeof(EdgeVis));
}

void CountDeg(int NodeNum)
{
    int i,u,v;
    memset(ind,0,sizeof(ind));
    memset(oud,0,sizeof(oud)); 
    for (u=1;u<=NodeNum;u++)
    {
    	for (i=head[u];i!=-1;i=Edge[i].next)
    	{
            v=Edge[i].v;
            if (grp[u]!=grp[v])
            {
                ind[grp[v]]++;
                oud[grp[u]]++;
            } 
    	}
    }
    inc=ouc=0;
    for (i=1;i<=scc;i++)
    {
        if (ind[i]==0) inc++;
        if (oud[i]==0) ouc++;
    }
}

void Solve(int NodeNum)
{
    int u;
    scc=top=cnt=0;
    memset(dfn,0,sizeof(dfn));
    memset(vis,0,sizeof(vis));
    for (u=1;u<=NodeNum;u++) if (dfn[u]==0) Tarjan(u);
    CountDeg(NodeNum);
}

/*----------Tarjan Template Over----------*/

int n,m; 
bool map[MaxN][MaxN];

int main()
{
    freopen("poj3177.txt","r",stdin);
    freopen("poj3177ans.txt","w",stdout);
    int t,i,j,u,v;
    while (scanf("%d%d",&n,&m)!=EOF)
    {
        InitEdge();
        memset(map,false,sizeof(map));
        for (i=1;i<=m;i++)
        {
            scanf("%d%d",&u,&v);
            if (map[u][v] || map[v][u]) continue;
            map[u][v]=map[v][u]=true;
            AddEdge(u,v); 
        }
        Solve(n);
        t=0;
        for (i=0;i<=n;i++) if (ind[i]==1) t++;
        printf("%d\n",(t+1)/2); 
    }
} 
