#include<stdio.h>
#include<string.h>

#define MaxN 1005
#define MaxL 10
#define Max(a,b) (a)>(b)?(a):(b)
#define Min(a,b) (a)<(b)?(a):(b)

class RMQ
{
    private:
            int size;
            int min[MaxN][MaxL];  //������Сֵ
        int max[MaxN][MaxL];  //�������ֵ
    public:
            RMQ()
            {
            memset(min,0,sizeof(min));
            memset(max,0,sizeof(max));
            }
            void Init(int _size,int a[])  //a��Ҫ��1��ʼ���
            {
            int i,j;
            size=_size;
            for (i=1;i<=size;i++) min[i][0]=max[i][0]=a[i];
            for (j=1;(1<<j)<=size;j++)
                for (i=1;i+(1<<j)-1<=size;i++)
                {
                    min[i][j]=Min(min[i][j-1],min[i+(1<<(j-1))][j-1]);
                    max[i][j]=Max(max[i][j-1],max[i+(1<<(j-1))][j-1]);
                }
            }
            int RangeMinQuery(int l,int r)
            {
            int k=0;
            if (l>r) return 0;
            while ( (1<<(k+1)) <= (r-l+1) ) k++;
            return Min(min[l][k],min[r+1-(1<<k)][k]);
            }
            int RangeMaxQuery(int l,int r)
            {
            int k=0;
            if (l>r) return 0;
            while ( (1<<(k+1)) <= (r-l+1) ) k++;
            return Max(max[l][k],max[r+1-(1<<k)][k]);
            }
};
