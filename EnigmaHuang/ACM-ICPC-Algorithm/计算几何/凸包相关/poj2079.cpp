#include<stdio.h>
#include<math.h>

#define eps  1e-7
#define MaxN 50001

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

//�������������������������Ҫ����2
double Cross(Vector a,Vector b)
{
    return a.x*b.y-b.x*a.y;
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

Point p[MaxN];
int   res[MaxN];
int   chnum;

int main()
{
    int i,n;
    double ans;
    freopen("poj2079.txt","r",stdin);
    freopen("poj2079ans.txt","w",stdout);
    while (scanf("%d",&n)!=EOF)
    {
        if (n==-1) break;
        for (i=0;i<n;i++) scanf("%lf%lf",&p[i].x,&p[i].y);
        if (n<3) printf("0.00\n");
        else
        {
            chnum=Graham(p,n,res);
            ans=ConvexHullMaxTriangleArea(p,res,chnum);
            printf("%.2f\n",ans);
        }
    }
    return 0;
}
