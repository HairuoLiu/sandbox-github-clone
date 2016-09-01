#include<stdio.h>
#include<string.h>

#define MaxN 101
#define MaxL 10001

int len,k,n[MaxN],ans[MaxN];
int flag[MaxN][MaxL],mod[MaxN][10];

char num[MaxN];

/*mod[i][j]��ʾj*(10^i) mod k��ʹ��ģͬ�෽ʽ�õ�*/
void InitMod()
{
    int i,j;
    for (i=0;i<=9;i++) mod[0][i]=i%k;
    for (i=1;i<len;i++)
        for (j=0;j<=9;j++) mod[i][j]=(mod[i-1][j]*10)%k;
}

/*pos��ʾ����������λ����n�е���һλ
  restnum��ʾ���ܸ��Ķ��ٸ�����
  mod_k��ʾ��ǰ���ִ�mod k�Ľ��*/
int DFS(int pos,int restnum,int mod_k)
{
    int i,j,new_mod_k;
    if (mod_k==0) return 1;
    if (restnum==0 || pos<0) return 0;
    //�ǳ���Ҫ�ļ�֦�����ӻᳬʱ�������ǰ�����ĸı䳤��
    //С�����������λ�õõ���������ĵĸı䳤�ȣ��������Ž⣬����
    if (restnum<=flag[pos][mod_k]) return 0;  
    
    for (i=pos;i>=0;i--)  //������ǰ�����±�nС�������Ӹ�λ��ʼ��
        for (j=0;j<n[i];j++)
        {
            if (i==len-1 && j==0) continue;
            new_mod_k=(mod_k-(mod[i][n[i]]-mod[i][j])+k)%k;
            ans[i]=j;
            if (DFS(i-1,restnum-1,new_mod_k)) return 1;
            ans[i]=n[i];
        }

    for (i=0;i<=pos;i++)  //������ǰ�����±�n��������ӵ�λ��ʼ��
        for (j=n[i]+1;j<10;j++)
        {
            new_mod_k=(mod_k-(mod[i][n[i]]-mod[i][j])+k)%k;
            ans[i]=j;
            if (DFS(i-1,restnum-1,new_mod_k)) return 1;
            ans[i]=n[i];
        }
        
    flag[pos][mod_k]=restnum;  //����ʧ�ܣ����¼�֦��Ϣ
    return 0;
}

int main()
{
    int i,n_mod_k;
    freopen("poj3373.txt","r",stdin);
    freopen("poj3373ans.txt","w",stdout);
    while (scanf("%s%d",num,&k)!=EOF)
    {
        n_mod_k=0;
        len=strlen(num);
        InitMod();
        for (i=0;i<len;i++)
        {
            n[i]=num[len-i-1]-'0';                   //���������n������ʹ��
            ans[i]=n[i];
            n_mod_k=(n_mod_k+mod[i][n[i]])%k;        //ģͬ�����n mod k
        }
        memset(flag,0,sizeof(flag));
        for (i=1;i<=len;i++) if (DFS(len-1,i,n_mod_k)) break;
        for (i=len-1;i>=0;i--) printf("%d",ans[i]);  //�����޸ĵ�λ����С����ö��
        printf("\n");
    }
    return 0;
}
