#include<iostream>
#include<Windows.h>
using namespace std;
const int n = 5, m = 3;    //5�����̺�3����Դ

int Max[n][m] = { {7,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3} };         //ÿ�����������Դ��ʼ��
int Need[n][m] = { {7,4,3},{1,2,2},{6,0,0},{0,1,1},{4,3,1} };        //ÿ�����̻�����Դ��ʼ��
int Allocation[n][m] = { {0,1,0},{2,0,0},{3,0,2},{2,1,1},{0,0,2} };  //ÿ�������ѷ�����Դ��ʼ��
int Available[m] = { 3,3,2 };                                        //������Դʣ��
int Request[m];
int Work[m];
int Seq[n];
//��ȫ���
bool Scurity()
{
	
	bool Finish[n];
	int y = 0;
	for (int i = 0; i < n; i++)  Finish[i] = false;

	for (int i=0; i < m; i++) {
		Work[i] = Available[i];
	}
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			if (Finish[i] == false && Need[i][0] <= Work[0] && Need[i][1] <= Work[1] && Need[i][2] <= Work[2]) {
				for (int j = 0; j < m; j++) {
					Work[j] = Work[j] + Allocation[i][j];
				}
				Finish[i] = true;
				Seq[y] = i;
				y++;
				break;
			}
			else continue;
		}
	}
	//��ȫ���е����

	if (Finish[4] == true) 
	{
		Sleep(700);
		cout << endl<<"ͨ����ȫ���"<<endl<<"��ȫ����Ϊ�� " << endl;
		
		for (int l = 0; l < n - 1; l++) {
			if (Finish[l] == true) {
				cout << "P" << Seq[l];
				cout << "--->";
			}

		}
		cout << "P" << Seq[4] << endl;
		return 1;
	}
	else {
		cout <<endl<<"�ް�ȫ���У�������Σ�գ����� ���������롣" << endl;

		return 0;
	}
}
void Banker(int c)
{
	if (Need[c][0] >= Request[0] && Need[c][1] >= Request[1] && Need[c][2] >= Request[2]) {     //�ж������Ƿ��������
		if (Request[0] <= Available[0] && Request[1] <= Available[1] && Request[2] <= Available[2]) {   //�ж������Ƿ���ڿɷ���
			cout << "���Է�����Դ�У�����" << endl;
			for (int j = 0; j < m; j++) {
				//�Է���
				Available[j] = Available[j] - Request[j];
				Allocation[c][j] = Allocation[c][j] + Request[j];
				Need[c][j] = Need[c][j] - Request[j];
			}
			if (Scurity() == 1) {
				cout <<endl<< "�������ڷ��䣡" << endl;

			}
			else {
				cout << "�ѽ����ݸ�ԭ��" << endl;
				for (int j = 0; j < m; j++) {
					Available[j] = Available[j] + Request[j];
					Allocation[c][j] = Allocation[c][j] - Request[j];
					Need[c][j] = Need[c][j] + Request[j];
				}
			}
		}
		else cout << "���������Դ�����ڿɷ������Դ�������� ���������룡" << endl;
	}
	else cout << "���������Դ��������Ҫ����Դ�������� ���������룡��" << endl;
}



int main()
{
	int b = 0;
	cout << "���ڽ���ϵͳ��..." << endl;
	Sleep(1000);
	cout << "�ѽ���ϵͳ��" << endl;
	do
	{
		Sleep(700);
		cout <<endl<< "Max����" << endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				cout << Max[i][j] << "  ";
			}
			cout << endl;
		}
		cout << "Allocation����" << endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				cout << Allocation[i][j] << "  ";
			}
			cout << endl;
		}
		cout << "Need����" << endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				cout << Need[i][j] << "  ";
			}
			cout << endl;
		}
		cout << "Available����" << endl;
		for (int i = 0; i < m; i++) {
			cout << Available[i] << "  ";
		}
		cout << endl;
		int PID;
		//����ǰ���а�ȫ�ж�
		if (Scurity() == 1) {}
		cout << endl << "������Ҫ�޸ĵĽ��̣�1-5���� ";
		cin >> PID;
		cout << "������������Դ����ʽΪ1 2 3��: ";
		cin >> Request[0] >> Request[1] >> Request[2];
		int h = PID - 1;
		Banker(h);
		Sleep(1000);
		cout << endl <<"��������ɣ�" << endl;
		cout<<"������(����1����������0�˳�):  ";
		
		cin >> b;
	} while (b>0);
	system("pause");
	return 0;
}