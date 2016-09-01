#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<vector>

#define CharsetBase 'a'
#define CharsetSize 28

using namespace std;

struct TrieNode        //��̬����
{
    TrieNode* next[CharsetSize];     //26��Сд��ĸ����'?'��'*'
    vector<int> pattern;    //��Ǹýڵ���������ַ�������Щģʽ��
    TrieNode(){memset(next,NULL,sizeof(next));}
};

TrieNode *root=new TrieNode();

void Insert(char str[],int pos)
{
    TrieNode *p=root;
    int i,j;
    for (i=0;str[i];i++)
    {
        if (str[i]=='?') j=26;
        else if (str[i]=='*') j=27;
        else j=str[i]-CharsetBase;
        if (p->next[j]==NULL) p->next[j]=new TrieNode();
        p=p->next[j];
    }
    p->pattern.push_back(pos);
}

vector<int> ans;

void DFS(char str[],int k,TrieNode *p)    //��ǰλ�����ڽڵ�p,Ҫ���ҵ��ַ�str[k]
{
    int i,s;
    TrieNode *q;
    if (str[k]=='\0')    //�ַ�����β
    {
        while (p!=NULL)
        {
            s=p->pattern.size();
            for (i=0;i<s;++i) ans.push_back(p->pattern[i]);  //������ƥ���ģʽ����������
            p=p->next[27];        //��Ϊ*ͨ������Ե���0���ַ�������������
        }
    }
    else
    {
        q=p->next[str[k]-CharsetBase];
        if (q!=NULL) DFS(str,k+1,q);
        q=p->next[26];    //ģʽ����ǰλ���ϵ��ַ���?
        if (q!=NULL) DFS(str,k+1,q);
        q=p->next[27];    //ģʽ����ǰλ���ϵ��ַ���*
        if (q!=NULL) for (;k<=strlen(str);k++) DFS(str,k,q); // *ͨ�������ƥ��������ַ�
    }
}

int main()
{
    int n,m,i,s;
    char str[25];
    freopen("poj1816.txt","r",stdin);
    freopen("poj1816ans.txt","w",stdout);
    scanf("%d %d", &n, &m);
    for (i=0;i<n;++i)
    {
        scanf("%s",str);
        Insert(str,i);
    }
    while (m--)
    {
        scanf("%s",str);
        ans.clear();
        DFS(str,0,root);    //�Ӹ���㿪ʼ����
        if (ans.empty()) printf("Not match\n");
        else
        {
            //vector����Ľ���������ȥ��
            sort(ans.begin(),ans.end());
            printf("%d ",ans[0]);
            s=ans.size();
            for (i=1;i<s;++i) if (ans[i]!=ans[i-1]) printf("%d ",ans[i]);
            printf("\n");
        }
    }
    return 0;
}
