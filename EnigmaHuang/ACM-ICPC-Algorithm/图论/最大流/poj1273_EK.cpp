/*
�ڳ���ʵ�ֵ�ʱ������ֻ����һ��cap��������¼������������¼������
������+1��ʱ�����ǿ���ͨ������-1��ʵ�֣��Է�������ʵ�֡�
������cap[u][v],������cap[v][u]��ʾ��

328K��16MS
*/

#include<iostream>
#include<queue>

using namespace std;

const int N=201;  
const int INF=0x7fffffff;
int n,m,sum,s,t,w;           //s,tΪʼ����յ�
int cap[N][N],a[N],p[N];

int min(int a,int b) {return a<=b?a:b;}

void Edmonds_Karp() 
{
    int i,u,v;
    queue<int> q;  //���У���bfs������·
    while(1) 
    {
        memset(a,0,sizeof(a));//ÿ��һ�Σ���ʼ��һ��
        a[s]=INF;
        q.push(s);//Դ�����    
        while(!q.empty())
        {
            u=q.front();
            q.pop();
            for(v=1;v<=m;v++)
            {
                if(!a[v]&&cap[u][v]>0)
                {
	            p[v]=u;
	            q.push(v);
	            a[v]=min(a[u],cap[u][v]);//s-v·���ϵ���С����
	            }
	        }
	    }
		
	    if(a[m]==0) break; //�Ҳ�������·,��ǰ���Ѿ��������
	     
	    sum+=a[m];//������
	    for(i=m;i!=s;i=p[i]) //�ӻ��˳����������·������
	    {
	        cap[p[i]][i]-=a[m];//������������
	        cap[i][p[i]]+=a[m];//���·�������
	    }
    }
}

int main() 
{  
    //freopen("poj1273.txt","r",stdin);
	//freopen("poj1273ans.txt","w",stdout);
    int v,u;
    while(scanf("%d%d",&n,&m)!=EOF)
    {
	s=1;//��1��ʼ
	t=m;//mΪ���
	sum=0;//��¼�������
	memset(cap,0,sizeof(cap));//��ʼ��
	while(n--)
	{
	    scanf("%d%d%d",&u,&v,&w);
	    cap[u][v]+=w;//ע��ͼ�п��ܳ�����ͬ�ı�
        }
	Edmonds_Karp();
	printf("%d\n",sum);
    }
    return 0;
}