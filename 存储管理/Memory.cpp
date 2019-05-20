#include <iostream>
#include<cstdlib>
#include<ctime> 
#define Bsize 2          //用户内存空间
using namespace std;
struct BLOCK                 //物理块结构体
{
	int pagenum = -1;    //页号
	int next_instruction = 0;  //指令的权重
	int time = 0;     //LFU算法中的次数
};

int counte;						 //程序计数器，用来记录当前指令的序号
int n;						    //缺页计数器，用来记录缺页的次数	
int m;						   //置换计数器，用来记录置换的次数
int temp[320];  //用来存储320条随机数
BLOCK block[Bsize]; //定义一大小为2的物理块数组
void init();//初始化函数 
int findExist(int curpage);//查找物理块中是否有该页面
int findSpace();//查找是否有空闲物理块
int findReplace();//查找应予置换的页面
void display();//显示
void random();//产生320条随机数,显示并存储到temp[320]
void pagestring();//显示调用的页面队列
void FIFO();
void LRU();
void OPT();
void LFU();
void init()      //内存初始化
{
	for (int i = 0; i < Bsize; i++)
	{
		block[i].pagenum = -1;
		block[i].next_instruction = 0;
		block[i].time = 0;
		counte = n = m = 0;
	}
}


int findExist(int curpage)     //查找物理块中是否有该页面
{

	for (int i = 0; i < Bsize; i++)
	{
		if (block[i].pagenum == curpage)
			return i;                     //检测到内存中有该页面，返回block中的位置
	}
	return -1;
}


int findSpace()                        //查找是否有空闲物理块
{
	for (int i = 0; i < Bsize; i++)
	{
		if (block[i].pagenum == -1)
			return i;    //找到空闲的block，返回block中的位置
	}

	return -1;

}


int findReplace()                  //查找应予置换的页面
{
	int pos = 0;
	for (int i = 0; i < Bsize; i++)
	{
		if (block[i].next_instruction > block[pos].next_instruction)
			pos = i;//找到应予置换页面，返回BLOCK中位置
	}
	return pos;
}

int findlfu()      //查找LFU中的访问次数最少的
{
	int pos = 0;
	for (int i = 0; i < Bsize; i++) {
		if (block[i].time < block[pos].time)
			pos = i;
	}
	return pos;
}

void display() //打印四个块中页号 
{
	for (int i = 0; i < Bsize; i++)
	{
		if (block[i].pagenum != -1)
		{
			printf(" %4d", block[i].pagenum);
		}
	}
	cout << endl;
}


void random()                  //产生320条随机数,显示并存储到temp[320]
{
	int flag = 0;
	srand((unsigned)time(NULL)); //系统时间为随机数种子 
	counte = rand() % 320;
	cout << "******按照要求产生的320个随机数：*******" << endl;
	for (int i = 0; i < 320; i++)
	{
		temp[i] = counte;
		if (flag % 2 == 0) counte = ++counte % 320;
		if (flag == 1) counte = rand() % (counte - 1);
		if (flag == 3) counte = counte + 1 + (rand() % (320 - (counte + 1)));
		flag = ++flag % 4;
		printf(" %4d", temp[i]);
		if ((i + 1) % 10 == 0) cout << endl;
	}
}


void pagestring()               //显示调用的页面队列
{
	for (int i = 0; i < 320; i++)
	{
		printf(" %4d", temp[i] / 10+1);
		if ((i + 1) % 10 == 0) cout << endl;
	}

}
//先进先出置换算法
void FIFO()
{
	int exist, space, replace;
	int curpage;
	for (int i = 0; i < 320; i++)
	{

		counte = temp[i];
		curpage = counte / 10 + 1;
		exist = findExist(curpage);   //寻找该指令是否在内存中
		if (exist == -1)            //不在内存中 
		{
			n++;                  //缺页
			space = findSpace();   //寻找是否有空余物理块
			if (space != -1)        //有空闲的物理块 
			{
				block[space].pagenum = curpage;
				display();

			}
			else                    //置换 
			{
				replace = findReplace();
				block[replace].pagenum = curpage;
				m++;
				block[replace].next_instruction = 0;
				display();

			}
		}

		for (int j = 0; j < Bsize; j++)
			block[j].next_instruction++; //增加第一个指令的权重 

	}
	cout << "缺页次数:" << n << endl;
	cout << "置换次数：" << m << endl;
	cout << "缺页率:" << (n / 320.0) * 100 << "%" << endl;
}

