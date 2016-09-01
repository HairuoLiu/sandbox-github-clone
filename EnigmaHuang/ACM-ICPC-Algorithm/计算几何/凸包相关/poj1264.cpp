#include<stdio.h>
#include<math.h>
#include<string.h>

#define eps  1e-7
#define MaxN 1001
#define pi   3.1415926535

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

/* 2����������ͬʱҲ��������� */
inline double Cross(Vector a,Vector b)
{
    return a.x*b.y-b.x*a.y;
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

/*------Graham��͹��----*/

struct ConvexHull
{
    Point  p[MaxN];
    int    res[MaxN];
    int    chnum;
    double area;
}kingdom[30];

int main()
{
    int n,i,k=0,target;
    int vis[MaxN];
    Point bomb;
    double ans;
    freopen("poj1264.txt","r",stdin);
    freopen("poj1264ans.txt","w",stdout);
    while (scanf("%d",&n)!=EOF)
    {
	if (n==-1) break;
        for (i=0;i<n;i++) scanf("%lf%lf",&kingdom[k].p[i].x,&kingdom[k].p[i].y);
        kingdom[k].chnum=Graham(kingdom[k].p,n,kingdom[k].res);
        kingdom[k].area=0.0;
        for (i=1;i<kingdom[k].chnum-1;i++)
	    kingdom[k].area+=Cross(kingdom[k].p[kingdom[k].res[i]]
	                          -kingdom[k].p[kingdom[k].res[0]],
	                           kingdom[k].p[kingdom[k].res[i+1]]
	                          -kingdom[k].p[kingdom[k].res[0]]);
	kingdom[k].area/=2;
	k++;
    }
    memset(vis,0,sizeof(vis));
    ans=0;
    kingdom[k].area=0;
    while (scanf("%lf%lf",&bomb.x,&bomb.y)!=EOF)
    {
	for (target=0;target<k;target++)
	    if (PointInConvexHull(kingdom[target].p,kingdom[target].res,
	                          kingdom[target].chnum,bomb)) break;
	if (!vis[target]) ans+=kingdom[target].area;
	vis[target]=1;
    }
    printf("%.2f\n",ans);
    return 0;
}
