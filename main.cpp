#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define SEP "------------------------------------------------------------------------------"//������ܿ��
#define COL 78
#define MARGIN_X 20             //��߾�
#define MAP_START_Y 3           //��ʼy������
#define MAP_END_Y 11            //����y������
#define INFO_START_Y 12         //��Ϣ���濪ʼ��Y����
#define INFO_END_Y 19           //��Ϣ���������Y����

void SetPosition(int x,int y);
/*��x�У�y�п�ʼ��rowcount��*/
void Clear(int x,int y,int rowcount);
/*�������ֵ�ǰ��ɫ���ͱ���ɫ*/
void SetColor(int froeColor,int bankColor);
void Clear(int x,int y,int rowcount)
{

    //ÿ�����78���ַ�����ÿ�д�ӡ78���ո�
    int i,j;
    for(i=0;i<rowcount;i++)
    {
        SetPosition(x,y+i);
        for(j=0;j<78;j++)
        {
            printf(" ");
        }
    }
}

void SetPosition(int x,int y)
{
    HANDLE winHandle;   //���
    COORD pos = {x,y};
    winHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    //���ù�������
    SetConsoleCursorPosition(winHandle,pos);
}
void SetColor(int foreColor,int bankColor)
{
    HANDLE winHandle;   //���
    winHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    //����������ɫ
    SetConsoleTextAttribute(winHandle,foreColor+bankColor*0x10);
}



const int WORD_LENGTH = 256;          //ʹ��const int ����defineҪ��
int FREQUENCY_COUNT=7;	              //�û�ָ��ͳ�ƴʵ�Ƶ��
struct wordNode
{
    char word[WORD_LENGTH];          //��ŵ���
    int iWordCount;                  //���ʳ��ִ���
	wordNode *pNext;                 //�ṹ���ָ��
};

wordNode *pHeader = NULL;            //�����ͷָ��

//������Ҫ�ĺ���
void CountWord(char *current);
wordNode * SearchWord(char *current);
void PrintResult();
void Release();

int k=1;
int main()
{
    char temp[WORD_LENGTH]; //��ʱ��ŵ��ʵĴ���
    int k=1;    //����whileѭ���壬�γ���ѭ��
    FILE *fp; //��Ҫ��ȡ���ļ�
    if((fp=fopen("Breaking Dawn.txt", "r"))==NULL )
    {
        printf("Open file failed!!\n");
        exit(1);
    }
        while( EOF != (fscanf(fp,"%s",temp)) )//ѭ����ȡ�ı��е�����
    {
        CountWord(temp);
    }
       fclose(fp); //�ر��ļ�

       while(k)
        {
            PrintResult(); //���ͳ�ƽ��;
        }
        system("pause");

   	   Release(); //�ͷ��ڴ棬���ɺ�ϰ��
}
int i=1;
void CountWord(char *current)//����ͳ��
{
    wordNode *pNode = NULL;
    pNode = SearchWord(current);
    if(NULL == pNode)
    {
        return;
    }
    else
    {
        pNode->iWordCount++;
    }
}

wordNode * SearchWord(char *current)//���ҵ������ڽڵ�
{

    if( NULL == pHeader) //������Ϊ�յ�ʱ��Ҳ��ͳ�Ƶ�һ������ʱ
    {
        pHeader = new wordNode;
        strcpy(pHeader->word, current);
        pHeader->iWordCount = 0;
        pHeader->pNext = NULL;
        return pHeader;
    }

    //�������е�����
    wordNode *pCurr = pHeader;
    wordNode *pPre = NULL;
    while( (NULL != pCurr) && (0 != strcmp(pCurr->word, current)) )
    {
        pPre = pCurr;
        pCurr = pCurr->pNext;
    }

    if(NULL == pCurr) //�õ��ʲ�����
    {
        pCurr = new wordNode;
        strcpy(pCurr->word, current);
        pCurr->iWordCount = 0;
        pCurr->pNext = NULL;
        pPre->pNext = pCurr;
    }
    return pCurr;
}

