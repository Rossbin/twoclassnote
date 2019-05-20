#include <iostream>
#include<cstdlib>
#include<ctime> 
#define Bsize 2          //�û��ڴ�ռ�
using namespace std;
struct BLOCK                 //�����ṹ��
{
	int pagenum = -1;    //ҳ��
	int next_instruction = 0;  //ָ���Ȩ��
	int time = 0;     //LFU�㷨�еĴ���
};

int counte;						 //�����������������¼��ǰָ������
int n;						    //ȱҳ��������������¼ȱҳ�Ĵ���	
int m;						   //�û���������������¼�û��Ĵ���
int temp[320];  //�����洢320�������
BLOCK block[Bsize]; //����һ��СΪ2�����������
void init();//��ʼ������ 
int findExist(int curpage);//������������Ƿ��и�ҳ��
int findSpace();//�����Ƿ��п��������
int findReplace();//����Ӧ���û���ҳ��
void display();//��ʾ
void random();//����320�������,��ʾ���洢��temp[320]
void pagestring();//��ʾ���õ�ҳ�����
void FIFO();
void LRU();
void OPT();
void LFU();
void init()      //�ڴ��ʼ��
{
	for (int i = 0; i < Bsize; i++)
	{
		block[i].pagenum = -1;
		block[i].next_instruction = 0;
		block[i].time = 0;
		counte = n = m = 0;
	}
}


int findExist(int curpage)     //������������Ƿ��и�ҳ��
{

	for (int i = 0; i < Bsize; i++)
	{
		if (block[i].pagenum == curpage)
			return i;                     //��⵽�ڴ����и�ҳ�棬����block�е�λ��
	}
	return -1;
}


int findSpace()                        //�����Ƿ��п��������
{
	for (int i = 0; i < Bsize; i++)
	{
		if (block[i].pagenum == -1)
			return i;    //�ҵ����е�block������block�е�λ��
	}

	return -1;

}


int findReplace()                  //����Ӧ���û���ҳ��
{
	int pos = 0;
	for (int i = 0; i < Bsize; i++)
	{
		if (block[i].next_instruction > block[pos].next_instruction)
			pos = i;//�ҵ�Ӧ���û�ҳ�棬����BLOCK��λ��
	}
	return pos;
}

int findlfu()      //����LFU�еķ��ʴ������ٵ�
{
	int pos = 0;
	for (int i = 0; i < Bsize; i++) {
		if (block[i].time < block[pos].time)
			pos = i;
	}
	return pos;
}

void display() //��ӡ�ĸ�����ҳ�� 
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


