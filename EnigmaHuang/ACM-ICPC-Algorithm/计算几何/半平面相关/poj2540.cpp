#include <cstdio>
#include <cmath>

using namespace std;

#define eps  1e-16
#define MaxN 101

//��ά����
struct Point
{
    double x,y;
    Point(double a=0,double b=0){x=a;y=b;}
};

typedef Point Vector;

//��άֱ���࣬һ�㷽��ax+by+c=0
struct Line
{
    double a,b,c,angle;
    Point p1,p2;
    Line(Point s,Point e)
    {
        a=s.y-e.y;
        b=e.x-s.x;
        c=s.x*e.y-e.x*s.y;
        angle=atan2(e.y-s.y,e.x-s.x);
        p1=s;p2=e;
    }
    Line(double _a,double _b,double _c):a(_a),b(_b),c(_c)
    {
        p1.x=0;
        p1.y=(-c-a*p1.x)/b;
        p2.x=1;
        p1.y=(-c-a*p2.x)/b;
    }
    Line(){}
};

Vector operator - (Point a,Point b)
{
    return Vector(a.x-b.x,a.y-b.y);
}

//�������������������������Ҫ����2
double Cross(Vector a,Vector b)
{
    return a.x*b.y-b.x*a.y;
}

//����eps�ľ����жϴ�/С����
int epssgn(double x)
{
    if (fabs(x)<eps) return 0;
    else return x<0?-1:1;
}

//������ֱ��l1��l2�Ľ���
Point GetIntersect(Line l1, Line l2)
{
    Point res;
    res.x=(l1.b*l2.c-l2.b*l1.c)/(l1.a*l2.b-l2.a*l1.b);
    res.y=(l1.c*l2.a-l2.c*l1.a)/(l1.a*l2.b-l2.a*l1.b);
    return res;
}

/*-----��ƽ�潻ģ��-----*/
//p�������г����İ�ƽ��ĵ㣬pn�ǵ����������Ҫ��˳ʱ�������ʱ������
//�µİ�ƽ��ֱ��Ϊax+by+c=0
void HalfPlaneCut(Point p[],int &pn,double a,double b,double c)
{
    int cnt=0,i;
    Point tp[MaxN];  //temp_p
    //���ڽ������ĵ����µİ�ƽ���ڣ�����
    for (i=1;i<=pn;i++) if (epssgn(a*p[i].x+b*p[i].y+c)>=0) tp[++cnt]=p[i];
    else //���������ǰ��ĵ��ڰ�ƽ���ڣ������и�
    {
        if (epssgn(a*p[i-1].x+b*p[i-1].y+c)>0)
            tp[++cnt]=GetIntersect(Line(p[i-1],p[i]),Line(a,b,c));
        if (epssgn(a*p[i+1].x+b*p[i+1].y+c)>0)
            tp[++cnt]=GetIntersect(Line(p[i],p[i+1]),Line(a,b,c));
    }
    pn=cnt;
    for (i=1;i<=cnt;i++) p[i]=tp[i];
    p[0]=p[cnt];
    p[cnt+1]=p[1];
}
/*-----��ƽ�潻ģ��-----*/

Point p[MaxN];
int n,pn;

//�����������Ҫ��㼯����ʱ��˳��
double ConvexPolygonArea(Point *p,int n)
{
    int i;
    double area=0;
    for (i=1;i<n-1;i++) area+=Cross(p[i]-p[0],p[i+1]-p[0]);
    return area/2;
}

Line GetMidVertical(Point p1,Point p2)
{
    Point p3((p1.x+p2.x)/2,(p1.y+p2.y)/2);
    double a=p1.x-p2.x;
    double b=p1.y-p2.y;
    double c=-a*p3.x-b*p3.y;
    return Line(a,b,c);
}

int main()
{
    int i,flag=0;
    Point pre(0,0),now;
    char str[255];
    freopen("poj2540.txt","r",stdin);
    freopen("poj2540ans.txt","w",stdout);
    //������Χ�ռ�
    p[1]=Point(0,0);
    p[2]=Point(0,10);
    p[3]=Point(10,10);
    p[4]=Point(10,0);
    p[5]=p[1];
    p[0]=p[4];
    pn=4;
    while (scanf("%lf%lf%s",&now.x,&now.y,str)!=EOF)
    {
        Line l=GetMidVertical(pre,now);
        if (str[0]=='C')
        {
            //����һ�·���ȷ������Ŀ��������һ����ֱ�����
            if (epssgn(l.a*pre.x+l.b*pre.y+l.c)<0)
            {
                l.a=-l.a;
                l.b=-l.b;
                l.c=-l.c;
            }
        }
        else if (str[0]=='H')
        {
            //����һ�·���ȷ������Ŀ��������һ����ֱ�����
            if (epssgn(l.a*now.x+l.b*now.y+l.c)<0)
            {
                l.a=-l.a;
                l.b=-l.b;
                l.c=-l.c;
            }
        }
        else flag=1;
        if (flag)
        {
            printf("0.00\n");
            continue;
        }
        HalfPlaneCut(p,pn,l.a,l.b,l.c);
        printf("%.2f\n",fabs(ConvexPolygonArea(p,pn)));
        pre=now;
    }
    return 0;
}
