#include<stdio.h>
#include<math.h>

#define eps  1e-7
#define MaxN 10001

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


inline double dis(Point &a,Point &b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

/*------Graham��͹��----*/
/*
�õ�sp-op��ep-op�Ĳ��
>0ʱep��opsp����ʱ�뷽��<0ʱ˳ʱ�룬=0ʱ����
*/
inline double Cross(Point sp,Point ep,Point op)
{
    return (sp.x-op.x)*(ep.y-op.y)-(ep.x-op.x)*(sp.y-op.y);
}

inline int cmp(Point &a,Point &b)
{
    if (a.y==b.y) return (a.x<b.x);
    return (a.y<b.y);
}

//����eps�ľ����жϴ�/С����
inline int epssgn(double x)
{
    if (fabs(x)<eps) return 0;
    else return x<0?-1:1;
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

/*------Graham��͹��----*/

//��������ģ�����ȣ�
double len(Vector a)
{
    return sqrt(a.x*a.x+a.y*a.y);
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

Point p0[MaxN],p[MaxN],q[MaxN];
int   res[MaxN];

double min(double a,double b)
{
    if (a>b) return b; else return a;
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

int main()
{
    int i,n,m;
    double ans,tmp;
    freopen("poj3608.txt","r",stdin);
    freopen("poj3608ans.txt","w",stdout);
    while (scanf("%d%d",&n,&m)!=EOF)
    {
        if (n==0 && m==0) break;
        //����һ�����±��棬��ú���д����̫�鷳 
        for (i=0;i<n;i++) scanf("%lf%lf",&p0[i].x,&p0[i].y);
        n=Graham(p0,n,res);
        for (i=0;i<n;i++) p[i]=p0[res[i]];
        
        for (i=0;i<m;i++) scanf("%lf%lf",&p0[i].x,&p0[i].y);
        m=Graham(p0,m,res);
        for (i=0;i<m;i++) q[i]=p0[res[i]];
        
        ans=99999999.0;
        //p��������סp����תq 
        tmp=TwoConvexHullMinDist(p,q,n,m);
        if (tmp<ans) ans=tmp;
        //q��������סq����תp 
        tmp=TwoConvexHullMinDist(q,p,m,n);
        if (tmp<ans) ans=tmp;
        printf("%.5f\n",ans);
    }
    return 0;
}
