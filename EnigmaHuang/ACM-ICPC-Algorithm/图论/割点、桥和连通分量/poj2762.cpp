#include <cstring>
#include <cstdio>

#define min(a,b) (a<b)?a:b;

using namespace std;

const int MaxN = 1005;
const int MaxE = 6005;

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
int ind[MaxN],oud[MaxN],inc,ouc; //�����Ⱥͳ�����

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

int n,m,src,linklen; 

void DFS(int u)
{
    int i;
    linklen++;
    vis[u]=1;
    for (i=1;i<=m;i++)  //����û�п����Һ����ܱ��������ö��ν�ͼ�� 
    {
        if (grp[Edge[i].u]==u && vis[grp[Edge[i].v]]==0)
        { 
            DFS(grp[Edge[i].v]);
            break;
	}
    }
}

int main()
{
    freopen("poj2762.txt","r",stdin);
    freopen("poj2762ans.txt","w",stdout);
    int t,i,u,v;
    scanf("%d",&t); 
    while (t--)
    {
        scanf("%d%d",&n,&m);
        InitEdge();
        for (i=1;i<=m;i++)
        {
            scanf("%d%d",&u,&v);
            AddEdge(u,v);
        }
        Solve(n);
        if (scc==1) printf("Yes\n");    //��ͼ��ֻ��һ���㣬���� 
        else if (inc>1) printf("No\n"); //���Ϊ0�ĵ�������1������һ����㣬���� 
        else
        {
            for (i=1;i<=scc;i++) if (ind[i]==0) src=i;
            linklen=0;
            memset(vis,0,sizeof(vis));
            DFS(src);  //�����������䳤��=��ͼ����������� 
            if (linklen==scc) printf("Yes\n");
            else printf("No\n");
        }
    }
} 
