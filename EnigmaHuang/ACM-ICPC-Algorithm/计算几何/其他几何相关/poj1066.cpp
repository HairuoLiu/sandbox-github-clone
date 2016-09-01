#include<stdio.h>
#include<math.h>

#define eps  1e-8
#define MaxN 120
#define MaxM 60

//��ά����
struct Point
{
    double x,y;
    Point(double a=0,double b=0){x=a;y=b;}
};

typedef Point Vector;

//��ά�߶���
struct Segment
{
    Point s,e;
    Segment(Point a,Point b){s=a;e=b;}
    Segment(double x1,double y1,double x2,double y2)
    {
        s=Point(x1,y1);
        e=Point(x2,y2);
    }
    Segment(){}
};


//�õ�sp-op��ep-op�Ĳ��
//>0ʱep��opsp����ʱ�뷽��<0ʱ˳ʱ�룬=0ʱ����
double Cross(Point &sp, Point &ep, Point &op)
{
    return (sp.x-op.x)*(ep.y-op.y)-(ep.x-op.x)*(sp.y-op.y);
}

//�������Сֵ
double max(double a,double b)
{
    if (a<b) return b; else return a;
}

double min(double a,double b)
{
    if (a>b) return b; else return a;
}

bool operator == (const Point &a,const Point &b)
{
    return (a.x==b.x && a.y==b.y);
}

//�ж��߶�s1e1��s2e2�Ƿ��ཻ�����˵㣩
//�����˵�Ļ��������<=�ĳ�<
int IsSegmentIntersect(Point s1, Point e1, Point s2, Point e2)
{
    if( min(s1.x,e1.x)<= max(s2.x,e2.x) &&
        min(s1.y,e1.y)<= max(s2.y,e2.y) &&
        min(s2.x,e2.x)<= max(s1.x,e1.x) &&
        min(s2.y,e2.y)<= max(s1.y,e1.y) &&
        Cross(s2,e2,s1)*Cross(s2,e2,e1)<=0 &&
        Cross(s1,e1,s2)*Cross(s1,e1,e2)<=0)
    return 1;
    return 0;
}

Point p[MaxN];
Segment seg[MaxM];

int main()
{
    int i,j,n,num,ans,res;
    Point src;
    freopen("poj1066.txt","r",stdin);
    freopen("poj1066ans.txt","w",stdout);
    while (scanf("%d",&n)!=EOF)
    {
        num=0;
        for (i=0;i<n;i++)
        {
            scanf("%lf%lf%lf%lf",&seg[i].s.x,&seg[i].s.y,&seg[i].e.x,&seg[i].e.y);
            p[num++]=seg[i].s;
            p[num++]=seg[i].e;
        }
        scanf("%lf%lf",&src.x,&src.y);
        ans=99999999;
        for (i=0;i<num;i++)
        {
            res=0;
            for (j=0;j<n;j++)
            {
                if (p[i]==seg[j].s || p[i]==seg[j].e) continue;
                if (IsSegmentIntersect(src,p[i],seg[j].s,seg[j].e)) res++;
            }
            ans=min(res,ans);
        }
        ans++;
        if (n==0) printf("Number of doors = 1\n");
        else printf("Number of doors = %d\n",ans);
    }
    return 0;
}
