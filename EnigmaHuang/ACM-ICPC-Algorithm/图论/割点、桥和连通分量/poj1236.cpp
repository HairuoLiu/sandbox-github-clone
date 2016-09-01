#include <cstring>
#include <cstdio>

#define min(a,b) (a<b)?a:b;

const int MaxN = 105;
const int MaxE = MaxN*MaxN;

/*----------Tarjan Template Start----------*/

struct TEdge
{
    int u,v,next;
}Edge[MaxE];
int head[MaxN],index;

int dfn[MaxN];  //dfn[u]:������u���ʱ��; 
int low[MaxN];  //low[u]:u��u�������ܹ�׷�ݵ��������ջ�нڵ�Ĵ����
int grp[MaxN];  //grp[u]:u���ڵ���ͨ�����ı��
int vis[MaxN];  //v�Ƿ���ջ��

int stack[MaxN],top,scc,cnt;

void AddEdge(int u, int v)
{
    index++;
    Edge[index].u=u;
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
    for (u=1;u<=NodeNum;u++) if (dfn[u]==0) Tarjan(u);
}

/*----------Tarjan Template Over----------*/

int ind[MaxN],oud[MaxN]; //�����Ⱥͳ�����
int n; 

void CountDeg()
{
    int i,u,v;
    memset(ind,0,sizeof(ind));
    memset(oud,0,sizeof(oud)); 
    for (u=1;u<=n;u++)
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
}

int main()
{
    freopen("poj1236.txt","r",stdin);
    freopen("poj1236ans.txt","w",stdout);
    int u,v,i,inc,ouc;
    while (scanf("%d",&n)!=EOF)
    {
        InitEdge();
        for (u=1;u<=n;u++)
        {
            while (scanf("%d",&v) && v) 
            {
                AddEdge(u,v);
            } 
        }
        Solve(n);
        if (scc==1) printf("1\n0\n");
        else
        {
            CountDeg();
            inc=ouc=0;
            for (i=1;i<=scc;i++)
            {
                if (ind[i]==0) inc++;
                if (oud[i]==0) ouc++;
            }
            printf("%d\n%d\n",inc,(inc>ouc?inc:ouc)); 
        }
    }
} 
