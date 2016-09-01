#include<cstdio>
#include<vector>
#include<cstring>
#define min(a,b) (a<b)?a:b;

using namespace std;

/*-----Cut_Bridge Template Start-----*/

const int MaxN = 101;
const int MaxE = 10010;

int vis[MaxN];  //v�Ƿ���ջ�У�0=δ���ʣ�1=��ջ�У�2=������� 
int dfn[MaxN];  //dfn[u]:������u���ʱ��;
int low[MaxN];  //low[u]:u��u�������ܹ�׷�ݵ��������ջ�нڵ�Ĵ����
int cut[MaxN];         //cut[i]=1˵����i���ڵ�Ϊ���
int root,BridgeNum;    //rootΪ���±�
int bridge[MaxE][2];   //�� 
vector<int> edge[MaxN];
 
void AddEdge(int u,int v)
{
    edge[u].push_back(v);
    edge[v].push_back(u);
}
 
void Cut_Bridge(int u, int fa, int dep)
{
    int v,i,son=0;
    vis[u]=1;           //��ǰ���ջ 
    dfn[u]=low[u]=dep;  //��ʼʱdfn[u]=low[u]
    for(i=0;i<edge[u].size();i++) //�������б� 
    {
        v=edge[u][i];
        if (vis[v]==1 && v!=fa)         //�ҵ�һ������ǿ��ͨ������ 
            low[u]=min(low[u],dfn[v]);  //���µ�ǰ���lowֵ 
        if (vis[v]==0)
        {
            Cut_Bridge(v,u,dep+1);      //���±��� 
            son++;
            low[u]=min(low[u],low[v]);  //ȷ��low[u]��С
            //��� 
            if ((u==root && son>1) || (u!=root && low[v]>=dfn[u])) cut[u]=1;
            //��(u,v)���� 
            if (low[v] > dfn[u])       
            {
                bridge[BridgeNum][0]=u;
                bridge[BridgeNum++][1]=v;   
            } 
        }
    }
    vis[u]=2;
}

void  InitCutBridge(int TargetRoot,int PointNum)
{
    int i;
    root=TargetRoot;
    memset(cut,0,sizeof(cut));
    memset(vis,0,sizeof(vis));
    memset(low,0,sizeof(low));
    memset(dfn,0,sizeof(dfn));
    for (i=1;i<=PointNum;i++) edge[i].clear(); //������� 
}

/*-----Cut_Bridge Template Over-----*/

int n;

int main()
{
    int u,v,ans,i;
    freopen("poj1144.txt","r",stdin);
    freopen("poj1144ans.txt","w",stdout);
    while(scanf("%d",&n)!=EOF && n)
    {
        InitCutBridge(1,n);
        while (scanf("%d",&u)!=EOF && u)
        {
            while (getchar()!='\n')
            {
                scanf("%d",&v);
                AddEdge(u,v);
            }
        }
        Cut_Bridge(1,1,1);
        ans=0;
        for (i=1;i<=n;i++) ans+=cut[i];
        printf("%d\n",ans);
    }
}
