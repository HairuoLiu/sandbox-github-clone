#include <cstdlib>  
#include <cstdio>  
#include <cstring> 

#define min(a,b) (a<b)?a:b;
 
using namespace std;  

const int MaxN = 501;  
const int INF  = 0x3F3F3F3F;  

int n,m;
int v[MaxN];          //�����ĵ㼯 
int map[MaxN][MaxN];  //��Ȩ�ڽӾ��� 
int dis[MaxN];        //�����ĳһ�㵽��ǰS���ľ��� 
bool vis[MaxN];       //���ʱ�� 

int Stoer_Wagner(int n)   
{  
    int i,j,res=INF,maxp,prev;
    for (i=0;i<n;i++) v[i]=i;  
    while (n>1)   
    {  
        maxp=1;
        prev=0;  
        for (i=1;i<n;i++) //��ʼ����S���ĸ��С,���ҳ�������Ķ���  
        {
            dis[v[i]]=map[v[0]][v[i]];  
            if (dis[v[i]]>dis[v[maxp]]) maxp=i;  
        }  
        memset(vis,0,sizeof(vis));  
        vis[v[0]]=1;  
        for (i=1;i<n;i++)   
        {  
            if (i==n-1) //ֻʣ���һ��û���뼯�ϵĵ㣬������С��  
            {   
                res=min(res,dis[v[maxp]]);  
                for (j=0;j<n;j++) //�ϲ����һ�����Լ��Ƴ����ļ����еĵ�  
                {   
                    map[v[prev]][v[j]]+=map[v[j]][v[maxp]];  
                    map[v[j]][v[prev]]=map[v[prev]][v[j]];  
                }  
                n--;
                v[maxp]=v[n]; //����  
            }  
            vis[v[maxp]]=1;  
            prev=maxp;  
            maxp=-1;  
            for (j=1;j<n;j++) if (!vis[v[j]])   //�������л�û���������ĵ� 
            {   
                dis[v[j]]+=map[v[prev]][v[j]];  //���¾���ֵ 
                if (maxp==-1 || dis[v[maxp]]<dis[v[j]]) maxp=j;  //�������ֵ�� 
            }  
        } 
    }
    return res;  
}  

int main()
{   
    while (scanf("%d%d", &n, &m) != EOF)
    {  
        memset(map,0,sizeof (map));  
        int u,v,w;  
        while (m--)
        {  
            scanf("%d%d%d",&u,&v,&w);  
            map[u][v]+=w;  
            map[v][u]+=w;  
        }  
        printf("%d\n",Stoer_Wagner(n));  
    }  
    return 0;  
} 
