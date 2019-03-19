#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define SEP "------------------------------------------------------------------------------"//界面的总宽度
#define COL 78
#define MARGIN_X 20             //左边距
#define MAP_START_Y 3           //开始y轴坐标
#define MAP_END_Y 11            //结束y轴坐标
#define INFO_START_Y 12         //信息界面开始的Y坐标
#define INFO_END_Y 19           //信息界面结束的Y坐标

void SetPosition(int x,int y);
/*从x行，y列开始清rowcount行*/
void Clear(int x,int y,int rowcount);
/*设置文字的前景色，和背景色*/
void SetColor(int froeColor,int bankColor);
void Clear(int x,int y,int rowcount)
{

    //每行清除78个字符——每行打印78个空格
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
    HANDLE winHandle;   //句柄
    COORD pos = {x,y};
    winHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    //设置光标的坐标
    SetConsoleCursorPosition(winHandle,pos);
}
void SetColor(int foreColor,int bankColor)
{
    HANDLE winHandle;   //句柄
    winHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    //设置文字颜色
    SetConsoleTextAttribute(winHandle,foreColor+bankColor*0x10);
}



const int WORD_LENGTH = 256;          //使用const int 比用define要好
int FREQUENCY_COUNT=7;	              //用户指定统计词的频数
struct wordNode
{
    char word[WORD_LENGTH];          //存放单词
    int iWordCount;                  //单词出现次数
	wordNode *pNext;                 //结构体的指针
};

wordNode *pHeader = NULL;            //链表的头指针

//声明需要的函数
void CountWord(char *current);
wordNode * SearchWord(char *current);
void PrintResult();
void Release();

int k=1;
int main()
{
    char temp[WORD_LENGTH]; //临时存放单词的词组
    int k=1;    //用于while循环体，形成死循环
    FILE *fp; //打开要读取的文件
    if((fp=fopen("Breaking Dawn.txt", "r"))==NULL )
    {
        printf("Open file failed!!\n");
        exit(1);
    }
        while( EOF != (fscanf(fp,"%s",temp)) )//循环读取文本中的内容
    {
        CountWord(temp);
    }
       fclose(fp); //关闭文件

       while(k)
        {
            PrintResult(); //输出统计结果;
        }
        system("pause");

   	   Release(); //释放内存，养成好习惯
}
int i=1;
void CountWord(char *current)//单词统计
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

wordNode * SearchWord(char *current)//查找单词所在节点
{

    if( NULL == pHeader) //当链表为空的时候，也就统计第一个单词时
    {
        pHeader = new wordNode;
        strcpy(pHeader->word, current);
        pHeader->iWordCount = 0;
        pHeader->pNext = NULL;
        return pHeader;
    }

    //搜索现有的链表
    wordNode *pCurr = pHeader;
    wordNode *pPre = NULL;
    while( (NULL != pCurr) && (0 != strcmp(pCurr->word, current)) )
    {
        pPre = pCurr;
        pCurr = pCurr->pNext;
    }

    if(NULL == pCurr) //该单词不存在
    {
        pCurr = new wordNode;
        strcpy(pCurr->word, current);
        pCurr->iWordCount = 0;
        pCurr->pNext = NULL;
        pPre->pNext = pCurr;
    }
    return pCurr;
}

