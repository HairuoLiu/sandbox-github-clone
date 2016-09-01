#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<queue>
using namespace std;
#define MAXN 205 
#define MAXE 2500   
#define INF 0x3f3f3f3f 

struct edge
{      
    int next,pair;    //ͬһ�����һ���ߵı�ţ�����ߵı��
    int trg,cap,flow; //�ñ�ָ��ĵ㣬�ñߵ�ʣ���������ñߵ�����         
}edges[MAXE];         //�߼� 
int first[MAXN];      //ÿһ��������ıߵĵ�һ���ı��
int source,target,index,pointnum; 

struct link
{
    int u,v,d;
}links[MAXE];

int ind[MAXN]; 

int m,s,has_odd_point,fullflow;

int SAP() 
{
    //������еĵ����Ŀ�����㵽�����룬��ǰ����·���еĸ��㣬�����ǰ��
    int level[MAXN],dist[MAXN],nowpath[MAXN],pre[MAXN];
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

void InitSAP()
{
    index=0;
    memset(first,-1,sizeof(first));
}

void ReadData()
{
    int src,trg,dt,i;
    scanf("%d %d",&m,&s);
    source=m+1;
    target=source+1;
    pointnum=target;
    index=1;
    for (i=1;i<=s;i++) 
    {
        scanf("%d %d %d",&src,&trg,&dt);
        links[index].u=src;
        links[index].v=trg;
        links[index++].d=dt;
    }
}

void AddEdges()
{
    int i;
    memset(ind,0,sizeof(ind));
    for (i=1;i<=s;i++)
    {
    	ind[links[i].u]--;
    	ind[links[i].v]++;
    	if (!links[i].d) AddEdge(links[i].u,links[i].v,1);
    }
    has_odd_point=0;
    fullflow=0;
    for (i=1;i<=m;i++) if (ind[i] & 1)
    {
    	has_odd_point=1;
    	return;
    }
    for (i=1;i<=m;i++)	
    {
    	if (ind[i]<0) AddEdge(source,i,(-ind[i])/2);
        if (ind[i]>0)
        {
       	    AddEdge(i,target,ind[i]/2);
       	    fullflow+=ind[i]/2;
        }
    }
}

int Solve()
{
    if (has_odd_point) return(0);
    if (SAP()<fullflow) return(0); else return(1);
}

int main() 
{
    freopen("poj1637.txt","r",stdin);
    freopen("poj1637ans.txt","w",stdout);
    long testcase;
    scanf("%d\n",&testcase);
    while(testcase--)
    {
    	ReadData();
    	InitSAP();
    	AddEdges();
    	if (Solve()) printf("possible\n"); else printf("impossible\n"); 
    }
    return 0;
}
