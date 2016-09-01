#include<stdio.h>
#include<string.h>

#define CharsetSize 2
#define CharsetBase 0
#define MaxN 100001

struct TEdge
{
    int v,w,next;
}edge[MaxN*2];

int head[MaxN],eindex;
int vis[MaxN];

struct TrieNode
{
    //int flag;
    int next[CharsetSize];
}trie[MaxN*16];   //�����ֵ����֣���Ҳû������Ϊʲô

int tindex;

int XorValue[MaxN];

void AddEdge(int u,int v,int w)
{
    edge[eindex].v=v;
    edge[eindex].w=w;
    edge[eindex].next=head[u];
    head[u]=eindex++;
    edge[eindex].v=u;
    edge[eindex].w=w;
    edge[eindex].next=head[v];
    head[v]=eindex++;
}

void dfs(int u,int val)
{
    int i;
    XorValue[u]=val;
    vis[u]=1;
    for (i=head[u];i;i=edge[i].next)
	if (!vis[edge[i].v]) dfs(edge[i].v,val^edge[i].w);
}

void Insert(int num)
{
    int i,p=0,a;
    for (i=30;i>=0;i--)
    {
	a=num&(1<<i)?1:0;  //ȡnum�Ķ����Ƶ�i+1λ�ϵ�����
	if (trie[p].next[a]==0)
	{
	    trie[p].next[a]=++tindex;
	    trie[tindex].next[0]=trie[tindex].next[1]=0; //��Ҫͬʱ��˫���ʼ����������
	}
	p=trie[p].next[a];
    }
}

int FindMax(int num)
{
    int i,p=0,a,res=0;
    for (i=30;i>=0;i--)
    {
	a=num&(1<<i)?0:1;
	if (trie[p].next[a])    //����ֵ�����һλ�͵�ǰ���ֵĲ�һ��
	{
	    res|=(1<<i);        //ȡ��һλ
	    p=trie[p].next[a];  //������
        }
        else p=trie[p].next[!a];//����ԭ������
    }
    return res;
}

int main()
{
    int n,i,u,v,w,max,res;
    freopen("poj3764.txt","r",stdin);
    freopen("poj3764ans.txt","w",stdout);
    while (scanf("%d",&n)!=EOF)
    {
	eindex=tindex=1;
	memset(head,0,sizeof(head));
	memset(vis,0,sizeof(vis));
	for (i=1;i<n;i++)
	{
	    scanf("%d%d%d",&u,&v,&w);
	    AddEdge(u,v,w);
	}
	dfs(0,0); //�ݹ��ҽ��0����������򳤶�
	trie[0].next[0]=trie[0].next[1]=0;
	max=0;
	for (i=0;i<n;i++)
	{
	    Insert(XorValue[i]);      //��0��i����򳤶Ȳ����ֵ���
	    res=FindMax(XorValue[i]); //�����ֵ������Ѵ泤����0��i����򳤶���������ֵ
	    if (res>max) max=res;
	}
	printf("%d\n",max);
    }
    return 0;
}
