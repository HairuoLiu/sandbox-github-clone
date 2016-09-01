#include<stdio.h>
#include<string.h>
#define MaxN 21

int len[MaxN],used[MaxN];
int solved,sticknum,totallen,sidelen;

void QSort(int l,int r)
{
    int i,j,mid,swap;
    i=l;j=r;
    mid=len[(l+r)/2];
    while (i<=j)
    {
        while (len[i]>mid) i++;
        while (len[j]<mid) j--;
        if (i<=j)
        {
            swap=len[i];
            len[i]=len[j];
            len[j]=swap;
            i++;j--;
        }
    }
    if (i<r) QSort(i,r);
    if (l<j) QSort(l,j);
}

void DFS(int startpos,int sumlen,int searched)
{
    int i,j;
    if (searched==3)
    {
        solved=1;
        return;
    }
    if (sumlen==sidelen) DFS(1,0,searched+1);
    if (solved) return;  //�������¶��Ѿ��ѳ��˽����ֱ�ӷ��� 
    for (i=startpos;i<=sticknum;i++)
    {
        if (!used[i] && sumlen+len[i]<=sidelen)
        {
            used[i]=1;
            DFS(i+1,sumlen+len[i],searched);
            if (solved) return;
            else //��֦4����ͬ���ȵ��Ѿ��������ˣ����Ҳ��У������� 
            {
                used[i]=0;
                while (len[i]==len[i+1]) i++;
            }
            
        } 
    }
} 

int main()
{
    int testcase,i;
    freopen("poj2362.txt","r",stdin);
    freopen("poj2362ans.txt","w",stdout);
    scanf("%d",&testcase);
    while (testcase--)
    {
        scanf("%d",&sticknum);
        solved=totallen=0;
        for (i=1;i<=sticknum;i++) 
        {
            scanf("%d",&len[i]);
            totallen+=len[i];
        }
        if (totallen%4!=0) printf("no\n"); //��֦1���ܳ���Ҫ��4�ı��� 
        else 
        {
            QSort(1,sticknum); //��֦3�����򣬴Ӵ�С���� 
            memset(used,0,sizeof(used));
            sidelen=totallen/4;
            if (len[1]>sidelen) //��֦2���֦��ҪС�ڱ߳� 
            {
                printf("no\n");
                continue;
            }
            DFS(1,0,0);
            if (solved) printf("yes\n"); else printf("no\n"); 
        }
    }
}
