#include<stdio.h>
#include<math.h>
#include<string.h>

#define eps  1e-7
#define MaxN 51

struct Point
{
    double x,y;
    Point(double a=0,double b=0){x=a;y=b;}
};

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

Point p[MaxN];
int res[MaxN];
int vis[MaxN];
int chnum;

int main()
{
    int i,start,n=0;
    freopen("poj2007.txt","r",stdin);
    freopen("poj2007ans.txt","w",stdout);
    while (scanf("%lf%lf",&p[n].x,&p[n].y)!=EOF) n++;
    chnum=Graham(p,n,res);
    for (start=0;start<chnum;start++) if(!p[res[start]].x && !p[res[start]].y) break;
    for (i=start;i<chnum;i++) printf("(%.f,%.f)\n", p[res[i]].x, p[res[i]].y);
    for (i=0;i<start;i++) printf("(%.f,%.f)\n", p[res[i]].x, p[res[i]].y);
    return 0;
}
