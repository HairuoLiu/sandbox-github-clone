#include <stdio.h>  
#include <string.h> 

#define MaxN 305 
#define MaxE 2*3005 
#define INF  99999999.0  
#define eps  0.0005 

/*----------ISAP Template Start----------*/

struct TEdge
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
    int now,neck,tmp,i;
    double now_flow,max_flow;
    memset(dist,0,sizeof(dist));    
    memset(level,0,sizeof(level));
    memset(pre,-1,sizeof(pre));
    for(i=1;i<=pointnum;++i)  nowpath[i]=first[i];
    level[target]=pointnum;
    max_flow=0.0;
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

void AddEdge(int u,int v,double c)
{
    edges[index].next=first[u];
    edges[index].trg=v;
    edges[index].cap=c;
    edges[index].pair=index+1;
    first[u]=index++;
    edges[index].next=first[v];
    edges[index].trg=u;
    edges[index].cap=0.0;
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

int d[MaxN],u[MaxE],v[MaxE],f[MaxN];
int n,m;

int Check(double mid)
{
    int i;
    double res;
    InitISAP(0,n+1,n+2);
    for (i=1;i<=m;i++)
    {
        AddEdge(u[i],v[i],1.0);
        AddEdge(v[i],u[i],1.0); 
    }
    for (i=1;i<=n;i++)
    {
        AddEdge(source,i,m);
        AddEdge(i,target,m+2*mid-d[i]);
    }
    res=ISAP();
    res=(m*n-res)/2.0;
    if (res>0.0) return 1; else return 0;
}

void DFS(int u)
{
    int i,v;
    f[u]=1;
    for (i=first[u];i!=-1;i=edges[i].next)
    {
        v=edges[i].trg;
        if (!f[v] && edges[i].cap>0) DFS(v);
    }
}

int main()
{
    int i,ans;
    double l,r,mid;
    freopen("poj3155.txt","r",stdin);
    freopen("poj3155ans.txt","w",stdout);
    while (scanf("%d%d",&n,&m)!=EOF)
    {
        memset(d,0,sizeof(d));
        for (i=1;i<=m;i++) 
	{
	    scanf("%d%d",&u[i],&v[i]);
	    d[u[i]]++;d[v[i]]++;
	}
        if (m==0)
        {
       	    printf("1\n1\n");
       	    continue;
        }
        l=0;r=m;
        while (r-l>eps)
        {
       	    mid=(l+r)/2;
       	    if (Check(mid)) l=mid; else r=mid;
        }
        Check(l);
        memset(f,0,sizeof(f));
        DFS(source);
        ans=0;
        for (i=1;i<=n;i++) ans+=f[i];
        printf("%d\n",ans);
        for (i=1;i<=n;i++) if (f[i]) printf("%d\n",i);
    }
    return 0;
}
