#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

#define INF 0x3f3f3f3f
#define MaxN 21 


int n,k,ROOT,mst;            //�ڵ���������������Ϊk�����ƽڵ��ţ����ս�� 
int g[MaxN][MaxN];           //ԭʼͼ
int father[MaxN];            //�ڵ�n�ĸ��ڵ�
int connect[MaxN][MaxN];     //�жϱ�(i,j)�Ƿ�����������
int maxlen[MaxN];            //��ROOT���ڵ�v��·������ROOT�޹ص����Ȩ�ߵĵ�
int visit[MaxN],mark[MaxN];  //ȫ�ֺ�Prim��DFS�õľֲ����ʱ�� 

map<string,int> mp;          //����->���ӳ��

void DFS(int now)            //��DFS���޸�������и���
{
    int i;
    for (i=0;i<n;i++)
    {
        if (connect[i][now] && mark[i])
        {
            father[i]=now;
            mark[i]=0;
            DFS(i);
        }
    }
}

int Prim(int source)//PRIM�㷨������1��MST
{
    int minlen,key,sum=0,i,subroot;
    int dis[MaxN],pre[MaxN];  //pre[x]��ʾx���disֵ����һ��ָ�� 

    memset(pre,0,sizeof(pre));
    memset(mark,0,sizeof(mark));
    mark[source]=1;
    visit[source]=1;
    
    for (i=0;i<n;i++)
    {
        dis[i]=g[source][i];
        pre[i]=source;
    }
    
    while (1)
    {
        minlen=INF;
        for (i=0;i<n;i++)
        {
            if (!visit[i] && !mark[i] && dis[i]<minlen)
            {
                minlen=dis[i];
                key=i;
            }
        }
        if (minlen>=INF) break;
        mark[key]=1;
        visit[key]=1;
        connect[pre[key]][key]=connect[key][pre[key]]=1;
        sum+=minlen;
        for (i=0;i<n;i++)
        {
            if (!visit[i] && !mark[i] && dis[i]>g[key][i])
            {
                dis[i]=g[key][i];
                pre[i]=key;
            }
        }
    }
    
    minlen=INF;
    subroot=-1;      //�ҵ���v0������ĵ����С�ߣ�����1���ߣ�����1��MST
    for (i=0;i<n;i++)
    {
        if (mark[i] && g[ROOT][i]<minlen)
        {
            minlen=g[ROOT][i];
            subroot=i;
        }
    }
    mark[subroot]=0;
    DFS(subroot);        //�����и���
    father[subroot]=ROOT;
    return sum+minlen;
}

int findMaxLen(int x)//���仯����ROOT��x�����Ȩֵ�ı�
{
    int tmp;
    if (father[x]==ROOT) return -1;      //����ڵ�ĸ��ڵ���ROOT�����ٲ���
    if (maxlen[x]!=-1) return maxlen[x]; //������ʹ��˽ڵ㣬������ȷ��ֵ
    tmp=findMaxLen(father[x]);
    //ȡROOT����һ�������뱾�㵽��һ��ı��нϳ���һ�� 
    if (tmp!=-1 && g[tmp][father[tmp]]>g[father[x]][x]) maxlen[x]=tmp;
    else maxlen[x]=x; 
    
    return maxlen[x];
}


void solve()
{
    memset(visit,0,sizeof(visit));
    memset(connect,0,sizeof(connect));
    memset(father,-1,sizeof(father));
    visit[ROOT]=1;
    int m=0,i,j,x,fatherx;
    int change;//��·��Ȩֵ���ıߣ����ڽ���
    mst=0;
    //����m��������С������
    for (i=0;i<n;i++)
    {
        if (!visit[i])
        {
            m++;
            mst+=Prim(i);
        }
    }
    //Ȼ����k-m�ε��滻�߲��� 
    for (i=1;i<=k-m;i++)
    {
        memset(maxlen,-1,sizeof(maxlen));
        for (j=0;j<n;j++)
        {
            if(maxlen[j]==-1 && father[j]!=ROOT) findMaxLen(j);
        }

        int minadd=INF; // �����ߵ���С��ֵ
        //ö��ÿһ����ROOT�����ıߣ���Ϊ�¼���ı�
        for (j=0;j<n;j++) if (g[ROOT][j]!=INF && father[j]!=ROOT) 
        {
            x=maxlen[j];
            //ȡԭ��ROOT��������·���ϵ���ı� 
            fatherx=father[x];
            //���߱Ƚ�ȡ��ֵ
            if (g[ROOT][j]-g[x][fatherx]<minadd)
            {
                minadd=g[ROOT][j]-g[x][fatherx];
                change=j;
            }
        }
        if (minadd>=0) break; //ROOT�Ѿ��������еıߣ�������С��K��ֱ���˳� 
        
        mst+=minadd;        //mst��ֵ���ϲ�ֵ
        //��ͼ��ȥ�����滻�ı� 
        x=maxlen[change];
        fatherx=father[x];
        g[x][fatherx]=g[fatherx][x]=INF;
        //�޸�����������Ϣ������xֱ��ָ��Դ��ROOT 
        father[x]=fatherx=ROOT;         
        g[x][ROOT]=g[ROOT][x]=g[change][ROOT];
        g[ROOT][change]=g[change][ROOT]=INF;
    }
}

int main()
{
    int m,i,u,v,w;
    freopen("poj1639.txt","r",stdin);
    freopen("poj1639ans.txt","w",stdout);
    memset(g,INF,sizeof(g));
    string str;
    n=1;
    ROOT=0;         //��԰�����Ƶ㣬���Ϊ0 
    mp.clear();
    mp["Park"]=ROOT;
    
    
    scanf("%d",&m);    
    for(i=0;i<m;i++)
    {
        cin >> str;
        if (mp.find(str)==mp.end()) mp[str]=n++;
        u=mp[str];
        
        cin >> str;
        if (mp.find(str)==mp.end()) mp[str]=n++;
        v=mp[str];
        
        scanf("%d",&w);
        if (w<g[u][v]) g[u][v]=g[v][u]=w;
    }
    scanf("%d",&k);
    solve();
    
    printf("Total miles driven: %d",mst);
    return 0;
}
