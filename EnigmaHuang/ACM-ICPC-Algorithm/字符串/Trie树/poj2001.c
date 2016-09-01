#include<stdio.h>

#define CharsetSize 26
#define CharsetBase 'a'
#define MaxN 1001

struct TrieNode
{
    int num;
    int next[CharsetSize];
}trie[MaxN*CharsetSize];

int index;

void Insert (char str[])
{
    int p=1,i;
    for (i=0;str[i];i++)
    {
        if (trie[p].next[str[i]-CharsetBase]==0)
        {
            trie[p].next[str[i]-CharsetBase]=++index;
            trie[index].num=0;  //�½�һ���ڵ㣬��û���߹�
        }
        p=trie[p].next[str[i]-CharsetBase];
        trie[p].num++;   //�����һ��·����ĳ����������һ��
    }
}

void Search(char str[])
{
    int i,p=1;
    for (i=0;str[i];i++)
    {
        p=trie[p].next[str[i]-CharsetBase];
        printf("%c",str[i]);        //����ظ��Ĳ���
        if (trie[p].num==1) return; //�����Ѿ�û�б�ĵ�����֮�ظ��ˣ�ֱ�ӷ���
    }
}

char str[MaxN][30];

int main ()
{
    int n=0,i;
    freopen("poj2001.txt","r",stdin);
    freopen("poj2001ans.txt","w",stdout);
    index=1;
    while (scanf("%s",str[n])!=EOF)  Insert(str[n++]);
    for (i=0;i<n;i++)
    {
        printf("%s ",str[i]);
        Search(str[i]);
        printf("\n");
    }
    return 0;
}
