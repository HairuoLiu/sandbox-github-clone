#include<stdio.h>
#include<math.h>

#define MaxN 101

struct Point
{
    double x,y;
    Point(double a=0,double b=0){x=a;y=b;}
};

typedef Point Vector;

Vector operator - (Point a,Point b)
{
    return Vector(a.x-b.x,a.y-b.y);
}

/* 2����������ͬʱҲ��������� */
double Cross(Vector a,Vector b)
{
    return a.x*b.y-b.x*a.y;
}

int gcd(int a,int b)
{
    return b>0?gcd(b,a%b):a;
}

int iabs(int x)
{
    if (x>0) return x; else return -x;
}

Point p[MaxN];

int main()
{
    int n,i,k,t,e,dx,dy;
    double s;
    freopen("poj1265.txt","r",stdin);
    freopen("poj1265ans.txt","w",stdout);
    scanf("%d",&t);
    for (k=1;k<=t;k++)
    {
        scanf("%d",&n);
        p[0]=Point(0,0);
        e=0;s=0;
        for (i=1;i<=n;i++)
        {
            scanf("%d%d",&dx,&dy);
            p[i].x=p[i-1].x+dx;
            p[i].y=p[i-1].y+dy;
            s+=Cross(p[i-1],p[i]); //ע��ǰ��˳�򣬻�Ӱ�����
            if (dx==0 || dy==0) e+=iabs(dx+dy);
            else e+=gcd(iabs(dx),iabs(dy));  //����ͼ��֪�����Լ���������ϵ�����
        }
        s=fabs(s)/2;  //���ע��Ҫ��2����Ϊ���ֱ�ӵõ�����ƽ���ı������
        i=(int)(s+1-e/2);
        printf("Scenario #%d:\n",k);
        printf("%d %d %.1f\n\n",i,e,s);
    }
    return 0;
}
