#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<queue>
using namespace std;
#define MAXN 235 
#define MAXE 235*235*2   
#define INF 0x3f3f3f3f

long source,target,index,pointnum;   
int k,c,m,minlen,maxlen;
int map[MAXN][MAXN]; 

struct edges{      
    long next,pair;    //ͬһ�����һ���ߵı�ţ�����ߵı��
    long trg,cap,flow; //�ñ�ָ��ĵ㣬�ñߵ�ʣ���������ñߵ�����         
}edges[MAXE];          //�߼� 

long first[MAXN];      //ÿһ��������ıߵĵ�һ���ı��

long SAP() 
{
    //������еĵ����Ŀ�����㵽�����룬��ǰ����·���еĸ��㣬�����ǰ��
    long level[MAXN],dist[MAXN],nowpath[MAXN],pre[MAXN];
    //��ǰ����·���ӵ��������ܵ������������ǰ�㣬��ǰ����·ƿ���� 
    long now_flow,max_flow,now,tmp,neck,i;
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
            dist[now]=tmp+1;               //���µ�ǰ��Ĳ�� 
            ++level[dist[now]];            //���µ�ǰ���εĵ��� 
            if(now!=source) now=pre[now];  //���ݵ���ǰ���ǰ���� 
        }
    }
    return max_flow;
}

void addedge(int u,int v,int c)
{  
    edges[index].next=first[u];
    edges[index].trg=v;
    edges[index].cap=c;
    edges[index].flow=0;
    edges[index].pair=index+1;
    first[u]=index++;
    edges[index].next=first[v];
    edges[index].trg=u;
    edges[index].cap=0;
    edges[index].pair=index-1;
    first[v]=index++;	
} 

void ReadData()
{
    int i,j,mid,n;
    n=k+c;
    minlen=INF;
    maxlen=0;
    for (i=1;i<=n;i++)
    {
        for (j=1;j<=n;j++)
        {
            scanf("%d",&map[i][j]);
            if (map[i][j]==0 && (i!=j)) map[i][j]=INF;
        }
    } 
    //Floyd to search the shortest distance
    for (mid=1;mid<=n;mid++)
        for (i=1;i<=n;i++)
            for (j=1;j<=n;j++)
            {
            	if (map[i][mid]!=INF && map[mid][j]!=INF)
                {
                    if (map[i][mid]+map[mid][j]<map[i][j]) 
	                map[i][j]=map[i][mid]+map[mid][j]; 
                    if (map[i][j]>maxlen) maxlen=map[i][j];
                    if (map[i][j]<minlen) minlen=map[i][j]; 
                } 
            }
}

void BuildMap(int len)
{
    int i,j;
    memset(first,-1,sizeof(first));
    index=0;
    for (i=k+1;i<=k+c;i++)
    {
    	for (j=1;j<=k;j++)
    	{
    	    if (map[i][j]<=len) addedge(i,j,1);
    	}
    }
    for (i=k+1;i<=k+c;i++) addedge(source,i,1);
    for (i=1;i<=k;i++) addedge(i,target,m);
}

int main() 
{
    freopen("poj2112.txt","r",stdio);
    freopen("poj2112ans.txt","w",stdout);
    index=0;
    long l,r,mid,cap;
    while(scanf("%d%d%d",&k,&c,&m)!=EOF)
    {
    	source=k+c+1;
    	target=k+c+2;
    	pointnum=k+c+2;
    	ReadData(); 
    	l=minlen;
    	r=maxlen;
    	while (l<r)
    	{
    	    mid=(l+r)/2;
    	    BuildMap(mid);
    	    cap=SAP();
    	    if (cap==c) r=mid; else l=mid+1;
    	}
    	printf("%d\n",l); 
    }
    return 0;
}
