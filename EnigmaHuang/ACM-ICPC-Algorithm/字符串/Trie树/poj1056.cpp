#include<stdio.h>
#include<string.h>

#define CharsetSize 2       //�ַ�����С
#define CharsetBase '0'     //�ַ�����С�ַ�

#define MaxN 101

struct TrieNode
{
    int flag;
    int next[CharsetSize];
}trie[MaxN*CharsetSize];

int index;

int Insert(char str[])
{
    int i,p=1,f=1,f2=0;
    for (i=0;str[i];i++)
    {
        if (trie[p].next[str[i]-CharsetBase]==0)   //�ڵ㲻����
        {
            trie[p].next[str[i]-CharsetBase]=++index;
            f2=1;              //������һ���½ڵ�
        }
        p=trie[p].next[str[i]-CharsetBase];
        if (trie[p].flag) f=0; //�������ڵ���֮ǰĳ�����ʵĽ�������ǰ׺
    }
    trie[p].flag=1;   //��Ǹõ�Ϊһ�����ʵĽ���
    if (f2==0) f=0;   //���û�д����½ڵ㣬����0
    return f;
}

int TrieInit()
{
    index=1;
    memset(trie,0,sizeof(trie));
}

int main()
{
    int flag,t;
    char s[10];
    freopen("poj1056.txt","r",stdin);
    freopen("poj1056ans.txt","w",stdout);
    for (t=1;scanf("%s",s)!=EOF;t++)
    {
	TrieInit();
	Insert(s);
	flag=1;
	while (scanf("%s",s) && s[0]!='9') if (!Insert(s)) flag=0;
        if (flag) printf("Set %d is immediately decodable\n",t);
        else  printf("Set %d is not immediately decodable\n",t);
    }
    return 0;
}
