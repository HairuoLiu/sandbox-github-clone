#include <stdlib.h> 
#include <stdio.h>  
#include <string.h> 

#define min(a,b) (a<b)?a:b;
#define MaxN 1020+50
#define MaxE 2*25*1005
#define INF  0x3F3F3F3F  

/*----------ISAP Template Start----------*/

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

int n,b;
int rank[MaxN][MaxN];
int cap[21];

int Test(int range)
{
	int start,end,i,j;
	for (start=1;start<=b-range+1;start++)
	{
	    end=start+range-1;
	    InitISAP(0,n+b+1,n+b+2);
	    for (i=1;i<=n;i++)
	    {
	        AddEdge(source,i,1);
	        for (j=start;j<=end;j++) AddEdge(i,n+rank[i][j],1);
	    }
	    for (i=1;i<=b;i++) AddEdge(n+i,target,cap[i]);
	    if (ISAP()==n) return 1;
	}
    return 0;
}

int Solve()
{
    int l=1,r=b,range=-1,mid;
    while (l<=r)
    {
        mid=(l+r)/2;
        if (Test(mid))
        {
            range=mid;
            r=mid-1;
        }
        else l=mid+1;
    }
    return range;
}

int main()
{
    int i,j,ans;
    freopen("poj3189.txt","r",stdin);
    freopen("poj3189ans.txt","w",stdout);
    while (scanf("%d%d",&n,&b)!=EOF)
    {
        for (i=1;i<=n;i++)
            for (j=1;j<=b;j++) scanf("%d",&rank[i][j]);
        for (i=1;i<=b;i++) scanf("%d",&cap[i]);
        ans=Solve();
        printf("%d\n",ans);
    }
}
