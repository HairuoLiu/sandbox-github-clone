#include<cstdio>
#include<cstring>
#include<cstdlib>

#define INF 0x3f3f3f3f 
#define MaxN 202
#define MaxE 10400 

using namespace std;

/*----------ISAP Template Start----------*/

struct Tedge
{      
    int next,pair;    //ͬһ�����һ���ߵı�ţ�����ߵı��
    int trg,cap,flow; //�ñ�ָ��ĵ㣬�ñߵ�ʣ���������ñߵ�����         
}edges[MaxE];         //�߼� 
int first[MaxN];      //ÿһ��������ıߵĵ�һ���ı��
int source,target,index,pointnum; 

int m,n; 

int level[MaxN];   //������еĵ����Ŀ
int dist[MaxN];    //���㵽������
int nowpath[MaxN]; //��ǰ����·���еĸ���
int pre[MaxN];     //�����ǰ��

int ISAP() 
{
    //��ǰ����·���ӵ��������ܵ������������ǰ�㣬��ǰ����·ƿ���� 
    int now_flow,max_flow,now,tmp,neck,i;
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
              if(edges[i].cap>0)
                tmp=tmp<dist[edges[i].trg]?tmp:dist[edges[i].trg];
            dist[now]=tmp+1;             //���µ�ǰ��Ĳ�� 
            ++level[dist[now]];       //���µ�ǰ���εĵ��� 
            if(now!=source) now=pre[now];  //���ݵ���ǰ���ǰ���� 
        }
    }
    return max_flow;
}

void AddEdge(int u,int v,int c)
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

int N,M;
int flag[MaxN];

void DFS(int u)
{
    int i,v;
    flag[u]=1;
    for (i=first[u];i!=-1;i=edges[i].next)
    {
        v=edges[i].trg;
        if (edges[i].cap && !flag[v]) DFS(v);
    }
}

int main()
{
    int i,u,v,inv,outv,MinCut,Operate;
    freopen("poj2125.txt","r",stdin);
    freopen("poj2125ans.txt","w",stdout);
    while (scanf("%d%d",&N,&M)!=EOF)
    {
    	InitISAP(0,2*N+1,2*N+2);
        for (i=1;i<=N;i++)
        {
       	    scanf("%d",&inv);
       	    AddEdge(i+N,target,inv);
        }
        for (i=1;i<=N;i++)
        {
       	    scanf("%d",&outv);
       	    AddEdge(source,i,outv);
        }
        for (i=0;i<M;i++)
        {
       	    scanf("%d%d",&u,&v);
       	    AddEdge(u,v+N,INF);
        }
        MinCut=ISAP();
        Operate=0;
        memset(flag,0,sizeof(flag));
        DFS(source);
        for (i=1;i<=N;i++)
        {
       	    if (0==flag[i])   Operate++;
       	    if (1==flag[i+N]) Operate++;
        }
        printf("%d\n",MinCut);
        printf("%d\n",Operate);
        for (i=1;i<=N;i++)
        {
       	    if (0==flag[i])   printf("%d -\n",i);
       	    if (1==flag[i+N]) printf("%d +\n",i);
        }
    }
}
