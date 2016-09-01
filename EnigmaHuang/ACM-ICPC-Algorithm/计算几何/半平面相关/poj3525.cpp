#include <cstdio>
#include <cmath>

using namespace std;

#define eps  1e-8
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

//�����������Ҫ��㼯����ʱ��˳��
double ConvexPolygonArea(Point p[],int n)
{
    int i;
    double area=0;
    for (i=1;i<n-1;i++) area+=Cross(p[i]-p[0],p[i+1]-p[0]);
    return area/2;
}

/*-----��ƽ�潻ģ��-----*/
int cmp(const Line & l1,const Line & l2)
{
    int d=epssgn(l1.angle-l2.angle);
    if (!d) return (epssgn(Cross(l2.p1-l1.p1,l2.p2-l1.p1))>0); //������ͬʱ����������ƽ������ķ���ǰ��
    return d<0;
}

void QSort(Line L[],int l,int r)
{
    int i=l,j=r;
    Line swap,mid=L[(l+r)/2];
    while (i<=j)
    {
        while (cmp(L[i],mid)) i++;
        while (cmp(mid,L[j])) j--;
        if (i<=j)
        {
            swap=L[i];
            L[i]=L[j];
            L[j]=swap;
            i++;j--;
        }
    }
    if (i<r) QSort(L,i,r);
    if (l<j) QSort(L,l,j);
}

//�ж�l1��l2�Ľ����Ƿ��ڰ�ƽ��hpl��
int IntersectionOutOfHalfPlane(Line &hpl,Line &l1,Line &l2)
{
     Point p=GetIntersect(l1,l2);
     return (epssgn(Cross(hpl.p1-p,hpl.p2-p))<0);
}

//��n����ƽ��l�İ�ƽ�潻���õ��Ľ��㴢����p�У�������Ŀ���ص�pn
void HalfPlaneIntersect(Line l[],int n,Point p[],int &pn)
{
    int i,j;
    int dq[MaxN],top,bot;
    //���������������а�ƽ��A*x+B*y+C>0��<,<=,>=��,
    //Ҳ�������а�ƽ��ķ��ž���ͬ������¶Լ��ǽ�������
    QSort(l,0,n-1);
    //������ͬʱ��ֻ��������������
    for (i=j=0;i<n;i++) if (epssgn(l[i].angle-l[j].angle)>0) l[++j]=l[i];
    n=j+1;
    dq[0]=0; //˫�˶���
    dq[1]=1;
    top=1;   //�����͵ײ�
    bot=0;
    for (i=2;i<n;i++)
    {
        //��ջ��������ֱ�߽����ڵ�ǰ��ƽ���ⲿʱ����ջ
        while (top>bot && IntersectionOutOfHalfPlane(l[i],l[dq[top]],l[dq[top-1]])) top--;
        //���������һ��͹����Σ����Ե���ƽ��ת���ӽ�һȦʱ��ĳ����ƽ��������һ��while��������
        //���ֻ�Ӱ�쵽�ײ�������ֱ�ߣ����ײ�������ֱ�ߵĽ��㣬�ڵ�ǰ�İ�ƽ���ⲿʱ���ײ���ջ
        while (top>bot && IntersectionOutOfHalfPlane(l[i],l[dq[bot]],l[dq[bot+1]])) bot++;
        dq[++top]=i; //��ǰ��ƽ����ջ
    }
    //�����������ֱ�ߵĽ��㲻����ײ��İ�ƽ����ʱ���������Ǹ���ƽ���Ƕ���ģ�������ջ
    while (top>bot && IntersectionOutOfHalfPlane(l[dq[bot]],l[dq[top]],l[dq[top-1]])) top--;
    //����ײ�������ֱ�ߵĽ��㲻������İ�ƽ����ʱ���ײ����Ǹ���ƽ���Ƕ���ģ��ײ���ջ
    while (top>bot && IntersectionOutOfHalfPlane(l[dq[top]],l[dq[bot]],l[dq[bot+1]])) bot++;
    dq[++top]=dq[bot]; //����ײ��İ�ƽ��ŵ�����������������󶥵�
    for (pn=0,i=bot;i<top;i++,pn++) p[pn]=GetIntersect(l[dq[i+1]],l[dq[i]]);
}
/*-----��ƽ�潻ģ��-----*/

Line l[MaxN],l2[MaxN];
Point p[MaxN];
int n,pn;

//��������ģ�����ȣ�
double len(Vector a)
{
    return sqrt(a.x*a.x+a.y*a.y);
}

//��ƽ��hpl�����ƽ�dis����
Line HalfPlaneMoveIn(Line &hpl,double &dis)
{
    double dx=hpl.p1.x-hpl.p2.x;
    double dy=hpl.p1.y-hpl.p2.y;
    double ll=len(hpl.p1-hpl.p2);
    Point pa=Point(dis*dy/ll+hpl.p1.x,hpl.p1.y-dis*dx/ll);
    Point pb=Point(dis*dy/ll+hpl.p2.x,hpl.p2.y-dis*dx/ll);
    return Line(pa,pb);
}

int Check(double r)
{
    int i;
    for (i=0;i<n;i++) l2[i]=HalfPlaneMoveIn(l[i],r);
    HalfPlaneIntersect(l2,n,p,pn);
    if (pn>=3) return 1; else return 0;
}

int main()
{
    int i;
    double left,right,mid;
    freopen("poj3525.txt","r",stdin);
    freopen("poj3525ans.txt","w",stdout);
    while (scanf("%d",&n) && n)
    {
        for (i=0;i<n;i++) scanf("%lf%lf",&p[i].x,&p[i].y);
        for (i=0;i<n;i++) l[i]=Line(p[i],p[(i+1)%n]);
        left=0;
        right=10000;
        while (epssgn(right-left)>0)
        {
            mid=(left+right)/2;
            if (Check(mid)) left=mid; else right=mid;
        }
        printf("%.6f\n",mid);
    }
    return 0;
}
