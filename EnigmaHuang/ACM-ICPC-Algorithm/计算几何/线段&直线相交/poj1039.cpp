#include<cstdio>
#include<cmath>

using namespace std;

#define eps 1e-8
#define INF 1e20
#define MaxN 25
#define max(a,b) (a)>(b)?(a):(b)

struct Point
{
    double x,y;
    Point(double a=0,double b=0){x=a;y=b;} 
};

struct Line //ax+by+c=0 
{
    double a,b,c;
    Line(Point &p1,Point &p2)
    {
        a=p1.y-p2.y;
        b=p2.x-p1.x;
        c=p1.x*p2.y-p2.x*p1.y;
    }
    Line(){}
};

/*
�õ�sp-op��ep-op�Ĳ��
>0ʱep��opsp����ʱ�뷽��<0ʱ˳ʱ�룬=0ʱ���� 
*/ 
double Cross(Point sp,Point ep,Point op) 
{
    return (sp.x-op.x)*(ep.y-op.y)-(ep.x-op.x)*(sp.y-op.y);
}

Point a[MaxN],b[MaxN];
double ans;
int n;

int Check(Point &p1,Point &p2,int x)
{
    int i,flag;
    for (i=1;i<n;i++)
    {
            //������ߴ������£��������ϲ�ĵ���p1��ɵ�������Ӧ���ڹ��ߵ���ʱ�뷽��
        if (Cross(p2,a[i],p1)<-eps || Cross(p2,a[i+1],p1)<-eps)
        {
                   flag=1;
                   break;
        }
        //������ߴ������£��������²�ĵ���p1��ɵ�������Ӧ���ڹ��ߵ�˳ʱ�뷽�� 
        if (Cross(p2,b[i],p1)>eps  || Cross(p2,b[i+1],p1)>eps)
        {
                   flag=2;
                   break;
        }
    }
    if (i==n) return 1;  //û�к��κιܵ��ཻ
    if (i<x) return 0;   //���߲��Ϸ�
    Line l1(p1,p2),l2;
    if (flag==1) l2=Line(a[i],a[i+1]);
    else l2=Line(b[i],b[i+1]);
    ans=max(ans,((l1.b*l2.c-l2.b*l1.c)/(l1.a*l2.b-l2.a*l1.b)));
    return 0;
} 

int main()
{
    int i,j,flag;
    freopen("poj1039.txt","r",stdin);
    freopen("poj1039ans.txt","w",stdout);
    while (scanf("%d",&n) && n)
    {
        for (i=1;i<=n;i++)
        {
                   scanf("%lf%lf",&a[i].x,&a[i].y);
                   b[i].x=a[i].x;
                   b[i].y=a[i].y-1;
        }
        ans=-INF;
        if (n<3) flag=1;
        for (i=1;i<=n;i++)
        {
            for (j=i+1;j<=n;j++)
            {
                       flag=Check(a[i],b[j],j);
                       if (flag) break;
                       flag=Check(b[i],a[j],j);
                       if (flag) break;
            }
            if (flag) break;
        }
        if (flag) printf("Through all the pipe.\n");
        else printf("%.2f\n",ans);
    }
    return 0;
} 
