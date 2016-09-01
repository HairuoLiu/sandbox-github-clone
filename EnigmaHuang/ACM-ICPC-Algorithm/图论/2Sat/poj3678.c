#include<string.h>
#include<stdio.h>

#define min(a,b) (a<b)?a:b;
#define INF 0x3f3f3f3f
#define MaxN 1005
#define MaxE 4000005

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
    int n,m,a,b,c,i,flag;
    char opt[8];
    freopen("poj3678.txt","r",stdin);
    freopen("poj3678ans.txt","w",stdout);
    while (scanf("%d %d",&n,&m)!=EOF)
    {
        InitEdge();
        for (i=1;i<=m;i++)
        {
       	    scanf("%d %d %d %s",&a,&b,&c,opt);
       	    a++;b++;
	    if (opt[0]=='A')
       	    {
                if (c==1)
                {
               	    AddEdge(a,a+n);
               	    AddEdge(b,b+n);
               	    AddEdge(a+n,b+n);
               	    AddEdge(b+n,a+n);
                }
                else
                {
               	    AddEdge(a+n,b);
               	    AddEdge(b+n,a);
                }
       	    }
       	    if (opt[0]=='O')
       	    {
                if (c==1)
                {
               	    AddEdge(a,b+n);
               	    AddEdge(b,a+n);
                }
                else
                {
               	    AddEdge(a+n,a);
               	    AddEdge(b+n,b);
               	    AddEdge(a,b);
               	    AddEdge(b,a);
                }
       	    }
       	    if (opt[0]=='X')
       	    {
                if (c==1)
                {
               	    AddEdge(a,b+n);
               	    AddEdge(b,a+n);
               	    AddEdge(a+n,b);
               	    AddEdge(b+n,a);
                }
                else 
                {
               	    AddEdge(a,b);
               	    AddEdge(b,a);
               	    AddEdge(a+n,b+n);
               	    AddEdge(b+n,a+n);
                }
       	    }
        }
        Solve(2*n);
        flag=1;
        for (i=1;i<=n;i++) if (grp[i]==grp[i+n])
        {
       	    flag=0;
       	    break;
        }
        if (flag) printf("YES\n"); else printf("NO\n");
    }
    return 0;
}