void PrintResult()//������
{
    int num;
    void view();
    void help();
    void findk();
    void show();
    void print();
    SetColor(4,14);//���ĵ�ǰ���ֵ���ɫ�ı���ɫ
    SetColor(10,0);//��ӡ�귵��Ĭ�ϵ�ͼ��ɫ
    SetPosition(MARGIN_X,0);
    printf("%s\n",SEP);
    SetPosition(MARGIN_X,1);
    printf("|");
    SetPosition(MARGIN_X+25,1);
    printf("��ӭ�������ı���Ƶͳ��ϵͳ��\n");
    SetPosition(MARGIN_X+77,1);
    printf("|");
    SetPosition(MARGIN_X,2);
    printf("%s",SEP);

    int i,j;
    printf("\n");
    for(i=0;i<8;i++)
    {
        SetPosition(MARGIN_X,MAP_START_Y+i);
        for(j=0;j<8;j++)
        {
            if(j==0)
            {
                printf("|  ");
            }
            SetColor(4,14);//���ĵ�ǰ���ֵ���ɫ�ı���ɫ
            SetColor(10,0);//��ӡ�귵��Ĭ�ϵ�ͼ��ɫ
        }
        SetPosition(MARGIN_X+77,3+i);
        printf("|");
    }
    SetPosition(MARGIN_X,MAP_END_Y);
    printf(SEP);

    SetPosition(MARGIN_X+30,MAP_START_Y);
    printf("ϵͳ���ܲ˵�");
    SetPosition(MARGIN_X+25,MAP_START_Y+2);
    printf("1.ϵͳ������˵��");
    SetPosition(MARGIN_X+25,MAP_START_Y+3);
    printf("2.��ʾ���ı����е��ʴ�Ƶ��Ϣ");
    SetPosition(MARGIN_X+25,MAP_START_Y+4);
    printf("3.���Ҵ�����������ĵ��ʴ�Ƶ");
    SetPosition(MARGIN_X+25,MAP_START_Y+5);
    printf("4.ͳ�Ʊ��Ĺ��е�������");
    SetPosition(MARGIN_X+25,MAP_START_Y+6);
    printf("5.�˳���Ƶϵͳ");
    SetPosition(MARGIN_X+25,MAP_START_Y+7);
	printf("��ѡ��˵����:");
	scanf("%d",&num);
	switch(num)     /*����switch��֧�ṹ���ø����ֹ��ܺ���*/
	{
	case 1:help();break;
	case 2:view();break;
	case 3:findk();break;
	case 4:show();break;
	case 5:
	    Clear(MARGIN_X,INFO_START_Y,20);
	    SetPosition(MARGIN_X+30,INFO_START_Y+5);
	    printf("��л����ʹ�ã��´��ٻأ�����");exit(0);break;
	default:printf("����1-6֮��ѡ��\n");
	}
}
help()  //������Ϣ
{
    SetPosition(MARGIN_X+10,INFO_START_Y);
    printf("��ӭʹ��ϵͳ����!");
    SetPosition(MARGIN_X,INFO_START_Y+1);
	printf("1.���ν���ϵͳ��,����ѡ��������Ҫ�Ĺ���!");
	SetPosition(MARGIN_X,INFO_START_Y+2);
	printf("2.���ղ˵���ʾ�������ִ���");
	SetPosition(MARGIN_X,INFO_START_Y+3);
	printf("3.ѡ����ź����Ų�ѯ֮��ϵͳ���Զ�������ѯ���");
	SetPosition(MARGIN_X,INFO_START_Y+4);
	printf("4.����ѡ��������Ǹ��ı����еĴʻ㼰��Ƶ��");
	SetPosition(MARGIN_X,INFO_START_Y+5);
	printf("5.����ѡ��������Ǵ��ڵ����û�����Ƶ���ĵ���");
	SetPosition(MARGIN_X,INFO_START_Y+6);
	printf("6.лл����ʹ�ã�ף��ʹ�����!");
}

