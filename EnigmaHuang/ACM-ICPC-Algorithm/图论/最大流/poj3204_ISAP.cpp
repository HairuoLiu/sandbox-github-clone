#include <stdlib.h> 
#include <stdio.h>  
#include <string.h> 
#include <vector>

#define min(a,b) (a<b)?a:b;
#define MaxN 1000
#define MaxE 50000
#define INF  0x3F3F3F3F  

/*----------ISAP Template Start----------*/

using namespace std;

struct TEdge
{      
    int next,pair,trg;//ͬһ�����һ���ߵı�ţ�����ߵı�ţ��ñ�ָ��ĵ� 
    int cap;          //�ñߵ�ʣ������       
}edges[MaxE];         //�߼� 
int first[MaxN];      //ÿһ��������ıߵĵ�һ���ı��
int source,target,index,pointnum; 

int level[MaxN];   //������еĵ����Ŀ
int dist[MaxN];    //���㵽������
int nowpath[MaxN]; //��ǰ����·���еĸ���
int pre[MaxN];     //�����ǰ��

int ISAP() 
{
    //��ǰ����·���ӵ��������ܵ������������ǰ�㣬��ǰ����·ƿ���� 
    int now_flow,max_flow,now,neck,tmp,i;
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
            if (now_flow==INF) return(now_flow);
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

int n,m;
int u[MaxE],v[MaxE];
int SSet[MaxN],TSet[MaxN];  //��С�������Դ�ļ��Ϻͻ�ļ��� 

vector <int> ef[MaxN],eb[MaxN];  //ǰ����ıߣ��������� 

void DFSF(int u)
{
    int i,v;
    SSet[u]=1;
    for (i=0;i<ef[u].size();i++)
    {
       v=ef[u][i];
       if (!SSet[v]) DFSF(v);
    }
}

void DFSB(int u)
{
    int i,v;
    TSet[u]=1;
    for (i=0;i<eb[u].size();i++)
    {
       v=eb[u][i];
       if (!TSet[v]) DFSB(v);
    }
}

int main()
{
    int i,w,eid,ans;
    freopen("poj3204.txt","r",stdin);
    freopen("poj3204ans.txt","w",stdout);
    while (scanf("%d%d",&n,&m)!=EOF)
    {
        InitISAP(0,n-1,n);
        for (i=1;i<=m;i++)
        {
            scanf("%d%d%d",&u[i],&v[i],&w);
            AddEdge(u[i],v[i],w);
        }
        ISAP();
        for (i=0;i<MaxN;i++)  //������� 
        {
            ef[i].clear();
            eb[i].clear();
        }
        for (i=0;i<index;i+=2) if (edges[i].cap) //������в�����������Ϊ���ñ� 
		{
		    eid=i/2+1;  //ȡԭʼ�߶��Ƕ�ż����߱��
		    ef[u[eid]].push_back(v[eid]); //��������ͼ�ӱ� 
		    eb[v[eid]].push_back(u[eid]); //��������ͼ�ӱ� 
		}
		memset(SSet,0,sizeof(SSet));
		memset(TSet,0,sizeof(TSet));
		DFSF(source); //��������Ⱦɫ 
		DFSB(target); //��������Ⱦɫ 
		ans=0;
		for (i=0;i<index;i+=2) if (edges[i].cap==0) //�������ϵı�
		{
		    eid=i/2+1;
		    if (SSet[u[eid]] && TSet[v[eid]]) ans++;
		}
		printf("%d\n",ans);
    }
    return 0;
}
