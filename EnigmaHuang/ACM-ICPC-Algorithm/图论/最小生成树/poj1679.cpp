#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>

using namespace std;

#define MaxN 101
#define MaxE 101*101

int succ;

/*---------------Kruskal Template Start---------------*/

struct TEdge
{
    int u,v,w,used;
}edge[MaxE];

int father[MaxN],edgenum;

void InitEdge() 
{
    edgenum=0;
}

void AddEdge(int u,int v,int w)
{
    edge[edgenum].u=u;
    edge[edgenum].v=v;
    edge[edgenum].w=w;
    edge[edgenum].used=0;
    edgenum++;
}

int cmp(const void *a, const void *b) //��������д������ 
{
    return (*(struct TEdge *)a).w - (*(struct TEdge *)b).w;
}

int GetFather(int x)
{
    if (x!=father[x]) father[x]=GetFather(father[x]); //·���ϲ� 
    return father[x];
}

int Kruskal(int nodenum)
{
    int cnt=0,i,res=0,f1,f2; 
    for (i=1;i<=nodenum;i++) father[i]=i;  //��ʼ�����鼯 
    for (i=0;i<edgenum;i++)
    {
        if (edge[i].used) continue;
        f1=GetFather(edge[i].u);
        f2=GetFather(edge[i].v);
        if (f1!=f2)
        {
            father[f1]=f2;
            res+=edge[i].w;
            edge[i].used=1;
            cnt++;
            if (cnt==nodenum-1) break;    //�Ѿ�������n-1���ߣ������С������ 
        }
    }
    if (cnt==nodenum-1) succ=1;else succ=0;
    return res;
}

/*---------------Kruskal Template Start---------------*/

int main()
{
    int i,j,u,v,w,testcase,m,n,ans,res;
    int anse[MaxN],pos;
    freopen("poj1679.txt","r",stdin);
    freopen("poj1679ans.txt","w",stdout);
    scanf("%d",&testcase);
    while (testcase--)
    {
        scanf("%d%d",&n,&m);
        InitEdge();
        for (i=1;i<=m;i++)
        {
            scanf("%d%d%d",&u,&v,&w);;
            AddEdge(u,v,w);
        }
        qsort(edge,edgenum,sizeof(TEdge),cmp); //�Ա߰�Ȩ��С�������� 
        ans=Kruskal(n); //����С������ 
        /* ����˵Ӧ���ж��Ƿ���ͨ�ġ��������ж��˷��������� 
        if (!succ)
        {
            printf("0\n");
            continue; 
        } 
        */
        pos=0;
        for (i=0;i<edgenum;i++) if (edge[i].used) anse[++pos]=i; //��¼��С�������ı� 
        for (i=1;i<=pos;i++) //����ȥ����С�������ıߣ����С������ 
        {
            for (j=0;j<edgenum;j++) edge[j].used=0;
            edge[anse[i]].used=1;
            res=Kruskal(n);
            if (!succ) continue; //�޷����� 
            if (res==ans) //��С��������Ψһ���˳� 
            {
                ans=-1;
                break;
            }
        }
        if (ans==-1) printf("Not Unique!\n"); else printf("%d\n",ans);
    }
    return 0;
}