void PrintResult()//输出结果
{
    int num;
    void view();
    void help();
    void findk();
    void show();
    void print();
    SetColor(4,14);//更改当前文字的颜色的背景色
    SetColor(10,0);//打印完返回默认地图颜色
    SetPosition(MARGIN_X,0);
    printf("%s\n",SEP);
    SetPosition(MARGIN_X,1);
    printf("|");
    SetPosition(MARGIN_X+25,1);
    printf("欢迎来到《文本词频统计系统》\n");
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
            SetColor(4,14);//更改当前文字的颜色的背景色
            SetColor(10,0);//打印完返回默认地图颜色
        }
        SetPosition(MARGIN_X+77,3+i);
        printf("|");
    }
    SetPosition(MARGIN_X,MAP_END_Y);
    printf(SEP);

    SetPosition(MARGIN_X+30,MAP_START_Y);
    printf("系统功能菜单");
    SetPosition(MARGIN_X+25,MAP_START_Y+2);
    printf("1.系统帮助及说明");
    SetPosition(MARGIN_X+25,MAP_START_Y+3);
    printf("2.显示该文本所有单词词频信息");
    SetPosition(MARGIN_X+25,MAP_START_Y+4);
    printf("3.查找大于输入次数的单词词频");
    SetPosition(MARGIN_X+25,MAP_START_Y+5);
    printf("4.统计本文共有单词数量");
    SetPosition(MARGIN_X+25,MAP_START_Y+6);
    printf("5.退出词频系统");
    SetPosition(MARGIN_X+25,MAP_START_Y+7);
	printf("请选择菜单编号:");
	scanf("%d",&num);
	switch(num)     /*利用switch分支结构调用各部分功能函数*/
	{
	case 1:help();break;
	case 2:view();break;
	case 3:findk();break;
	case 4:show();break;
	case 5:
	    Clear(MARGIN_X,INFO_START_Y,20);
	    SetPosition(MARGIN_X+30,INFO_START_Y+5);
	    printf("感谢您的使用，下次再回！！！");exit(0);break;
	default:printf("请在1-6之间选择\n");
	}
}
help()  //帮助信息
{
    SetPosition(MARGIN_X+10,INFO_START_Y);
    printf("欢迎使用系统帮助!");
    SetPosition(MARGIN_X,INFO_START_Y+1);
	printf("1.初次进入系统后,请先选择增您想要的功能!");
	SetPosition(MARGIN_X,INFO_START_Y+2);
	printf("2.按照菜单提示键入数字代号");
	SetPosition(MARGIN_X,INFO_START_Y+3);
	printf("3.选择二号和三号查询之后系统会自动读出查询结果");
	SetPosition(MARGIN_X,INFO_START_Y+4);
	printf("4.二号选项读出的是该文本所有的词汇及其频数");
	SetPosition(MARGIN_X,INFO_START_Y+5);
	printf("5.三号选项读出的是大于等于用户输入频数的单词");
	SetPosition(MARGIN_X,INFO_START_Y+6);
	printf("6.谢谢您的使用，祝您使用愉快!");
}

view()  //查询单词词频信息
{
    //1,清除信息窗口的信息
    Clear(MARGIN_X,INFO_START_Y,7);
    int sum=0;
    int i=0;
    FILE* fp1=fopen("out_all_word_frequency.txt", "w");
    FILE* fp2=fopen("out_high_frequency.txt","w");
    if(NULL == pHeader)
    {
        printf("该文件为空!\n");
    }
    else
    {
        wordNode *pCurr = pHeader;
        //1,清除信息窗口的信息
        Clear(MARGIN_X,INFO_START_Y,7);
        while(NULL != pCurr)
        {
	    	fprintf(fp1,"%s\t%d\n", pCurr->word, pCurr->iWordCount);
            SetPosition(MARGIN_X,INFO_START_Y+i);
            printf("%-20s出现的次数:%d", pCurr->word, pCurr->iWordCount);
            SetPosition(MARGIN_X+36,INFO_START_Y+i);
            printf("|");
            sum=sum+pCurr->iWordCount;
            if(pCurr->iWordCount>=FREQUENCY_COUNT)
                fprintf(fp2,"%s\t%d\n", pCurr->word, pCurr->iWordCount);
			pCurr = pCurr->pNext;
			SetPosition(MARGIN_X+40,INFO_START_Y+i);
            printf("%-20s出现的次数:%d", pCurr->word, pCurr->iWordCount);
            pCurr = pCurr->pNext;
			i+=1;
        }
		printf("\n总共有%d个词",sum);
		 fclose(fp1);
		 fclose(fp2);
    }

}
findk()     //查找大于出入次数的单词
{
    int wordcount;
    //1,清除信息窗口的信息
    Clear(MARGIN_X,INFO_START_Y,50);
    wordNode *pCurr = pHeader;
    //1,清除信息窗口的信息
    Clear(MARGIN_X,INFO_START_Y,i);

    FILE* fp3=fopen("input_frequency.txt","w");

    if(NULL == pHeader)
    {
        printf("该文件为空!\n");
    }
    else
    {
        wordNode *pCurr = pHeader;
        SetPosition(MARGIN_X+20,INFO_START_Y+1);
        printf("请输入您要查询的频次：");
        scanf("%d",&FREQUENCY_COUNT);
        int k=3;
        while(NULL != pCurr)
        {

			if(pCurr->iWordCount >= FREQUENCY_COUNT)
               {
                   SetPosition(MARGIN_X+10,INFO_START_Y+k);
                    printf("|");
                    SetPosition(MARGIN_X+20,INFO_START_Y+k);
                    printf("%-10s出现的次数:%d", pCurr->word, pCurr->iWordCount);
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
show()      //显示全部此单词信息
{
    //1,清除信息窗口的信息
    Clear(MARGIN_X,INFO_START_Y,7);
    int wordcount,worder=0;
    int sum=0;
    FILE* fp1=fopen("out_all_word_frequency.txt", "w");
    FILE* fp2=fopen("out_high_frequency.txt","w");
    if(NULL == pHeader)
    {
        printf("该文件为空!\n");
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
		printf("该文本总共有%d个词",sum);
		 fclose(fp1);
		 fclose(fp2);
    }
}


void Release()  //释放内存
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

