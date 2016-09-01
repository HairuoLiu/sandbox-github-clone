#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define MaxN 100005
#define MaxE 400005

int degree[MaxN],ans;  //degree[x]��ʾx��x���ڵ������߱����ǵĴ����������� 

struct TEdge
{
    int v,next;
}edge[MaxE];
int thead[MaxN],qhead[MaxN],index;

int father[MaxN],vis[MaxN]; //����ĸ��ڵ㣬���ʱ��
int root,n,m;               //���ڵ㣬�������¼ӱ��� 

void InitEdge()
{
    index=0;
    memset(thead,-1,sizeof(thead));
    memset(qhead,-1,sizeof(qhead));
}

void AddTEdge(int u,int v)  //��ԭͼ�� 
{
    edge[index].v=v;
    edge[index].next=thead[u];
    thead[u]=index++;
}

void AddQEdge(int u,int v)  //�Ӳ�ѯ�� 
{
    edge[index].v=v;
    edge[index].next=qhead[u];
    qhead[u]=index++;
}

int GetFather(int x)
{
    if (father[x]==x) return x;
    father[x]=GetFather(father[x]);
    return father[x];
}

void Union(int x,int y)
{
    int fx,fy;
    fx=GetFather(x);
    fy=GetFather(y);
    if (fx==fy) return; else father[y]=fx;
}

void DFS(int u)
{
    int i,v;
    father[u]=u;  //��ĸ��ڵ��ʼ��Ϊ�Լ� 
    vis[u]=1;     //����ѷ��� 
    for (i=qhead[u];i!=-1;i=edge[i].next)
    {
        v=edge[i].v;
        if (vis[v]) degree[GetFather(v)]-=2;  //��ÿһ���¼ӱߣ���ѯ�ߣ�����LCA�Ķȼ�2 
    }
    for (i=thead[u];i!=-1;i=edge[i].next)
    {
        v=edge[i].v;
        if (!vis[v])
        {
            DFS(v);
            Union(u,v);
            degree[u]+=degree[v];      //���߱������ǵĴ���Ҫ�����ӱ߱������ǵĴ��� 
            if (degree[v]==1) ans++;   //ֻ��һ���¼ӱ��г̵�Ȧ���ǹ�һ�Σ���+1 
            if (degree[v]==0) ans+=m;  //û�б�Ȧ���ǣ����ţ���+m 
        }
    }
}

void get(int &a)  //����ң���ʡ����֮����ʱ�� 
{  
    char c;  
    while ((c=getchar())<'0'||c>'9');  
    for (a=0;c>='0'&&c<='9';c=getchar()) a=a*10+c-'0';  
}  

int main()
{
    int i,u,v;
    freopen("poj3417.txt","r",stdin);
    freopen("poj3417ans.txt","w",stdout);
    while (scanf("%d%d",&n,&m)!=EOF)
    {
        InitEdge();
        memset(degree,0,sizeof(degree));
        memset(vis,0,sizeof(vis));
        for (i=1;i<n;i++)
        {
            //scanf("%d%d",&u,&v);
            get(u);
            get(v);
            AddTEdge(u,v);
            AddTEdge(v,u);
        }
        for (i=1;i<=m;i++)
        {
            //scanf("%d%d",&u,&v);
            get(u);
            get(v);
            if (u!=v)
            {
                AddQEdge(u,v);
                AddQEdge(v,u);
                degree[u]++;
                degree[v]++;
            }
        }
        ans=0;
        DFS(1);
        printf("%d\n",ans);
    }
}
