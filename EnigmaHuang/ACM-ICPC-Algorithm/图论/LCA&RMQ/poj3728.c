#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define Max(a,b) ((a)>(b)?(a):(b))  
#define Min(a,b) ((a)<(b)?(a):(b))  

#define MaxN 50005
#define MaxE 200005

int w[MaxN],ans[MaxN];   //��Ȩ���� 
int min[MaxN],max[MaxN]; //�Ӹ�����ǰ�����С�۸�����۸� 
int up[MaxN],down[MaxN]; //�ӵ�ǰ�㵽���ʹӸ�����ǰ���������� 

struct TEdge
{
    int u,v,next,id;
}edge[MaxE];

//ԭͼ��ͷ��treehead������ѯ��ͷ(queryhead) 
int thead[MaxN],qhead[MaxN],head[MaxN],index;

int father[MaxN],vis[MaxN]; //����ĸ��ڵ㣬���ʱ��

void InitEdge()
{
    index=0;
    memset(head,-1,sizeof(head));
    memset(thead,-1,sizeof(thead));
    memset(qhead,-1,sizeof(qhead));
}

void AddTEdge(int u,int v)  //��ԭͼ�� 
{
    edge[index].v=v;
    edge[index].next=thead[u];
    thead[u]=index++;
}

void AddQEdge(int u,int v,int id) //�Ӳ�ѯ�� 
{
    edge[index].v=v;
    edge[index].u=u;
    edge[index].id=id;
    edge[index].next=qhead[u];
    qhead[u]=index++;
}

void AddEdge(int u,int id)
{
    edge[index].id=id;
    edge[index].next=head[u];
    head[u]=index++;
}

int Max3(int a,int b,int c)
{
    return (Max(a,Max(b,c)));
}

int Update(int u)
{
    int fa; 
    if (father[u]==u) return u;
    //��һ����Ҫ������
    fa=father[u];  //����ԭ���ĸ��ڵ�
    father[u]=Update(father[u]);  //���º�ѹ��·�� 
    //DP��̬���� 
    up[u]   = Max3(up[u],up[fa],max[fa]-min[u]);
    down[u] = Max3(down[u],down[fa],max[u]-min[fa]);
    //ά��·���ϵ������Сֵ 
    max[u]  = Max(max[u],max[fa]);
    min[u]  = Min(min[u],min[fa]);
    return father[u];
}

void DFS(int u)
{
    int i,fa,src,v,tmp,id;
    father[u]=u;
    for (i=thead[u];i!=-1;i=edge[i].next)
    {
        v=edge[i].v;
        if (!vis[v])
        {
            DFS(v);
            father[v]=u;  //���鼯�ϲ� 
        } 
    }
    vis[u]=1;
    for (i=qhead[u];i!=-1;i=edge[i].next)
    {
        v=edge[i].v;
        if (vis[v])  //�ϲ�������������ڽӱ� 
        {
            fa=Update(v);
            AddEdge(fa,i);  //�����ߣ���¼����һ����ѯ�� 
        }
    }
    for (i=head[u];i!=-1;i=edge[i].next)
    {
        tmp=edge[i].id;
        id=edge[tmp].id;
        src=edge[tmp].u;
        v=edge[tmp].v;
        Update(src);
        if (id<0)  //��u,v������кϲ� 
        {
            tmp=src;
            src=v;
            v=tmp;
            id=-id;
        }
        ans[id]=Max3(up[src],down[v],max[v]-min[src]);
    }
}

int main()
{
    int n,i,u,v,m;
    freopen("poj3728.txt","r",stdin);
    freopen("poj3728ans.txt","w",stdout);
    while (scanf("%d",&n)!=EOF)
    {
        InitEdge();
        for (i=1;i<=n;i++)
        {
            scanf("%d",&w[i]);
            min[i]=max[i]=w[i];
        }
        for (i=1;i<n;i++)
        {
            scanf("%d%d",&u,&v);
            AddTEdge(u,v);
        }
        scanf("%d",&m);
        for (i=1;i<=m;i++)
        {
            scanf("%d%d",&u,&v);
            AddQEdge(u,v,i);
            AddQEdge(v,u,-i);  //�����ߵķ��� 
        }
        memset(vis,0,sizeof(vis));
        memset(up,0,sizeof(up));
        memset(down,0,sizeof(down));
        DFS(1);
        for (i=1;i<=m;i++) printf("%d\n",ans[i]);
    }
}
