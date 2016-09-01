#include <stdio.h>
#include <string.h>
#define MaxN 205 
#define MaxE 1005 

/*----------2SAT Template Start----------*/ 
/*----���1��ʼ��ţ�һ���������Ÿ�n---*/

struct Edge
{
    int u,v,next;
}e[MaxE],e2[MaxE];
int index,index2,head[MaxN],head2[MaxN];
int n,m;

void AddEdge(int u,int v)
{
    e[index].u=u;
    e[index].v=v;
    e[index].next=head[u];
    head[u]=index++;
}

void InitEdge()
{
    index=0;
    memset(head,-1,sizeof(head));
}

void AddEdge2(int u,int v)
{
    e2[index2].u=u;
    e2[index2].v=v;
    e2[index2].next=head2[u];
    head2[u]=index2++;
}

void InitEdge2()
{
    index2=0;
    memset(head2,-1,sizeof(head2));
}

int dfn[MaxN];   //dfn[u]:������u���ʱ��
int low[MaxN];   //low[u]:u��u�������ܹ�׷�ݵ��������ջ�нڵ�Ĵ����
int id[MaxN];    //id[u]:u���ڵ���ͨ�����ı��
int vis[MaxN];   //v�Ƿ���ջ��
int stack[MaxN]; //ջ
int top,scc,cnt; //cnt���ڱ���ʱ������scc��Ϊ�����ĵ���

void Tarjan(int u)
{
    int i,v;
    dfn[u]=low[u]=++cnt;
    stack[++top]=u;
    vis[u]=1;
    for (i=head[u];i!=-1;i=e[i].next)
    {
        v=e[i].v;
        if (!dfn[v])
        {
            Tarjan(v);
            if (low[v]<low[u]) low[u]=low[v];
        }
        else if (vis[v] && dfn[v]<low[u]) low[u]=dfn[v];
    }
    if (dfn[u]==low[u])
    {
        scc++;
        do
        {
            v=stack[top--];
            vis[v]=0;
            id[v]=scc;
        } while(v!=u);
    }
}

int cf[MaxN];    //������
int indeg[MaxN]; //���
int que[MaxN];   //����
int col[MaxN];   //Ⱦɫ��־
int ans[MaxN];   //ԭͼ��ѡȡ�ĵ� 

int TwoSAT(int n)
{
    int i,head,tail,u,v;
    cnt=scc=top=0;
    memset(dfn,0,sizeof(dfn));
    for (i=1;i<=2*n;i++) if (!dfn[i]) Tarjan(i);
    
    for (i=1;i<=n;i++)
    {
        if (id[i]==id[i+n]) return 0; //һ����������ͬһ��ͨ�����У��޽� 
        cf[id[i]]=id[i+n]; 
        cf[id[i+n]]=id[i]; //�������ͼ�б�ǻ��������
    }
    
    memset(indeg,0,sizeof(indeg));
    memset(col,0,sizeof(col));
    InitEdge2();
    for (i=0;i<index;i++) //��������°�ԭ���ı�����ͼ 
    {
        u=e[i].u;
        v=e[i].v;
        if (id[u]!=id[v])
        {
            AddEdge2(id[v],id[u]); //����,����Ϊu->v�����ѡ����u����ѡ��v����Ӧ����
            indeg[id[u]]++; //ͳ�����
        }
    }

    head=1,tail=1;
    for (i=1;i<=scc;i++) if (indeg[i]==0) que[tail++]=i; //���Ϊ0�����
    while (head<tail)
    {
        u=que[head];
        head++;
        if (col[u]==0) //δ��ɫ�ĵ�xȾ��1��ͬʱ����xì�ܵĵ�cf[x]Ⱦ��2
        {
            col[u]=1;
            col[cf[u]]=2;
        }
        for (i=head2[u];i!=-1;i=e2[i].next)
        {
            v=e2[i].v;
            if (--indeg[v]==0) que[tail++]=v; //���Ϊ0�����
        }
    }
    
    memset(ans,0,sizeof(ans));
    for (i=1;i<=n;i++) if (col[id[i]]==1) ans[i]=1;
    return 1;
}

/*----------2SAT Template Start----------*/ 

int main()
{
    int i,r,l;
    char c1,c2;
    freopen("poj3648.txt","r",stdin);
    freopen("poj3648ans.txt","w",stdout);
    while(scanf("%d%d\n",&n,&m) && ( n || m ))
    {
        InitEdge();
        while (m--)
        {
            scanf("%d%c %d%c",&l,&c1,&r,&c2);
            l++;r++; //��Ŀ��0��ʼ��ţ�����Ҫע�� 
            if (c1=='h' && c2=='h')
            {
                AddEdge(r+n,l);
                AddEdge(l+n,r);
            }
            else if (c1=='h' && c2=='w')
            {
                AddEdge(l+n,r+n);
                AddEdge(r,l);
            }
            else if (c1=='w' && c2=='h')
            {
                AddEdge(l,r);
                AddEdge(r+n,l+n);
            }
            else if (c1=='w' && c2=='w')
            {
                AddEdge(l,r+n);
                AddEdge(r,l+n);
            }
        }
        AddEdge(1,1+n); //�������ﵽ���ɵı�
        if (TwoSAT(n))
        {
            //��Ŀ��0��ʼ��ţ�����Ҫע����-1 
            for (i=2;i<=n;i++) if (ans[i]) printf("%dh ",i-1);else printf("%dw ",i-1); 
            printf("\n");
        }
        else printf("bad luck\n");
    }
    return 0;
}
