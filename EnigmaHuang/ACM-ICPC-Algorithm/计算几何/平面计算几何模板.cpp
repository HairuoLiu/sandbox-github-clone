#include<stdio.h>
#include<math.h>
#include<string.h>

#define eps 1e-8
#define pi  3.141592653589793

using namespace std;

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

//�����ļӼ�������
Vector operator + (Point a,Point b)
{
    return Vector(a.x+b.x,a.y+b.y);
}

Vector operator - (Point a,Point b)
{
    return Vector(a.x-b.x,a.y-b.y);
}

Vector operator * (Point a,double k)
{
    return Vector(a.x*k,a.y*k);
}

Vector operator / (Point a,double k)
{
    return Vector(a.x/k,a.y/k);
}

//��������ģ�����ȣ�
double len(Vector a)
{
    return sqrt(a.x*a.x+a.y*a.y);
}

//�õ�sp-op��ep-op�Ĳ��
//>0ʱep��opsp����ʱ�뷽��<0ʱ˳ʱ�룬=0ʱ����
double Cross(Point &sp, Point &ep, Point &op)
{
    return (sp.x-op.x)*(ep.y-op.y)-(ep.x-op.x)*(sp.y-op.y);
}

//�������������������������Ҫ����2
double Cross(Vector a,Vector b)
{
    return a.x*b.y-b.x*a.y;
}

