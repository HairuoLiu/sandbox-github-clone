#include <stdio.h>
#include <string.h>
#define MaxN 2005 
#define MaxE 4*1005*505 

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

struct TWedding
{
    int start,end,len;
}wed[MaxN];

int TimeStrToInt(char str[])
{
    int res=0;
    res=(str[0]-'0')*10+str[1]-'0';
    res*=60;
    res+=((str[3]-'0')*10+str[4]-'0');
    return res;
}

int Conflict(int s1,int l1,int s2,int l2)
{
    if (s1+l1>s2 && s1<s2+l2) return 1; else return 0;
}

void PrintTime(int t)
{
    printf("%02d:%02d",t/60,t%60);
}

int main()
{
    int i,n,len,j;
    char s1[9],s2[9];
    freopen("poj3683.txt","r",stdin);
    freopen("poj3683ans.txt","w",stdout);
    while (scanf("%d",&n)!=EOF)
    {
        InitEdge();
        for (i=1;i<=n;i++)
        {
            scanf("%s%s%d",s1,s2,&len);
            wed[i].start=TimeStrToInt(s1);
            wed[i].end=TimeStrToInt(s2);
            wed[i].len=len;
        }
        for (i=1;i<=n;i++)
            for (j=1;j<=n;j++)
            {
                if (i==j) continue;
                if (Conflict(wed[i].start,wed[i].len,wed[j].start,wed[j].len)) AddEdge(i,j+n);
                if (Conflict(wed[i].start,wed[i].len,wed[j].end-wed[j].len,wed[j].len)) AddEdge(i,j);
                if (Conflict(wed[i].end-wed[i].len,wed[i].len,wed[j].start,wed[j].len)) AddEdge(i+n,j+n);
                if (Conflict(wed[i].end-wed[i].len,wed[i].len,wed[j].end-wed[j].len,wed[j].len)) AddEdge(i+n,j);
            }
        if (TwoSAT(n))
        {
            printf("YES\n");
            for (i=1;i<=n;i++) if (ans[i])
            {
                PrintTime(wed[i].start);
                printf(" ");
                PrintTime(wed[i].start+wed[i].len);
                printf("\n");
            }
            else
            {
                PrintTime(wed[i].end-wed[i].len);
                printf(" ");
                PrintTime(wed[i].end);
                printf("\n");
            }
        }
        else printf("NO\n");
    }
    return 0;
}
