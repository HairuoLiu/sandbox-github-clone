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

Line l[MaxN];
Point p[MaxN];
int n,pn;

int main()
{
    int i,t=0;
    double x1,y1,x2,y2;
    freopen("poj1474.txt","r",stdin);
    freopen("poj1474ans.txt","w",stdout);
    while (scanf("%d",&n) && n)
    {
        for (i=0;i<n;i++) scanf("%lf%lf",&p[i].x,&p[i].y); //ע����������˳ʱ�뷽��
        for (i=0;i<n;i++) l[i]=Line(p[(i+1)%n],p[i]);      //������Ҫ������ʱ�뷽���
        HalfPlaneIntersect(l,n,p,pn);
        t++;
        printf("Floor #%d\n",t);
        if (pn>2) printf("Surveillance is possible.\n\n");
        else printf("Surveillance is impossible.\n\n");    //��ƽ�潻����ڵ���3���к�
    }
    return 0;
}
