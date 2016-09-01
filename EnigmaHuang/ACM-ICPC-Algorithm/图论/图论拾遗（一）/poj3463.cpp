#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<queue>

using namespace std;

#define inf  0x3f3f3f3f 
#define MaxN 1005
#define MaxE 10050

int dis[MaxN][2],cnt[MaxN][2],vis[MaxN][2];

struct edge
{
    int u,v,dis,next;
}edge[MaxE];
int head[MaxN],index,source,target;

struct Node
{
    int u;
    int flag;             //��ʾ�ڵ����ͣ�0��ʾ��̣�1��ʾ�ζ�
    bool operator < (const Node &a)const
    {
        return dis[u][flag]>dis[a.u][a.flag];
    }
};

void AddEdge(int u,int v,int w)
{
    edge[index].u=u;
    edge[index].v=v;
    edge[index].dis=w;
    edge[index].next=head[u];
    head[u]=index++;
}

void InitEdge()
{
    memset(head,-1,sizeof(head));
    index=0;
}

int Dijkstra()
{
    int u,flag,i,to,dist; 
    Node top,newnode;
    priority_queue<Node>Q;
    memset(vis,0,sizeof(vis));
    memset(cnt,0,sizeof(cnt));
    memset(dis,inf,sizeof(dis));
    newnode.u=source;
    newnode.flag=0;
    Q.push(newnode);
    dis[source][0]=0;
    cnt[source][0]=1;
    while(!Q.empty())
    {
        top=Q.top();
        Q.pop();
        u=top.u;
        flag=top.flag;
        if (vis[u][flag]) continue;          //u���Ѿ�������ɳڲ��������� 
        for (i=head[u];i!=-1;i=edge[i].next) //����u��ĳ��� 
        {
            to=edge[i].v;
            dist=dis[u][flag]+edge[i].dis;
            if (dist<dis[to][0])             //����ҵ�·����ԭ���·����
            {
                if (dis[to][0]!=inf)         //ԭ���Ѿ��ҵ������·�������
                {
                    dis[to][1]=dis[to][0];   //ԭ���·��Ϊ�ζ�·                
                    cnt[to][1]=cnt[to][0];   //ԭ�ζ�·������Ϊ�ζ�·����
                    newnode.u=to;
                    newnode.flag=1;
                    Q.push(newnode);         //��ǰ��u�Ĵζ̾����ѱ����£�������� 
                }                                          
                dis[to][0]=dist;             //����u����̾���
                cnt[to][0]=cnt[u][flag];     //�������·����������һ�����/�ζ�·�������� 
                newnode.u=to;
                newnode.flag=0;
		Q.push(newnode);
            }
            else if (dist==dis[to][0])       //����ҵ�·���ľ����ԭ���·��ͬ
            {
                cnt[to][0]+=cnt[u][flag];    //�������·��������������Ҫ��Ӹ��� 
            }
            else if (dist<dis[to][1])        //����ҵ�·����ԭ�ζ�·��
            {
                dis[to][1]=dist;             //���´ζ�·
                cnt[to][1]=cnt[u][flag];     //���Ӵζ�·����
                newnode.u=to;
                newnode.flag=1;
		Q.push(newnode);             //��Ӹ��� 
            }
            else if (dist==dis[to][1])       //����ҵ�·���ʹζ�·��ͬ
            {
                cnt[to][1]+=cnt[u][flag];    //���Ӵζ�·���� 
            }
        }
        vis[u][flag]=1;                      //u��������ɳڲ��������֮ 
    }
    if (dis[target][0]+1==dis[target][1]) return cnt[target][0]+cnt[target][1];
    return cnt[target][0];
}

int n,m;

int main()
{
    int t,u,v,w;
    freopen("poj3463.txt","r",stdin);
    freopen("poj3463-2ans.txt","w",stdout);
    scanf("%d",&t);
    while(t--)
    {
        InitEdge(); 
        scanf("%d%d",&n,&m);
        while(m--)
        {
            scanf("%d%d%d",&u,&v,&w);
            AddEdge(u,v,w);
        }
        scanf("%d%d",&source,&target);
        printf("%d\n",Dijkstra());
    }
    return 0;
}
