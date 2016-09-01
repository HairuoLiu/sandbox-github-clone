#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAXN 500 
#define MAXE 500*500*2   
#define INF 0x3f3f3f3f 

struct edge
{      
    int next,pair;    //ͬһ�����һ���ߵı�ţ�����ߵı��
    int trg,cap;      //�ñ�ָ��ĵ㣬�ñߵ�ʣ���������ñߵ�����         
}edges[MAXE];         //�߼� 
int first[MAXN];      //ÿһ��������ıߵĵ�һ���ı��
int source,target,index,pointnum; 

int f,p,cownum,filternum;
long long maxlen,minlen;

int f1[MAXN],f2[MAXN];

long long map[MAXN][MAXN]; 

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

void AddEdge(const int u,const int v,const int c)
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

void Floyd()
{
    int i,j,mid;
    for (mid=1;mid<=f;mid++)
        for (i=1;i<=f;i++)
            for (j=1;j<=f;j++)
            {
                if (map[i][mid]+map[mid][j]<map[i][j]) map[i][j]=map[i][mid]+map[mid][j]; 
                if (map[i][j]>maxlen && map[i][j]<0x3f3f3f3f3f3f3f3f) maxlen=map[i][j];
                if (map[i][j]<minlen) minlen=map[i][j]; 
            } 
} 

void ReadData()
{
    int i,j,cow,filter,x,y,l;
    memset(map,0x3f3f3f3f,sizeof(map));
    source=2*f+1;
    target=source+1;
    pointnum=target;
    cownum=filternum=0;
    maxlen=0;
    minlen=INF;
    
    for (i=1;i<=f;i++)
    {
        scanf("%d %d",&cow,&filter);
        cownum+=cow;
        filternum+=filter;
        f1[i]=cow;
        f2[i]=filter;
    }

    for (i=1;i<=f;i++) map[i][i]=0;
    for (i=1;i<=p;i++)
    {
        scanf("%d %d %d",&x,&y,&l);
        if (l<map[x][y]) map[x][y]=map[y][x]=l;
    }
    Floyd();
}

void BuildMap(long long mid)
{
	int i,j,ff;
	InitSAP();
	for (i=1;i<=f;i++) AddEdge(i,i+f,INF);
    for (i=1;i<=f;i++)
    {
    	AddEdge(source,i,f1[i]);
    	AddEdge(i+f,target,f2[i]);
    }
    for (i=1;i<=f;i++)
        for (j=1;j<=f;j++)
            if (map[i][j]<=mid) AddEdge(i,j+f,INF);
} 

long long Solve()
{
    long long l,r,mid;
    int hasans=0;
    int flow;
    if (cownum>filternum) return(-1); 
    l=minlen;
    r=maxlen;
    while (l<=r)
    {
        mid=(l+r)/2;
        BuildMap(mid);
        flow=SAP();
        if (flow>=cownum) 
        {
            r=mid;
            if (l==r) r--;  
            hasans=1;
	}
        else l=mid+1;
    }
    if (hasans) return(l);else return(-1);
}

int main()
{
    freopen("poj2391.txt","r",stdin);
    freopen("poj2391ans.txt","w",stdout);
    while (scanf("%d %d",&f,&p)!=EOF)
    {
        ReadData();
        printf("%lld\n",Solve());
    }
} 
