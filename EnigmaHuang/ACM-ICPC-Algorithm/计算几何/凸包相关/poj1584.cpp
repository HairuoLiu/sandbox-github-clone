#include<stdio.h>
#include<math.h>

#define eps 1e-8
#define MaxN 201

//��ά����
struct Point
{
    double x,y;
    Point(double a=0,double b=0){x=a;y=b;}
};

typedef Point Vector;

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

//���C���߶�AB�ľ���
double PointToSegDist(Point A,Point B,Point C)
{
    if (dis(A,B)<eps) return dis(B,C);
    if (epssgn(Dot(B-A,C-A))<0) return dis(A,C);
    if (epssgn(Dot(A-B,C-B))<0) return dis(B,C);
    return fabs(Cross(B-A,C-A))/dis(B,A);
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

Point p[MaxN];
int   res[MaxN];
int   chnum;

struct Circle
{
    Point center;
    double r;
}cir;

int main()
{
    int n,i,j,k,flag;
    double direct,tmp;
    freopen("poj1584.txt","r",stdin);
    freopen("poj1584ans.txt","w",stdout);
    while (scanf("%d",&n) && n>=3)
    {
        scanf("%lf%lf%lf",&cir.r,&cir.center.x,&cir.center.y);
        for (i=0;i<n;i++) scanf("%lf%lf",&p[i].x,&p[i].y);
        for (i=0;i<n-2;i++)  //��ȷ��һ��ʼ�ķ�����˳ʱ�뻹����ʱ��
        {
            direct=Cross(p[i+1],p[i+2],p[i]);
            if (epssgn(direct)!=0) break;
        }
        flag=1;
	for (i;i<n-2;i++)  //�������Ƚϣ�����з������ô���˳�
        {
            tmp=Cross(p[i+1],p[i+2],p[i]);
	    if (epssgn(tmp*direct)<0)
	    {
                flag=0;
                break;
	    }
        }
        if (!flag)
        {
	    printf("HOLE IS ILL-FORMED\n");
	    continue;
        }
        //���direct>0��ʾ����ʱ��㼯��������˳ʱ�룬���¹���һ�·�����ú���
	if (direct>0) for (i=0;i<n;i++) res[i]=i;
	else for (i=0;i<n;i++) res[i]=n-i-1;
	chnum=n;
        if (!PointInConvexHull(p,res,chnum,cir.center))
        {
            printf("PEG WILL NOT FIT\n");
            continue;
        }
        //�Ա�Բ�ĺ�ÿһ���ߵľ���
        flag=1;
        for (i=0;i<n;i++) if (cir.r>PointToSegDist(p[i],p[(i+1)%n],cir.center))
        {
            printf("PEG WILL NOT FIT\n");
            flag=0;
            break;
        }
        if (flag) printf("PEG WILL FIT\n");
    }
    return 0;
}
