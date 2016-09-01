#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<queue>

using namespace std;

#define min(x,y) ((x<y)?(x):(y))

#define INF 0x7fffffff
#define MaxPoint 405 
  
int c[MaxPoint][MaxPoint];       //�ڽӾ����ʾʣ������    
int dis[MaxPoint];               //��Դ����룬���ֲ�ͼ 
     
int N,F,D,ANS;               //NΪ������MΪ����
int source,target;

int BFS()   
{
    int i,j;
    queue<int> q;
    memset(dis,0xff,sizeof(dis));  //��-1�����Ϊδ���ʵı��   
    dis[source]=0;                 //Դ��ķֲ�Ϊ0
    q.push(source);
    while (!q.empty())
    {
        j=q.front();
        q.pop();
        for (i=0;i<=target;i++) if (dis[i]<0 && c[j][i]>0)
        {
            dis[i]=dis[j]+1;
            q.push(i);
        }
    }
    if (dis[target]>0) return 1; else return 0; //����DISС����,����BFS�������
}

//find����һ������,�������ر������������,����0��ʾ�޷�����   
//low��Դ�㵽������խ��(ʣ��������С)�ıߵ�ʣ������     
int find(int x,int low)
{
    int i,newcap=0;
    if (x==target) return low; //�ǻ�㣬ֱ�ӷ���
    for (i=0;i<=target;i++)  
        if (c[x][i]>0 && dis[i]==dis[x]+1 && (newcap=find(i,min(low,c[x][i]))))
		//   ��ͨ     ���Ƿֲ�ͼ����һ��  ��  �ܵ����(��������newcap<>0)    
        {
            c[x][i]-=newcap;
            c[i][x]+=newcap;
            return newcap;
        }
    return 0;
}

void ReadData()
{
    int fi,di,f,d,i;
    scanf("%d%d%d",&N,&F,&D);
    
	for (i=1;i<=F;i++) c[0][i]+=1;
    for (i=1;i<=N;i++) c[F+i][F+N+i]+=1;
    for (i=1;i<=D;i++) c[F+2*N+i][F+2*N+D+1]+=1;
    
    for (i=1;i<=N;i++)
    {
    	scanf("%d %d",&fi,&di);
    	while (fi--)
    	{
    		scanf("%d",&f);
    		c[f][F+i]+=1;
    	}
    	while (di--)
    	{
    		scanf("%d",&d);
    		c[F+N+i][F+2*N+d]+=1;
    	}
    }
} 

int main()
{
    freopen("poj3281.txt" ,"r",stdin);
    freopen("poj3281ans.txt","w",stdout);
    
    int newcap;
    
    memset(c,0,sizeof(c));
    ReadData();
	ANS=0;
	source=0;
	target=F+2*N+D+1;
    while(BFS())//Ҫ��ͣ�ؽ����ֲ�ͼ,���BFS�������Ž���
    {
	    //һ��BFSҪ��ͣ��������·,ֱ���Ҳ���Ϊֹ
        while(newcap=find(source,INF)) ANS+=newcap;
    }    
    printf("%d\n",ANS);    
}

