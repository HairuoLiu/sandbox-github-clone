#include<string.h>
#include<stdio.h>
#define min(a,b) (a<b)?a:b;
#define INF 0x3f3f3f3f
#define MaxN 5005
#define MaxE 13005

/*----------2SAT Judge Template Start----------*/
/*------���0��ʼ��ţ�һ���������Ÿ�1-------*/

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

int TwoSAT(int n)
{
    int i;
    memset(dfn,0,sizeof(dfn));
    memset(vis,0,sizeof(vis));
    scc=top=cnt=0;
    for(i=0;i<2*n;i++) if(!dfn[i]) Tarjan(i);
    for(i=0;i<n;i++) if(grp[i*2]==grp[i*2+1]) return 0;
    return 1;
}

/*----------2SAT Judge Template Over----------*/

int n,m;

struct TConflict
{
    int x,y;
}a[MaxN],b[MaxN];

int main()
{
    int i,ans,low,high,mid;
    freopen("poj2723.txt","r",stdin);
    freopen("poj2723ans.txt","w",stdout);
    while(scanf("%d%d",&n,&m),n||m)
    {
        for(i=1;i<=n;i++) scanf("%d%d",&a[i].x,&a[i].y);
        for(i=1;i<=m;i++) scanf("%d%d",&b[i].x,&b[i].y);
        low=0;high=m;
        while(low<=high)
        {
            mid=(low+high)/2;
            InitEdge();
            for(i=1;i<=n;i++) 
            {
                AddEdge(2*a[i].x,2*a[i].y+1);
                AddEdge(2*a[i].y,2*a[i].x+1);
            }
            for(i=1;i<=mid;i++)
            {
                AddEdge(2*b[i].x+1,2*b[i].y);
                AddEdge(2*b[i].y+1,2*b[i].x);
            }
            if(mid==0 || TwoSAT(n)) 
            {
                ans=mid;
                low=mid+1;
            }
            else high=mid-1;
        }
        printf("%d\n",ans);
    }
    return 0;
}
