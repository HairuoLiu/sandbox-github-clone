#include<string.h>
#include<stdio.h>
#define min(a,b) (a<b)?a:b;
#define INF 0x3f3f3f3f
#define MaxN 5005
#define MaxE 50005

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

struct TLine
{
    int s,e;
}line[MaxN];

int JudgeLine(int l1,int l2)
{
    int a,b,c,d;
    a=line[l1].s;
    b=line[l1].e;
    c=line[l2].s;
    d=line[l2].e;
    if (c<a && a<d && d<b) return 1;
    if (a<c && c<b && b<d) return 1;
    return 0;
}

int main()
{
    int n,m,i,j,flag;
    freopen("poj3207.txt","r",stdin);
    freopen("poj3207ans.txt","w",stdout);
    while (scanf("%d%d",&n,&m)!=EOF)
    {
        for (i=1;i<=m;i++) scanf("%d%d",&line[i].s,&line[i].e);
        InitEdge();
        for (i=1;i<m;i++)
            for (j=i+1;j<=m;j++) if (JudgeLine(i,j))
            {
                AddEdge(2*i+1,2*j);
                AddEdge(2*j+1,2*i);
                AddEdge(2*i,2*j+1);
                AddEdge(2*j,2*i+1);
            }
        Solve(2*m);
        flag=1;
        for (i=1;i<=m;i++) if (grp[i*2]==grp[i*2+1])
        {
       	    flag=0;
       	    break;
        }
        if (flag) printf("panda is telling the truth...\n");
        else printf("the evil panda is lying again\n");
    }
    return 0;
}
