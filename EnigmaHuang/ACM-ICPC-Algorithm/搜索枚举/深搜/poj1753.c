#include<stdio.h>

int chess[4][4];
int ans;

void Change(int x,int y)
{
    if (x>=0 && x<=3 && y>=0 && y<=3) chess[x][y]=!chess[x][y];
}

void Flip(int pos)
{
    int i,j;
    i=pos/4;
    j=pos%4;
    Change(i,j);
    Change(i+1,j);
    Change(i,j+1);
    Change(i-1,j);
    Change(i,j-1);
}

int Complete()
{
    int i,j,s=0;
    for (i=0;i<4;i++)
       for (j=0;j<4;j++) s+=chess[i][j];
    if (s==16 || s==0) return 1;
    else return 0;
}

void DFS(int pos,int cnt)
{
    if (Complete())
    {
        if (ans>cnt) ans=cnt;
        return;
    }

    if (pos>=16) return;

    DFS(pos+1,cnt);    //��һ���񲻷���������һ��
    
    Flip(pos);         //��һ������
    DFS(pos+1,cnt+1);  //������һ��
    Flip(pos);         //�ָ�����������
}

int main()
{
    char c;
    int i,j;
    
    freopen("poj1753.txt","r",stdin);
    freopen("poj1753ans.txt","w",stdout);
    
    for (i=0;i<4;i++)
    {
        for (j=0;j<4;j++)
        {
            scanf("%c",&c);
            if (c=='w') chess[i][j]=0;
            else        chess[i][j]=1;
        }
        scanf("%c",&c);
    }
    
    ans=17;  //��෭ת16�Σ�����û�����壨һ���㷭һ������û���壩
    DFS(0,0);
    
    if (ans==17) printf("Impossible\n");
    else printf("%d\n",ans);
    return 0;
}
