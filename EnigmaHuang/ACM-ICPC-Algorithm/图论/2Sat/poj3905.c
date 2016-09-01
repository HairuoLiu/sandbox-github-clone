#include<string.h>
#include<stdio.h>
#define min(a,b) (a<b)?a:b;
#define INF 0x3f3f3f3f
#define MaxN 2005
#define MaxE 2000050

/*----------Tarjan Template Start----------*/

struct TEdge
{
    int v,next;
}Edge[MaxE];
int head[MaxN],index;

int dfn[MaxN];  //dfn[u]:������u���ʱ��; 
int low[MaxN];  //low[u]:u��u�������ܹ�׷�ݵ��������ջ�нڵ�Ĵ����
int grp[MaxN];  //grp[u]:u���ڵ���ͨ�����ı��
int vis[MaxN];  //v�Ƿ���ջ��
int stack[MaxN],top,scc,cnt;

void AddEdge(int u,int v)
{
    index++;
    Edge[index].v=v;
    Edge[index].next=head[u];
    head[u]=index;
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
}

void Solve(int NodeNum)
{
    int u;
    scc=top=cnt=0;
    memset(dfn,0,sizeof(dfn));
    memset(vis,0,sizeof(vis));
    memset(grp,-1,sizeof(grp));
    for (u=1;u<=NodeNum;u++) if (dfn[u]==0) Tarjan(u);
}

/*----------Tarjan Template Over----------*/

int main()
{
    int n,m,i,a,b,flag;
    freopen("poj3905.txt","r",stdin);
    freopen("poj3905ans.txt","w",stdout);
    while (scanf("%d%d",&n,&m)!=EOF)
    {
        InitEdge();
        for (i=1;i<=m;i++)
        {
            scanf("%d%d",&a,&b);
	    if (a>0 && b>0)
	    {
                AddEdge(2*a+1,2*b);
                AddEdge(2*b+1,2*a);
            }
            if (a>0 && b<0)
            {
                b=-b;
                AddEdge(2*a+1,2*b+1);
                AddEdge(2*b,2*a);
            }
            if (a<0 && b>0)
            {
                a=-a;
                AddEdge(2*b+1,2*a+1);
                AddEdge(2*a,2*b);
            }
            if (a<0 && b<0)
            {
                a=-a;
                b=-b;
                AddEdge(2*a,2*b+1);
                AddEdge(2*b,2*a+1);
            }
        } 
        Solve(2*n+1);
        flag=1;
        for (i=1;i<=n;i++) if (grp[2*i]==grp[2*i+1])
        {
       	    flag=0;
       	    break;
        }
        printf("%d\n",flag);
    }
    return 0;
}

