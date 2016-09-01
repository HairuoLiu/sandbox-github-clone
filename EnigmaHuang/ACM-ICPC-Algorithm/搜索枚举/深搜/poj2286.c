#include<stdio.h>

int pos[8][7]={
0 ,2 ,6 ,11,15,20,22,  //����A���������ǵڼ�����
1 ,3 ,8 ,12,17,21,23,  //����B
10,9 ,8 ,7 ,6 ,5 ,4 ,  //����C
19,18,17,16,15,14,13,  //����D
23,21,17,12,8 ,3 ,1 ,  //����E���ͷ���B�෴
22,20,15,11,6 ,2 ,0 ,  //����F���ͷ���A�෴
13,14,15,16,17,18,19,  //����G���ͷ���D�෴
4 ,5 ,6 ,7 ,8 ,9 ,10}; //����H���ͷ���C�෴

int aim[8]={6,7,8,11,12,15,16,17};  //Ŀ������İ˸��������ǵڼ�����
int rev[8]={5,4,7,6,1,0,3,2};       //rev[i]��ʾ��i�ֲ����������ǵڼ��ֲ���

int map[25],ans[200],DEPTH;

int Remains()
{
    int i,cnt[4]={0,0,0,0},ans=0;
    for (i=0;i<8;++i) ++cnt[map[aim[i]]];  //���Ŀ������123�����ж��ٸ�
    for (i=1;i<=3;++i) if (ans<cnt[i]) ans=cnt[i];
    return 8-ans;
}

int Move(int dir)  //�������ƶ�
{
    int i,head=map[pos[dir][0]];
    for (i=0;i<6;++i) map[pos[dir][i]]=map[pos[dir][i+1]];
    map[pos[dir][6]]=head;
}

int DFS(int depth)
{
    int i,cnt;
    for(i=0;i<8;++i)
    {
        Move(i);
        cnt=Remains();
        if (cnt==0)
        {
            ans[depth]=i;
            return depth+1;
        }
        if (depth+cnt<DEPTH)
        {
            ans[depth]=i;
            if (DFS(depth+1)) return depth+1;
        }
        Move(rev[i]);
    }
    return 0;
}

int main()
{
    int i;
    freopen("poj2286.txt","r",stdin);
    freopen("poj2286ans.txt","w",stdout);
    while (scanf("%d",&map[0])!=EOF && map[0])
    {
        for (i=1;i<24;++i) scanf("%d",&map[i]);
        if (Remains()==0)  //����Ҫ�ƶ���ֱ�����Ŀ���������
        {
            puts("No moves needed");
            printf("%d\n",map[6]);
            continue;
        }
        for (DEPTH=1;!DFS(0);++DEPTH);  //������������
        for (i=0;i<DEPTH;++i) printf("%c",ans[i]+'A');
        printf("\n%d\n",map[6]);
    }
    return 0;
}
