#include <stdio.h>
#include <algorithm>

using namespace std;

#define MaxN 100005

struct TDivideTree
{
    int n;
    int sorted[MaxN];   //���������
    int sum[20][MaxN];  //sum[i][j]=��i��1~j���ֵ���������Ԫ�ظ���(����j��
    int data[20][MaxN]; //data[i]=��i��Ԫ������
    /*-----��������-----*/
    void Init(int OriginalData[],int size)
    {
        int i;
        n=size;
        for (i=1;i<=n;i++) sorted[i]=data[0][i]=OriginalData[i];
        sort(sorted+1,sorted+n+1);
        Build(0,1,n);
    }
    void Build(int c,int L,int R)   //����
    {
        int mid=(L+R)/2;
        int lsame=mid-L+1;    //lsame��¼���м�ֵsorted[mid]��ȵģ��ҿɷֵ����ӵ����ĸ���
        int lp=L,rp=mid+1;    //��ǰ�ڵ�����Ӻ��Һ��Ӵ��������
        int i;
        //���һ��ʼ��lsame
        for (i=L;i<mid;i++) if (sorted[i]<sorted[mid]) lsame--;
        for (i=L;i<=R;i++)
        {
            //��ǰ�������һ��ȷ����ǰ�ڵ������ڵ�����Ԫ�����ĸ�������
            if (i==L) sum[c][i]=0;
            else sum[c][i]=sum[c][i-1];
            if (data[c][i]<sorted[mid]) //��ǰԪ�ر��м�ֵsorted[mid]С����������
            {
                data[c+1][lp++]=data[c][i];
                sum[c][i]++;
            }
            //��ǰԪ�ر��м�ֵsorted[mid]�󣬷����Һ���
            else if (data[c][i]>sorted[mid]) data[c+1][rp++]=data[c][i];
            else //��ǰԪ��ֵ���м�ֵsorted[mid]��ȣ�����lsame���жϷ������ӻ����Һ���
            {
                if (lsame)
                {
                    lsame--;
                    sum[c][i]++;
                    data[c+1][lp++]=sorted[mid];
                }
                else data[c+1][rp++]=sorted[mid];
            }
        }
        if (L==R) return;    //��Ҷ�ӽڵ㣬����
        Build(c+1,L,mid);    //�ݹ������������
        Build(c+1,mid+1,R);  //�ݹ�����Һ�������
    }
    int Query(int c,int L,int R,int ql,int qr,int k)
    {
        //cΪ���Ĳ�����L,RΪ��ǰ�ڵ�����䷶Χ��ql,qrΪ��ѯ�����䷶Χ��kΪ��ѯ��Χ�ڵ�k�����
        int s;  //[L,ql-1]�н������ӵ�Ԫ�صĸ���
        int ss; //[ql,qr]�н������ӵ�Ԫ�صĸ���
        int mid=(L+R)/2;
        if (L==R) return data[c][L]; //��Ҷ�ӽڵ�ֱ�ӷ��ص�k�����
        if (L==ql) //�˵��غϵ��������������
        {
            s=0;
            ss=sum[c][qr];
        }
        else
        {
            s=sum[c][ql-1];
            ss=sum[c][qr]-s;
        }
        //���ӵ�Ԫ�ظ�������k�����������в�ѯ�������Һ����в�ѯ
        if (k<=ss) return Query(c+1, L   ,mid,    L+s     ,    L+s+ss-1   ,k);
        else       return Query(c+1,mid+1, R ,mid+1+ql-s-L,mid+1+qr-s-ss-L,k-ss);
    }
    /*-----�������ܽ�����������Ӧ��-----*/
    //[L,R]�����K�����
    int KthMaxInRange(int L,int R,int K)
    {
        return Query(0,1,n,L,R,K);
    }
    //������[L,R]�е�һ����XС�����ǵڼ����
    int GetXPrecursorRankInRange(int X,int L,int R)
    {
        int mid=(L+R)/2;
        while (L<R)
        {
            if (Query(0,1,n,L,R,mid)<=X) L=mid;
            else R=mid-1;
            mid=(L+R)/2;
        }
        if (Query(0,1,n,L,R,mid)<=X) return mid; else return -1;
    }
    //������[L,R]�е�һ����X������ǵڼ����
    int GetXSuccessorRankInRange(int X,int L,int R)
    {
        int mid=(L+R)/2;
        while (L<R)
        {
            if (Query(0,1,n,L,R,mid)>=X) R=mid;
            else L=mid+1;
            mid=(L+R)/2;
        }
        if (Query(0,1,n,L,R,mid)>=X) return mid; else return -1;
    }
}DT;

int a[MaxN];

int main()
{
    int i,l,r,n,m,k;
    freopen("poj2104.txt","r",stdin);
    freopen("poj2104ans.txt","w",stdout);
    while (scanf("%d%d",&n,&m)!=EOF)
    {
        for (i=1;i<=n;i++) scanf("%d",&a[i]);
        DT.Init(a,n);
        for (i=1;i<=m;i++)
        {
            scanf("%d%d%d",&l,&r,&k);
            printf("%d\n",DT.KthMaxInRange(l,r,k));
        }
    }
    return 0;
}
