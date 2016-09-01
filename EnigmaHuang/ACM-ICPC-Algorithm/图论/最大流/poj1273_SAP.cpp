#include<iostream>
#include<cstdio>
#include<memory.h>
#include<cmath>
using namespace std;
#define MAXN 201
#define MAXE 201*201*2   
#define INF 0x7fffffff
long m,n,tmp,source,target,index,pointnum;   

struct edges
{
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
            nowpath[now]=first[now];        //ɾ����ǰ����·��һ����¼���ָ���ʼ

ֵ 
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

int main() 
{
    freopen("poj1273.txt","r",stdin);
    freopen("poj1273ans.txt","w",stdout);
    index=0;
    long i,j,a,b,val;
    long c[MAXN][MAXN];
    while(scanf("%d%d",&m,&n)!=EOF)
    {
        s=1;
        t=n;
        memset(c,0,sizeof(c));
        memset(first,-1,sizeof(first));
        for(i=0;i<m;++i)
        {
            scanf("%ld%ld%ld",&a,&b,&val);
            c[a][b]+=val;
        }
        for(i=1;i<=n;++i)
            for(j=i;j<=n;++j) if(c[i][j]||c[j][i])
            {
                //��������  
                edges[index].next=first[i];
                edges[index].trg=j;
                edges[index].cap=c[i][j];
                edges[index].flow=0;
                edges[index].pair=index+1;
                first[i]=index++;
                //��ӷ����
                edges[index].next=first[j];
                edges[index].trg=i;
                edges[index].cap=c[j][i];
                edges[index].flow=0;
                edges[index].pair=index-1;
                first[j]=index++;
            }
        printf("%ld\n",SAP());
    }
    return 0;
}