//最近最长时间未访问置换算法
void LRU()
{
	int exist, space, replace;
	int curpage;
	for (int i = 0; i < 320; i++)
	{

		counte = temp[i];
		curpage = counte / 10 + 1;
		exist = findExist(curpage);     //寻找在内存中是否有该指令
		if (exist == -1)
		{
			n++;                   //在内存中没有该指令，缺页
			space = findSpace();   //内存中是否有空余物理块
			if (space != -1)
			{
				block[space].pagenum = curpage;
				display();
			}
			else
			{
				replace = findReplace();
				block[replace].pagenum = curpage;
				m++;
				display();
			}
		}
		else block[exist].next_instruction = 0;
		for (int j = 0; j < Bsize; j++) //未使用页面的权重每次加一,以便于之后的置换
		{
			if (j == exist) continue;
			block[j].next_instruction++;
		}
	}

	cout << "缺页次数:" << n << endl;
	cout << "置换次数：" << m << endl;
	cout << "缺页率:" << (n / 320.0) * 100 << "%" << endl;
}

//最佳置换算法
void OPT()
{
	int exist, space, replace;
	int curpage;
	for (int i = 0; i < 320; i++)
	{

		counte = temp[i];
		curpage = counte / 10+1;
		exist = findExist(curpage);       //在内存中找curpage
		if (exist == -1)   //缺页 
		{
			n++;
			space = findSpace();
			if (space != -1)  //找到空缺的内存物理块 
			{
				block[space].pagenum = curpage;
				display();

			}
			else     //页面置换 
			{
				for (int k = 0; k < Bsize; k++)
				{
					for (int j = i; j < 320; j++)          //向后遍历是否再有该指令出现
					{
						if (block[k].pagenum != temp[j] / 10)       //该指令在后面指令序列中未出现，则将该指令的权重改为最大
						{
							block[k].next_instruction = 1000; 
						}                                            
						else
						{
							block[k].next_instruction = j;    //在最近该指令将会出现，则将该指令的权重改为出现的序列位置数
							break;

						}
					}
				}
				replace = findReplace();
				block[replace].pagenum = curpage;
				m++;
				display();
			}
		}
		else {
			block[exist].next_instruction = 0;
			//display();   //显示未缺页
		}
	}
	cout << "缺页次数:" << n << endl;
	cout << "置换次数：" << m << endl;
	cout << "缺页率:" << (n / 320.0) * 100 << "%" << endl;
}

//不经常访问置换算法
void LFU() {
	int exist, space, replace, curpage;
	for (int i = 0; i < 320; i++) {
		counte = temp[i];
		curpage = temp[i] / 10 + 1;
		exist = findExist(curpage);
		if (exist == -1) {
			n++;
			space = findSpace();
			if (space != -1) {
				block[space].pagenum = curpage;
				block[space].time++;
				display();
			}
			else {
				replace = findlfu();
				block[replace].pagenum = curpage;
				m++;
				block[replace].time = 0;
				display();
			}
		}
		else {
			for (int j = 0; j < Bsize; j++) {
				if (exist == j) {
					block[j].time++;
					continue;
				}
				block[j].time = block[j].time / 2;
			}
		}
	}
	cout << "缺页次数:" << n << endl;
	cout << "置换次数：" << m << endl;
	cout << "缺页率:" << (n / 320.0) * 100 << "%" << endl;
}
int main()
{
	int select;
	random();
	cout << "**************** 算法 ******************" << endl;
	pagestring();
	do
	{
		cout << "****************************************" << endl;
		cout << "------1:FIFO  0:退出-----" << endl;
		cout << "------2:LRU   0:退出-----" << endl;
		cout << "------3:OPT   0:退出-----" << endl;
		cout << "------4:LFU   0:退出-----" << endl;
		cout << "****************************************" << endl;
		cout << " 请选择一种页面置换算法: ";
		cin >> select;
		cout << "****************************************" << endl;

		init();
		switch (select)
		{
		case 1:	cout << "先进先出置换算法FIFO:" << endl;
			cout << "**************************" << endl;
			FIFO();
			break;
		case 2:	cout << "最近最久未使用置换算法LRU:" << endl;
			cout << "**************************" << endl;
			LRU();
			break;
		case 3:	 cout << "最佳置换算法OPT:" << endl;
			cout << "**************************" << endl;
			OPT();
			break;
		case 4: cout << "最少次数访问算法LFU:" << endl;
			cout << "**************************" << endl;
			LFU();
			break;
		default:;
		}

	} while (select != 0);
	return 0;
}