view()  //��ѯ���ʴ�Ƶ��Ϣ
{
    //1,�����Ϣ���ڵ���Ϣ
    Clear(MARGIN_X,INFO_START_Y,7);
    int sum=0;
    int i=0;
    FILE* fp1=fopen("out_all_word_frequency.txt", "w");
    FILE* fp2=fopen("out_high_frequency.txt","w");
    if(NULL == pHeader)
    {
        printf("���ļ�Ϊ��!\n");
    }
    else
    {
        wordNode *pCurr = pHeader;
        //1,�����Ϣ���ڵ���Ϣ
        Clear(MARGIN_X,INFO_START_Y,7);
        while(NULL != pCurr)
        {
	    	fprintf(fp1,"%s\t%d\n", pCurr->word, pCurr->iWordCount);
            SetPosition(MARGIN_X,INFO_START_Y+i);
            printf("%-20s���ֵĴ���:%d", pCurr->word, pCurr->iWordCount);
            SetPosition(MARGIN_X+36,INFO_START_Y+i);
            printf("|");
            sum=sum+pCurr->iWordCount;
            if(pCurr->iWordCount>=FREQUENCY_COUNT)
                fprintf(fp2,"%s\t%d\n", pCurr->word, pCurr->iWordCount);
			pCurr = pCurr->pNext;
			SetPosition(MARGIN_X+40,INFO_START_Y+i);
            printf("%-20s���ֵĴ���:%d", pCurr->word, pCurr->iWordCount);
            pCurr = pCurr->pNext;
			i+=1;
        }
		printf("\n�ܹ���%d����",sum);
		 fclose(fp1);
		 fclose(fp2);
    }

}
findk()     //���Ҵ��ڳ�������ĵ���
{
    int wordcount;
    //1,�����Ϣ���ڵ���Ϣ
    Clear(MARGIN_X,INFO_START_Y,50);
    wordNode *pCurr = pHeader;
    //1,�����Ϣ���ڵ���Ϣ
    Clear(MARGIN_X,INFO_START_Y,i);

    FILE* fp3=fopen("input_frequency.txt","w");

    if(NULL == pHeader)
    {
        printf("���ļ�Ϊ��!\n");
    }
    else
    {
        wordNode *pCurr = pHeader;
        SetPosition(MARGIN_X+20,INFO_START_Y+1);
        printf("��������Ҫ��ѯ��Ƶ�Σ�");
        scanf("%d",&FREQUENCY_COUNT);
        int k=3;
        while(NULL != pCurr)
        {

			if(pCurr->iWordCount >= FREQUENCY_COUNT)
               {
                   SetPosition(MARGIN_X+10,INFO_START_Y+k);
                    printf("|");
                    SetPosition(MARGIN_X+20,INFO_START_Y+k);
                    printf("%-10s���ֵĴ���:%d", pCurr->word, pCurr->iWordCount);
                    SetPosition(MARGIN_X+50,INFO_START_Y+k);
                    printf("|");
                    fprintf(fp3,"%s\t%d\n", pCurr->word, pCurr->iWordCount);
                    pCurr = pCurr->pNext;
                    k+=1;
               }
               else
                pCurr = pCurr->pNext;
		}

		 fclose(fp3);
    }

}
show()      //��ʾȫ���˵�����Ϣ
{
    //1,�����Ϣ���ڵ���Ϣ
    Clear(MARGIN_X,INFO_START_Y,7);
    int wordcount,worder=0;
    int sum=0;
    FILE* fp1=fopen("out_all_word_frequency.txt", "w");
    FILE* fp2=fopen("out_high_frequency.txt","w");
    if(NULL == pHeader)
    {
        printf("���ļ�Ϊ��!\n");
    }
    else
    {
        wordNode *pCurr = pHeader;

        while(NULL != pCurr)
        {
            sum=sum+pCurr->iWordCount;
                if(pCurr->iWordCount >= FREQUENCY_COUNT)
			pCurr = pCurr->pNext;
		}
		SetPosition(MARGIN_X+4,INFO_START_Y+1);
		printf("���ı��ܹ���%d����",sum);
		 fclose(fp1);
		 fclose(fp2);
    }
}


void Release()  //�ͷ��ڴ�
{

    if(NULL == pHeader)
    {
        return;
    }
    wordNode *pCurr = pHeader;
    while(NULL != pCurr)
    {
        pHeader = pCurr->pNext;
        delete pCurr;
        pCurr = pHeader;
    }
}