void random()                  //����320�������,��ʾ���洢��temp[320]
{
	int flag = 0;
	srand((unsigned)time(NULL)); //ϵͳʱ��Ϊ��������� 
	counte = rand() % 320;
	cout << "******����Ҫ�������320���������*******" << endl;
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


void pagestring()               //��ʾ���õ�ҳ�����
{
	for (int i = 0; i < 320; i++)
	{
		printf(" %4d", temp[i] / 10+1);
		if ((i + 1) % 10 == 0) cout << endl;
	}

}
//�Ƚ��ȳ��û��㷨
void FIFO()
{
	int exist, space, replace;
	int curpage;
	for (int i = 0; i < 320; i++)
	{

		counte = temp[i];
		curpage = counte / 10 + 1;
		exist = findExist(curpage);   //Ѱ�Ҹ�ָ���Ƿ����ڴ���
		if (exist == -1)            //�����ڴ��� 
		{
			n++;                  //ȱҳ
			space = findSpace();   //Ѱ���Ƿ��п��������
			if (space != -1)        //�п��е������ 
			{
				block[space].pagenum = curpage;
				display();

			}
			else                    //�û� 
			{
				replace = findReplace();
				block[replace].pagenum = curpage;
				m++;
				block[replace].next_instruction = 0;
				display();

			}
		}

		for (int j = 0; j < Bsize; j++)
			block[j].next_instruction++; //���ӵ�һ��ָ���Ȩ�� 

	}
	cout << "ȱҳ����:" << n << endl;
	cout << "�û�������" << m << endl;
	cout << "ȱҳ��:" << (n / 320.0) * 100 << "%" << endl;
}

//����ʱ��δ�����û��㷨
void LRU()
{
	int exist, space, replace;
	int curpage;
	for (int i = 0; i < 320; i++)
	{

		counte = temp[i];
		curpage = counte / 10 + 1;
		exist = findExist(curpage);     //Ѱ�����ڴ����Ƿ��и�ָ��
		if (exist == -1)
		{
			n++;                   //���ڴ���û�и�ָ�ȱҳ
			space = findSpace();   //�ڴ����Ƿ��п��������
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
		for (int j = 0; j < Bsize; j++) //δʹ��ҳ���Ȩ��ÿ�μ�һ,�Ա���֮����û�
		{
			if (j == exist) continue;
			block[j].next_instruction++;
		}
	}

	cout << "ȱҳ����:" << n << endl;
	cout << "�û�������" << m << endl;
	cout << "ȱҳ��:" << (n / 320.0) * 100 << "%" << endl;
}

//����û��㷨
void OPT()
{
	int exist, space, replace;
	int curpage;
	for (int i = 0; i < 320; i++)
	{

		counte = temp[i];
		curpage = counte / 10+1;
		exist = findExist(curpage);       //���ڴ�����curpage
		if (exist == -1)   //ȱҳ 
		{
			n++;
			space = findSpace();
			if (space != -1)  //�ҵ���ȱ���ڴ������ 
			{
				block[space].pagenum = curpage;
				display();

			}
			else     //ҳ���û� 
			{
				for (int k = 0; k < Bsize; k++)
				{
					for (int j = i; j < 320; j++)          //�������Ƿ����и�ָ�����
					{
						if (block[k].pagenum != temp[j] / 10)       //��ָ���ں���ָ��������δ���֣��򽫸�ָ���Ȩ�ظ�Ϊ���
						{
							block[k].next_instruction = 1000; 
						}                                            
						else
						{
							block[k].next_instruction = j;    //�������ָ�����֣��򽫸�ָ���Ȩ�ظ�Ϊ���ֵ�����λ����
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
			//display();   //��ʾδȱҳ
		}
	}
	cout << "ȱҳ����:" << n << endl;
	cout << "�û�������" << m << endl;
	cout << "ȱҳ��:" << (n / 320.0) * 100 << "%" << endl;
}

//�����������û��㷨
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
	cout << "ȱҳ����:" << n << endl;
	cout << "�û�������" << m << endl;
	cout << "ȱҳ��:" << (n / 320.0) * 100 << "%" << endl;
}
int main()
{
	int select;
	random();
	cout << "**************** �㷨 ******************" << endl;
	pagestring();
	do
	{
		cout << "****************************************" << endl;
		cout << "------1:FIFO  0:�˳�-----" << endl;
		cout << "------2:LRU   0:�˳�-----" << endl;
		cout << "------3:OPT   0:�˳�-----" << endl;
		cout << "------4:LFU   0:�˳�-----" << endl;
		cout << "****************************************" << endl;
		cout << " ��ѡ��һ��ҳ���û��㷨: ";
		cin >> select;
		cout << "****************************************" << endl;

		init();
		switch (select)
		{
		case 1:	cout << "�Ƚ��ȳ��û��㷨FIFO:" << endl;
			cout << "**************************" << endl;
			FIFO();
			break;
		case 2:	cout << "������δʹ���û��㷨LRU:" << endl;
			cout << "**************************" << endl;
			LRU();
			break;
		case 3:	 cout << "����û��㷨OPT:" << endl;
			cout << "**************************" << endl;
			OPT();
			break;
		case 4: cout << "���ٴ��������㷨LFU:" << endl;
			cout << "**************************" << endl;
			LFU();
			break;
		default:;
		}

	} while (select != 0);
	return 0;
}
