#include<string.h>
#include<stdio.h>
#include<math.h>

#define min(a,b) (a<b)?a:b;
#define INF 0x3f3f3f3f
#define MaxN 1005 
#define MaxE 2*1005*505

/*----------2SAT Judge Template Start----------*/

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
    scc=top=cnt=0;
    memset(dfn,0,sizeof(dfn));
    memset(vis,0,sizeof(vis));
    memset(grp,-1,sizeof(grp));
    for (i=1;i<=2*n;i++) if (dfn[i]==0) Tarjan(i);
    for (i=1;i<=n;i++) if (grp[i]==grp[i+n]) return 0;
    return 1;
}

/*----------2SAT Judge Template Over----------*/

struct TData
{
    int x,y;
}s[MaxN],sa[MaxN],sb[MaxN],s1,s2;

int d[MaxN],D,n,a,b;

void RebuildEdge(int mid)
{
    int i,j;
    InitEdge();
    for (i=1;i<=a;i++)
    {
        AddEdge(sa[i].x,sa[i].y+n);
        AddEdge(sa[i].y+n,sa[i].x);
        AddEdge(sa[i].y,sa[i].x+n);
        AddEdge(sa[i].x+n,sa[i].y);
    }
    for (i=1;i<=b;i++)
    {
        AddEdge(sb[i].x,sb[i].y);
        AddEdge(sb[i].y,sb[i].x);
        AddEdge(sb[i].x+n,sb[i].y+n);
        AddEdge(sb[i].y+n,sb[i].x+n);
    }
    for (i=1;i<=n;i++)
        for (j=i+1;j<=n;j++)
        {
            if (d[i]+d[j]>mid)
            {
                AddEdge(i,j+n);
                AddEdge(j,i+n);
            }
            if (d[i+n]+d[j+n]>mid)
            {
                AddEdge(i+n,j);
                AddEdge(j+n,i);
            }
            if (d[i]+d[j+n]+D>mid)
            {
                AddEdge(i,j);
                AddEdge(j+n,i+n);
            }
            if (d[i+n]+d[j]+D>mid)
            {
                AddEdge(i+n,j+n);
                AddEdge(j,i);
            }
        }
}

int main()
{
    int i,l,r,mid,ans;
    freopen("poj2749.txt","r",stdin);
    freopen("poj2749ans.txt","w",stdout);
    while (scanf("%d%d%d",&n,&a,&b)!=EOF)
    {
        scanf("%d%d%d%d",&s1.x,&s1.y,&s2.x,&s2.y);
        D=abs(s1.x-s2.x)+abs(s1.y-s2.y);
        for (i=1;i<=n;i++) 
        {
            scanf("%d%d",&s[i].x,&s[i].y);
            d[i]=abs(s[i].x-s1.x)+abs(s[i].y-s1.y);
            d[i+n]=abs(s[i].x-s2.x)+abs(s[i].y-s2.y);
        }
        for (i=1;i<=a;i++) scanf("%d%d",&sa[i].x,&sa[i].y);
        for (i=1;i<=b;i++) scanf("%d%d",&sb[i].x,&sb[i].y);
        ans=-1;
        l=1;r=4000000;
        while (l<=r)
        {
            mid=(l+r)/2;
            RebuildEdge(mid);
            if (TwoSAT(n))
            {
                ans=mid;
                r=mid-1;
            }
            else l=mid+1;
        }
        printf("%d\n",ans);
    }
    return 0;
}
