#include <cstdlib>  
#include <cstdio>  
#include <cstring> 
#include <cmath>

#define min(a,b) (a<b)?a:b;
#define MaxN 102
#define MaxE 2*602 
#define INF  0x3F3F3F3F 
 
using namespace std;   

/*----------ISAP Template Start----------*/

struct Tedge
{      
    int next,pair,trg;//ͬһ�����һ���ߵı�ţ�����ߵı�ţ��ñ�ָ��ĵ�  
    double cap;       //�ñߵ�ʣ������ 
}edges[MaxE];         //�߼� 
int first[MaxN];      //ÿһ��������ıߵĵ�һ���ı��
int source,target,index,pointnum; 

int level[MaxN];   //������еĵ����Ŀ
int dist[MaxN];    //���㵽������
int nowpath[MaxN]; //��ǰ����·���еĸ���
int pre[MaxN];     //�����ǰ��

double ISAP() 
{
    //��ǰ����·���ӵ��������ܵ������������ǰ�㣬��ǰ����·ƿ���� 
    int now,tmp,neck,i;
    double now_flow,max_flow; 
    memset(dist,0,sizeof(dist));    
    memset(level,0,sizeof(level));
    memset(pre,-1,sizeof(pre));
    for(i=1;i<=pointnum;++i)  nowpath[i]=first[i];
    level[target]=pointnum;
    max_flow=0;
    now=source;
    while(dist[source]<pointnum)     
    {   //�����ǰ���Ѿ�����Ŀ�ĵ㣬����·Ѱ�����         
        if(now==target)         
        {
            //Ѱ������·�е������������������ͬʱ���ƿ���� 
            now_flow=INF;
            for(i=source;i!=target;i=edges[nowpath[i]].trg)
            {
                if(now_flow>edges[nowpath[i]].cap)
                {
                    neck=i;
                    now_flow=edges[nowpath[i]].cap;
                }
            }
            //��������·�ϸ�·����������Ϣ   
            for(i=source;i!=target;i=edges[nowpath[i]].trg)
            {
                tmp=nowpath[i];
                edges[tmp].cap-=now_flow;
                tmp=edges[tmp].pair;
                edges[tmp].cap+=now_flow;
            }
            max_flow+=now_flow;
            now=neck; 
        }          
        
        //�����ǰδ��������· 
        
        //�Ե�ǰ����һ�����ñ�        
        for(i=nowpath[now];i!=-1;i=edges[i].next)
            if(edges[i].cap>0 && dist[now]==dist[edges[i].trg]+1) break;

        if(i!=-1)   //�п��ñߣ�ʹ�ò���¼    
        {
            nowpath[now]=i;
            pre[edges[i].trg]=now;
            now=edges[i].trg;
        }
        else        //û�п��ñ� 
        {
            level[dist[now]]--;
            if(0==level[dist[now]]) break;  //���ֶϲ㣬��ֹ�㷨������ 
            nowpath[now]=first[now];        //ɾ����ǰ����·��һ����¼���ָ���ʼֵ 
            //�������е�ǰ��ָ��ĵ㣬�����в����С��
            tmp=pointnum; 
            for (i=first[now];i!=-1;i=edges[i].next)
              if(edges[i].cap>0) tmp=min(tmp,dist[edges[i].trg]);
            dist[now]=tmp+1;             //���µ�ǰ��Ĳ�� 
            ++level[dist[now]];       //���µ�ǰ���εĵ��� 
            if(now!=source) now=pre[now];  //���ݵ���ǰ���ǰ���� 
        }
    }
    return max_flow;
}

void AddEdge(int u,int v,double c)
{
    edges[index].next=first[u];
    edges[index].trg=v;
    edges[index].cap=c;
    edges[index].pair=index+1;
    first[u]=index++;
    edges[index].next=first[v];
    edges[index].trg=u;
    edges[index].cap=0;
    edges[index].pair=index-1;
    first[v]=index++;	
}

void InitISAP(int S,int T,int Num)
{
    index=0;
    source=S;
    target=T;
    pointnum=Num;
    memset(first,-1,sizeof(first));
}

/*----------ISAP Template Over----------*/

int n,m,edgenum;

void ReadData()
{
    int i,u,v;
    double weight;
    scanf("%d%d%d",&n,&m,&edgenum);
    InitISAP(0,n+m+1,n+m+2);
    for (i=1;i<=n;i++) 
    {
        scanf("%lf",&weight);
        weight=log(weight);
        AddEdge(source,i,weight);
    }
    for (i=n+1;i<=n+m;i++) 
    {
        scanf("%lf",&weight);
        weight=log(weight);
        AddEdge(i,target,weight);
    }
    for (i=0;i<edgenum;i++)
    {
        scanf("%d%d",&u,&v);
        AddEdge(u,n+v,INF);
    }
}

int main()
{
    int testcase;
    double ans;
    freopen("poj3308.txt","r",stdin);
    freopen("poj3308ans.txt","w",stdout);
    scanf("%d",&testcase);
    while (testcase--)
    {
        ReadData();
        ans=ISAP();
        ans=exp(ans);
        printf("%.4f\n",ans);
    }
    return 0;
}