//����������
double Dot(Vector a,Vector b)
{
    return a.x*b.x+a.y*b.y;
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

//����eps�ľ����жϴ�/С����
int epssgn(double x)
{
    if (fabs(x)<eps) return 0;
    else return x<0?-1:1;
}

//������֮���ֱ�߾���
double dis(Point a,Point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

//�ж���ֱ���Ƿ�ƽ��
int Parallel(Line l1,Line l2)
{
    return (fabs(l1.a*l2.b-l2.a*l1.b)<eps);
}

//�ж���ֱ���Ƿ����
int LineEqual(Line l1,Line l2)
{
    if (!Parallel(l1,l2)) return 0;
    else return (fabs(l1.a*l2.c-l2.a*l1.c)<eps && fabs(l1.b*l2.c-l2.b*l1.c)<eps);
}

//���C���߶�AB�ľ��� 
double PointToSegDist(Point A,Point B,Point C)
{
    if (dis(A,B)<eps) return dis(B,C);
    if (epssgn(Dot(B-A,C-A))<0) return dis(A,C);
    if (epssgn(Dot(A-B,C-B))<0) return dis(B,C);
    return fabs(Cross(B-A,C-A))/dis(B,A);
}

//���߶�����AB����һ�߶�CD�ľ���
double TwoSegMinDist(Point A,Point B,Point C,Point D)
{
    return min(min(PointToSegDist(A,B,C),PointToSegDist(A,B,D)),
               min(PointToSegDist(C,D,A),PointToSegDist(C,D,B)));
}

Point SymPoint(Point p,Line l) //���άƽ���ϵ�p����ֱ��p1p2�ĶԳƵ�
{
    Point result;
    double a=l.p2.x-l.p1.x;
    double b=l.p2.y-l.p1.y;
    double t=((p.x-l.p1.x)*a+(p.y-l.p1.y)*b)/(a*a+b*b);
    result.x=2*l.p1.x+2*a*t-p.x;
    result.y=2*l.p1.y+2*b*t-p.y;
    return result;
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

//֪��ֱ��������p1p2���ж�ֱ�����߶�se�Ƿ��ཻ��������
int IsLineIntersectSegment(Point p1,Point p2,Point s,Point e)
{
    if (Cross(p1,p2,s)*Cross(p1,p2,e)>eps) return 0;
    else return 1;
}

int IsLineIntersectSegment(Line l1,Point s,Point e)
{
    if (Cross(l1.p1,l1.p2,s)*Cross(l1.p1,l1.p2,e)>eps) return 0;
    else return 1;
}

//������ֱ��l1��l2�Ľ���
Point GetIntersect(Line l1, Line l2) 
{
    Point res;
    res.x=(l1.b*l2.c-l2.b*l1.c)/(l1.a*l2.b-l2.a*l1.b);
    res.y=(l1.c*l2.a-l2.c*l1.a)/(l1.a*l2.b-l2.a*l1.b);
    return res;
}

//���������ȷֲ��Ķ���ε�����
Point BaryCenter(Point *p,int n)
{
    Point res(0,0);
    double s=0.0,t;
    int i;
    for (i=1;i<n-1;i++)
    {
        t=Cross(p[i]-p[0],p[i+1]-p[0])/2;   //�ָ�������Σ������
        s+=t;
        res.x+=(p[0].x+p[i].x+p[i+1].x)*t;  //�������Ϊ�������������ε�������
        res.y+=(p[0].y+p[i].y+p[i+1].y)*t;  //����*���꣬��������������ĳ���3���ں���
    }
    res.x/=(3*s);
    res.y/=(3*s);
    return res;
}

//�����������Ҫ��㼯����ʱ��˳��
double ConvexPolygonArea(Point *p,int n)
{
    int i;
    double area=0;
    for (i=1;i<n-1;i++) area+=Cross(p[i]-p[0],p[i+1]-p[0]);
    return area/2;
}

//����ԭ��ΪԲ�ģ���a��b���뾶Ϊr���������
double SectorArea(Point a,Point b,double r)
{
    double theta=atan2(a.y,a.x)-atan2(b.y,b.x);
    while (theta<=0) theta+=2*pi;
    while (theta>=2*pi) theta-=2*pi;
    theta=min(theta,2*pi-theta);
    return r*r*theta/2;
}

//����oΪԲ��rΪ�뾶��Բ���߶Σ�ֱ�ߣ�ab�Ľ���
//���ص�ret�ǽ��㣬num�ǽ�������
//���ж�t��Χ������ifȥ�����Լ���Բ��ֱ�ߵĽ���
void CircleCrossLine(Point a,Point b,Point o,double r,Point ret[],int &num)
{
    double x0=o.x,y0=o.y;
    double x1=a.x,y1=a.y;
    double x2=b.x,y2=b.y;
    double dx=x2-x1,dy=y2-y1;
    double A=dx*dx+dy*dy;
    double B=2*dx*(x1-x0)+2*dy*(y1-y0);
    double C=(x1-x0)*(x1-x0)+(y1-y0)*(y1-y0)-r*r;
    double delta=B*B-4*A*C;
    num=0;
    if (epssgn(delta)>=0)
    {
        double t1=(-B-sqrt(fabs(delta)))/(2*A);
        double t2=(-B+sqrt(fabs(delta)))/(2*A);
        if (epssgn(t1-1.0)<=0 && epssgn(t1)>=0)
            ret[num++]=Point(x1+t1*dx,y1+t1*dy);
        if (epssgn(t2-1.0)<=0 && epssgn(t2)>=0)
            ret[num++]=Point(x1+t2*dx,y1+t2*dy);
    }
}

//����ԭ��ΪԲ�İ뾶Ϊr��԰����ԭ�㡢a��b��ɵ������ε��ص����
double Calc(Point a,Point b,double r)
{
    Point p[2];
    int num=0;
    int ina=(epssgn(len(a)-r)<0);
    int inb=(epssgn(len(b)-r)<0);
    if (ina)
    {
        if (inb) return fabs(Cross(a,b))/2.0; //����1����������ȫ��Բ�ڣ�ֱ�������������
        else  //����2��һ������Բ�ڣ�һ������Բ�⣺�ָ��һ����ȫ��Բ�ڵ������κ�һ������
        {
            CircleCrossLine(a,b,Point(0,0),r,p,num);
            return SectorArea(b,p[0],r)+fabs(Cross(a,p[0]))/2.0;
        }
    }
    else
    {
        CircleCrossLine(a,b,Point(0,0),r,p,num);
        //����2��һ������Բ�ڣ�һ������Բ�⣺�ָ��һ����ȫ��Բ�ڵ������κ�һ������
        if (inb) return SectorArea(p[0],a,r)+fabs(Cross(p[0],b))/2.0;
        else
        {
            //����4�������㶼��Բ�⣬���������������Բ���������㣺�ָ��һ����ȫ��Բ�ڵ������κ���������
            if (num==2) return SectorArea(a,p[0],r)+SectorArea(p[1],b,r)+fabs(Cross(p[0],p[1]))/2.0;
            //����3�������㶼��Բ�⣬�����ཻ��Ϊһ�����Σ�ֱ�����������
            else return SectorArea(a,b,r);
        }
    }
}

//���������ȷֲ��������ε�����
Point TriangleMassCenter(Point a,Point b,Point c)
{
    return (a+b+c)/3.0;
}

//�������ε�����
Point TriangleCircumCenter(Point a,Point b,Point c)
{
    Point res;
    double a1=atan2(b.y-a.y,b.x-a.x)+pi/2;
    double a2=atan2(c.y-b.y,c.x-b.x)+pi/2;
    double ax=(a.x+b.x)/2;
    double ay=(a.y+b.y)/2;
    double bx=(c.x+b.x)/2;
    double by=(c.y+b.y)/2;
    double r1=(sin(a2)*(ax-bx)+cos(a2)*(by-ay))/(sin(a1)*cos(a2)-sin(a2)*cos(a1));
    return Point(ax+r1*cos(a1),ay+r1*sin(a1));
}

//�������εĴ���
Point TriangleOrthoCenter(Point a,Point b,Point c)
{
    return TriangleMassCenter(a,b,c)*3.0-TriangleCircumCenter(a,b,c)*2.0;
}

//�������ε�����
Point TriangleInnerCenter(Point a,Point b,Point c)
{
    Point res;
    double la=len(b-c);
    double lb=len(a-c);
    double lc=len(a-b);
    res.x=(la*a.x+lb*b.x+lc*c.x)/(la+lb+lc);
    res.y=(la*a.y+lb*b.y+lc*c.y)/(la+lb+lc);
}

/*------Graham��͹��----*/
int cmp(Point &a,Point &b)
{
    if (a.y==b.y) return (a.x<b.x);
    return (a.y<b.y);
}

//�����еĵ����һ������
void QSort(Point p[],int l,int r)
{
    int i=l,j=r;
    Point mid=p[(l+r)/2],swap;
    while (i<=j)
    {
        while (cmp(p[i],mid)) i++;
        while (cmp(mid,p[j])) j--;
        if (i<=j)
        {
            swap=p[i];
            p[i]=p[j];
            p[j]=swap;
            i++;j--;
        }
    }
    if (i<r) QSort(p,i,r);
    if (l<j) QSort(p,l,j);
}

//nΪԭͼ�ĵ�����p[]Ϊԭͼ�ĵ㣨0~n-1����topΪ͹�����������0~top-1����res[]Ϊ͹������±꣬��
int Graham(Point p[],int n,int res[])
{
    int i,len,top;
    top=1;
    QSort(p,0,n-1);
    for (i=0;i<3;i++) res[i]=i;
    for (i=2;i<n;i++)
    {
        while (top && epssgn(Cross(p[i],p[res[top]],p[res[top-1]]))>=0) top--;
        res[++top]=i;
    }
    len=top;
    res[++top]=n-2;
    for (i=n-3;i>=0;i--)
    {
        while (top!=len && epssgn(Cross(p[i], p[res[top]], p[res[top-1]]))>=0) top--;
        res[++top]=i;
    }
    return top;
}

//�жϵ�x�Ƿ���͹��p[res[1~chnum]]�У�����1��Ϊ���ڲ���߽���
int PointInConvexHull(Point p[],int res[],int chnum,Point x)
{
    //��һ��͹���ڵĵ�
    Point g=(p[res[0]]+p[res[chnum/3]]+p[res[2*chnum/3]])/3.0;
    int l=0,r=chnum,mid;
    //����͹��
    while (l+1<r)
    {
        mid=(l+r)/2;
        if (epssgn(Cross(p[res[l]]-g,p[res[mid]]-g))>0)
        {
            if (epssgn(Cross(p[res[l]]-g,x-g))>=0
             && epssgn(Cross(p[res[mid]]-g,x-g))<0) r=mid;
            else l=mid;
        }
        else
        {
            if (epssgn(Cross(p[res[l]]-g,x-g))<0
             && epssgn(Cross(p[res[mid]]-g,x-g))>=0) l=mid;
            else r=mid;
        }
    }
    r%=chnum;
    if (epssgn(Cross(p[res[r]]-x,p[res[l]]-x))==-1) return 1; else return 0;
}

//��ת������͹��p[res[1~chnum]]��ֱ�������������appnum���洢��app[][2]�� 
double Diameter(Point p[],int res[],int chnum,int app[][2],int &appnum) //AntiPodal Point
{
    int i,j;
    double ret=0,nowlen;
    res[chnum]=res[0];
    j=1;
    appnum=0;
    for (i=0;i<chnum;i++)
    {
        while (Cross(p[res[i]]-p[res[i+1]],p[res[j+1]]-p[res[i+1]])
              <Cross(p[res[i]]-p[res[i+1]],p[res[j]]-p[res[i+1]])) 
        {
            j++;
            j%=chnum;
        }
        app[appnum][0]=res[i];
        app[appnum][1]=res[j];
        appnum++;
        nowlen=dis(p[res[i]],p[res[j]]);
        if (nowlen>ret) ret=nowlen;
        nowlen=dis(p[res[i+1]],p[res[j+1]]);
        if (nowlen>ret) ret=nowlen;
    }
    return ret;
}

//��ת������͹��p[res[1~chnum]]��������������
double ConvexHullMaxTriangleArea(Point p[],int res[],int chnum) 
{
    int i,j,k;
    double area=0,tmp;
    k=2;j=1;
    res[chnum]=res[0];
    for (i=0;i<chnum;i++)
    {
        //��סi,j������ǰ��תk�����������Ļ���һֱתһ��ȥ 
        while (fabs(Cross(p[res[j]]-p[res[i]],p[res[(k+1)%chnum]]-p[res[i]]))
              >fabs(Cross(p[res[j]]-p[res[i]],p[res[k]]          -p[res[i]])))
              k=(k+1)%chnum;
        tmp=fabs(Cross(p[res[j]]-p[res[i]],p[res[k]]-p[res[i]]));
        if (tmp>area) area=tmp;
        //��סi,k������ǰ��תj�����������Ļ���һֱתһ��ȥ 
        while (fabs(Cross(p[res[(j+1)%chnum]]-p[res[i]],p[res[k]]-p[res[i]]))
              >fabs(Cross(p[res[j]]-          p[res[i]],p[res[k]]-p[res[i]])))
              j=(j+1)%chnum;
        tmp=fabs(Cross(p[res[j]]-p[res[i]],p[res[k]]-p[res[i]]));
        if (tmp>area) area=tmp;
                //j,kת�����λ�ã���ǰתi(i++)
    }
    return area/2;
}

//����͹��p��q�����С���룬ע����õ�ʱ��Ҫ��������λ�õ�������
//��סp��p����������תq�����ܵõ�����С���� 
double TwoConvexHullMinDist(Point P[],Point Q[],int n,int m)
{
    int YMinP=0,YMaxQ=0,i;
    double tmp,ans=999999999;
    for (i=0;i<n;i++) if (P[i].y<P[YMinP].y) YMinP=i;
    for (i=0;i<m;i++) if (Q[i].y>Q[YMaxQ].y) YMaxQ=i;
    P[n]=P[0];
    Q[m]=Q[0];
    for (i=0;i<n;i++)
    {
        //ע�⣬tmp�������>�ȽϵĽ�� 
        while (tmp=Cross(Q[YMaxQ+1]-P[YMinP+1],P[YMinP]-P[YMinP+1])
                  >Cross(Q[YMaxQ]  -P[YMinP+1],P[YMinP]-P[YMinP+1]))
              YMaxQ=(YMaxQ+1)%m;
        if (tmp<0) ans=min(ans,PointToSegDist(P[YMinP],P[YMinP+1],Q[YMaxQ]));
        else       ans=min(ans,TwoSegMinDist (P[YMinP],P[YMinP+1],Q[YMaxQ],Q[YMaxQ+1]));
        YMinP=(YMinP+1)%n;
    }
    return ans;
}
/*------Graham��͹��----*/

/*-----��ƽ�潻O(nlogn)ģ��-----*/
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

//��n����ƽ��l�İ�ƽ�潻���õ��Ľ��㴢����p�У�������Ŀ���ص�pn
//���Խ�һ�������ÿһ���߿��ɰ�ƽ�棬������Ľ����Ƕ���εĺˣ�Ҫ��pn>=3
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
/*-----��ƽ�潻O(nlogn)ģ��-----*/

/*-----��ƽ�潻O(n^2)ģ��-----*/
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
/*-----��ƽ�潻O(n^2)ģ��-----*/
