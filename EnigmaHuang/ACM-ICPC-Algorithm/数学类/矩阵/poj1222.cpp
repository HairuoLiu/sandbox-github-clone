#include<stdio.h>
#include<string.h>

int a[35][35]; 
int ans[30];
int move[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};

void Swap(int &a,int &b)
{
    int x;
    x=a;a=b;b=x;
} 

void GaussSolve(int row,int col)
{
    int i,j,k,id,l,swap,lcm,tmp,x,y;
    for (i=j=0;i<row && j<col;i++,j++)  //i�ǵ�ǰ�У�j�ǵ�ǰ��Ԫλ�� 
    {
        id=i;
        //��ʣ�µ������ҵ�ǰ��Ԫ���ģ�����������ǰ�� 
        for (k=i+1;k<row;k++) if(a[k][j]>a[id][j]) id=k;
        for (k=j;k<=col;k++) Swap(a[i][k],a[id][k]);
        //ʣ�µ����ﵱǰ��Ԫ���������ˣ���Ԫ�����һλ 
        if (a[i][j]==0) 
	{ 
            i--; 
            continue; 
        }
        //������Ԫ 
        for (k=i+1;k<row;k++) if (a[k][j]) //�����������
            for (l=j;l<=col;l++) a[k][l]=a[k][l]^a[i][l];
    }
    
    for (i=i-1;i>=0;i--)
    {
        for (j=i+1;j<col;j++) a[i][col-1]^=(a[i][j]&&a[j][col-1]);
        ans[i]=a[i][col-1];
    }
}

int main()
{
    int cases,i,j,t=0,k,ty,tx;
    freopen("poj1222.txt","r",stdin);
    freopen("poj1222ans.txt","w",stdout);
    scanf("%d",&cases);
    while (cases--)
    {
        t++;
        memset(a,0,sizeof(a));
        for (i=0;i<5;i++)
            for (j=0;j<6;j++)
            {
       	        scanf("%d",&a[i*6+j][30]);
       	        a[i*6+j][i*6+j]=1;
       	        for (k=0;k<4;k++)
                {
                    tx=i+move[k][0];
                    ty=j+move[k][1];
                    if (!(tx>=0 && tx<5 && ty>=0 && ty<6)) continue;
                    a[tx*6+ty][i*6+j]=1;       
                }
            }

        GaussSolve(30,31);
        printf("PUZZLE #%d\n",t);
        for (i=0;i<5;i++)
        {
            for (j=0;j<6;j++) printf("%d ",ans[i*6+j]); 
	    printf("\n"); 
        }
    }
    return 0;
}
