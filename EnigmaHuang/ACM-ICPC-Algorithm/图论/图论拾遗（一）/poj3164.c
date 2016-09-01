#include<stdio.h>
#include<math.h>
#include<string.h>

#define min(a,b) (a)<(b)?(a):(b)
#define INF  1000000000
#define MaxN 110

double map[MaxN][MaxN];
int visit[MaxN];
int circle[MaxN]; //circle[x]=1��ʾx�㱻ɾ����
int pre[MaxN];    //pre[x]��ʾx�����С���
int n,m,ROOT;

struct TPoint
{
    double x,y;
}p[MaxN];

double dist(int i,int j)
{
    return sqrt((p[i].x-p[j].x)*(p[i].x-p[j].x)+(p[i].y-p[j].y)*(p[i].y-p[j].y));
}

void dfs(int u)
{
    int i;
    if (visit[u]) return;
    visit[u]=1;
    for (i=1;i<=n;i++) if (map[u][i]<INF) dfs(i);
}

int connect()//���ѣ��ж��Ƿ������С����ͼ
{
    int i;
    dfs(ROOT);
    for (i=1;i<=n;i++) if (!visit[i]) return 0;
    return 1;
}

double solve()
{
    double ans=0;
    int i,j,k;
    memset(circle,0,sizeof(circle));
    while (1)
    {
        for (i=1;i<=n;i++)      //���ÿ�������С���
        {
            if (circle[i] || i==ROOT) continue;
            map[i][i]=INF;
            pre[i]=i;
            for(j=1;j<=n;j++)
            {
                if (circle[j]) continue;
                if (map[j][i]<map[pre[i]][i]) pre[i]=j;
            }
        }
        for (i=1;i<=n;i++)      //�����һ�
        {
            if (circle[i] || i==ROOT) continue;
            j=i;
            memset(visit,0,sizeof(visit));
            while (!visit[j] && j!=1)
            {
                visit[j]=1;
                j=pre[j];
            }
            if (j==ROOT) continue; //j==ROOT˵��i���ڻ���
            i=j;                   //�ҵ��˻�
            ans+=map[pre[i]][i];
            for (j=pre[i];j!=i;j=pre[j])
            {
                ans+=map[pre[j]][j];
                circle[j]=1;    //�û���һ��i����˻���������ɾȥ����circle[j]=1
            }
            for(j=1;j<=n;j++)
            {
                if (circle[j]) continue;
                if (map[j][i]<INF) map[j][i]-=map[pre[i]][i]; //����j�����
            }
            for (j=pre[i];j!=i;j=pre[j])//�������е�����ű�Ϊ�˹�����ı�
            {
                for (k=1;k<=n;k++)      //���¹��ߣ����±�Ȩ
                {
                    if (circle[k]) continue;
                    if (map[j][k]<INF) map[i][k]=min(map[i][k],map[j][k]);
                    if (map[k][j]<INF) map[k][i]=min(map[k][i],map[k][j]-map[pre[j]][j]);
                }
            }
            break;  //��һ�����Ժ���Ϊ���¹��˱�����Ҫ�����һ�
        }
        if (i>n)    //û�л��ˣ�ֱ�Ӽ���𰸲�����
        {
            for (j=1;j<=n;j++)
            {
                if (circle[j] || j==ROOT) continue;
                ans+=map[pre[j]][j];
            }
            break;
        }
    }
    return ans;
}

int main()
{
    int i,j,a,b;
    freopen("poj3164.txt","r",stdin);
    freopen("poj3164ans.txt","w",stdout);
    while (scanf("%d%d",&n,&m)!=EOF)
    {
        for (i=1;i<=n;i++) scanf("%lf%lf",&p[i].x,&p[i].y);
        for (i=1;i<=n;i++)
            for (j=1;j<=n;j++) map[i][j]=INF;
        for (i=1;i<=m;i++)
        {
            scanf("%d%d",&a,&b);
            map[a][b]=dist(a,b);
        }
        ROOT=1;
        memset(visit,0,sizeof(visit));
        if (!connect()) printf("poor snoopy\n");
        else printf("%.2f\n",solve());  //GCC/C++���ﲻ����%.2lf
    }
    return 0;
}
