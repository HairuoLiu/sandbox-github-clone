#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define min(a,b) (a<b)?a:b;
#define max(a,b) (a>b)?a:b;

#define MaxN 4005
#define MaxE 210000

/*----------Tarjan Template Start----------*/

int dfn[MaxN];  //dfn[u]:������u���ʱ��; 
int low[MaxN];  //low[u]:u��u�������ܹ�׷�ݵ��������ջ�нڵ�Ĵ����
int grp[MaxN];  //grp[u]:u���ڵ���ͨ�����ı��
int vis[MaxN];  //v�Ƿ���ջ��

int map[MaxN][MaxN];  //�߱�ǣ��ÿռ任ʱ��ɡ��� 

int stack[MaxN],top,scc,cnt,n;

void Tarjan(int u)
{
    int v,i;
    dfn[u]=low[u]=++cnt;//��ʼʱdfn[u]==low[u]
    stack[top++]=u;     //��ǰ���ջ
    vis[u]=1;
    for (v=1;v<=2*n;v++)
    {
        if (!map[u][v]) continue;
        if (!dfn[v]) //���v�㻹δ����
        {
            Tarjan(v); //���±���
            low[u]=min(low[u],low[v]) //ȷ��low[u]��С
        }
        else if (vis[v]) low[u]=min(low[u],dfn[v]);
        //v��ջ�У��޸�low[u]          
    }
    if (dfn[u]==low[u])     //uΪ��ǿ��ͨ�����б����������ĸ�
    {
        scc++;
        while (1)
        {
            v=stack[--top]; //ջ�����е�u�ĵ㶼���ڸ�ǿ��ͨ��������ջ
            vis[v]=0;
            grp[v]=scc;
            if (u==v) break;
        } 
    }
}

void TarjanSolve(int NodeNum)
{
    int u;
    scc=top=cnt=0;
    memset(dfn,0,sizeof(dfn));
    memset(vis,0,sizeof(vis));
    memset(low,0,sizeof(low));
    for (u=1;u<=NodeNum;u++) if (!dfn[u]) Tarjan(u);
}

/*----------Tarjan Template Over----------*/

int ans[2002],pos;

int main()
{
    int i,num,u,v,j;
    freopen("poj1904.txt","r",stdin);
    freopen("poj1904ans.txt","w",stdout);
    while (scanf("%d",&n)!=EOF)
    {
        memset(map,0,sizeof(map));
        for (u=1;u<=n;u++)
        {
            scanf("%d",&num);
            for (i=1;i<=num;i++)
            {
                scanf("%d",&v);
                map[u][v+n]=1;
            }
        }
        for (u=1;u<=n;u++)
        {
            scanf("%d",&v);
            map[v+n][u]=1;
        }
        TarjanSolve(2*n);
        for (i=1;i<=n;i++)
        {
            pos=0;
            for (j=n+1;j<=2*n;j++) 
            if (map[i][j] && grp[i]==grp[j]) ans[++pos]=j-n; //�а�Ů������ͬһ��ͨ�����������ڼ��� 
            printf("%d",pos);
            for (j=1;j<=pos;j++) printf(" %d",ans[j]);
            printf("\n");    
        }
    }
}
