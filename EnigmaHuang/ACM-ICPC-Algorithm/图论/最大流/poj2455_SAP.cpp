#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<queue>

using namespace std;

#define MAXN 201
#define MAXE 201*201*2   
#define INF 0x3f3f3f3f

long tmp,source,target,index,pointnum;   

struct edge{      
    long next,pair;    //ͬһ�����һ���ߵı�ţ�����ߵı��
    long trg,cap,len; //�ñ�ָ��ĵ㣬�ñߵ�ʣ���������ñߵ�����         
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
            dist[now]=tmp+1;             //���µ�ǰ��Ĳ�� 
            ++level[dist[now]];       //���µ�ǰ���εĵ��� 
            if(now!=source) now=pre[now];  //���ݵ���ǰ���ǰ���� 
        }
    }
    return max_flow;
}

void BuildMap(int l)
{
    int i;
    for (i=0;i<index;i++) 
        if (edges[i].len<=l) edges[i].cap=1;
        else edges[i].cap=0;
}

int main() 
{
    freopen("poj2455.txt","r",stdin);
    freopen("poj2455ans.txt","w",stdout);
    index=0;
    long l,r,n,p,t,a,b,minl,maxl,mid,i,ncap;
    while(scanf("%ld%ld%ld",&n,&p,&t)!=EOF)
    {
        source=1;
        target=n;
        pointnum=n;
	minl=INF;
	maxl=0;
        memset(first,-1,sizeof(first));
        for(i=0;i<p;++i)
        {
            scanf("%ld%ld%ld",&a,&b,&l);
            edges[index].next=first[a];
	    edges[index].trg=b;
	    edges[index].len=l;
	    edges[index].pair=index+1;
	    first[a]=index++;
            edges[index].next=first[b];
	    edges[index].trg=a;
	    edges[index].len=l;
	    edges[index].pair=index-1;
	    first[b]=index++;	
            if (minl>l) minl=l;
            if (maxl<l) maxl=l;			
        }
	l=minl;r=maxl;
	while (l<r)
	{
	    mid=(l+r)/2;
	    BuildMap(mid);
	    ncap=SAP();
	    if (ncap>=t) r=mid;
            else l=mid+1;			
	}
        printf("%ld\n",l);
    }
    return 0;
}