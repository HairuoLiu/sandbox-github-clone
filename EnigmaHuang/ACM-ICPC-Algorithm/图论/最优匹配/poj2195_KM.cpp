#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MaxN 110
#define INF 0x3f3f3f3f

using namespace std;

/*---------------KM Template Start---------------*/

int numx,numy;              //x�㼯y�㼯�ĸ��� 
int lx[MaxN],ly[MaxN];      //lx,lyΪ����
int link[MaxN],slack[MaxN]; //link��ʾY��ĳһ������X����һ��ָ��� 
int visx[MaxN],visy[MaxN];  //����������������Щ�㱻���� 
int w[MaxN][MaxN];          //��Ȩ�� 

int DFS(int x)
{
    int y,t; 
    visx[x]=1;
    for (y=1;y<=numy;y++)
    {
        if (visy[y]) continue;
        t=lx[x]+ly[y]-w[x][y];
        if (t==0)   
        {
            visy[y]=1;
            if (link[y]==-1 || DFS(link[y]))
            {
                link[y]=x;
                return 1;
            }
        }
        else if (slack[y]>t) slack[y]=t; //���������ͼ��slackȡ��С��
    }
    return 0;
}

int KM()
{
    int i,j,x,d,res;
    for (i=1;i<=numx;i++)            //lx��ʼ��Ϊ����������������
    {
    	lx[i]=-INF;
    	for (j=1;j<=numy;j++) if (w[i][j]>lx[i]) lx[i]=w[i][j];
    }  
    for (x=1;x<=numx;x++)
    {
        memset(slack,INF,sizeof(slack));
        while (1)
        {
            memset(visx,0,sizeof(visx));
            memset(visy,0,sizeof(visy));
            if (DFS(x)) break; //�������ɹ����õ�������ɣ�������һ���������   
	    //�������ʧ�ܣ���ı�һЩ��ı�ţ�ʹ��ͼ�п��бߵ���������
            //����Ϊ����������������б�������X����ı��ȫ����ȥһ������d
            //������������е�Y����ı��ȫ������һ������d
            d=INF;
            for (i=1;i<=numy;i++) if (!visy[i]&&d>slack[i]) d=slack[i];
            //�޸Ķ����Ҫ�����в��ڽ������е�Y�����slackֵ����ȥd
            for (i=1;i<=numx;i++) if (visx[i]) lx[i]-=d;
            for (i=1;i<=numy;i++) if (visy[i]) ly[i]+=d;
            else slack[i]-=d;
        }
    }
    res=0;
    for (i=1;i<=numy;i++) if (link[i]>-1) res+=w[link[i]][i];
    return res;
}

void InitKM(int nx,int ny)
{
    numx=nx;
    numy=ny;
    memset(link,-1,sizeof(link));
    memset(ly,0,sizeof(ly));     
    memset(w,0,sizeof(w)); 
}

/*---------------KM Template Over---------------*/

struct TPos
{
    int x,y;
}house[MaxN],man[MaxN];

int n,m,numh,numm;

void ReadData()
{
    int i,j,dis;
    char c;
    numh=numm=0;
    for (i=1;i<=n;i++)
    {
        for (j=1;j<=m;j++)
        {
            scanf("%c",&c);
            if ('H'==c)
            {
                numh++;
                house[numh].x=i;
                house[numh].y=j;
            }
            else if ('m'==c)
            {
                numm++;
                man[numm].x=i;
                man[numm].y=j;
            }
        }
        scanf("\n");
    }
    InitKM(numm,numh);
    for (i=1;i<=numm;i++)
    {
        for (j=1;j<=numh;j++)
        {
            dis=abs(man[i].x-house[j].x)+abs(man[i].y-house[j].y);
            w[i][j]=-dis;
        }
    }
}

int main()
{
    freopen("poj2195.txt","r",stdin);
    freopen("poj2195ans.txt","w",stdout);
    while(scanf("%d%d\n",&n,&m)!=EOF)
    {
        if (0==n && 0==m) break;
        ReadData();
        printf("%d\n",-KM());
    }
    return 0;
} 
