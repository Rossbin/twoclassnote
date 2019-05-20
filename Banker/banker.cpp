#include<iostream>
#include<Windows.h>
using namespace std;
const int n = 5, m = 3;    //5个进程和3类资源

int Max[n][m] = { {7,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3} };         //每个进程最大资源初始化
int Need[n][m] = { {7,4,3},{1,2,2},{6,0,0},{0,1,1},{4,3,1} };        //每个进程还需资源初始化
int Allocation[n][m] = { {0,1,0},{2,0,0},{3,0,2},{2,1,1},{0,0,2} };  //每个进程已分配资源初始化
int Available[m] = { 3,3,2 };                                        //各类资源剩余
int Request[m];
int Work[m];
int Seq[n];
//安全检测
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
	//安全序列的输出

	if (Finish[4] == true) 
	{
		Sleep(700);
		cout << endl<<"通过安全检测"<<endl<<"安全序列为： " << endl;
		
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
		cout <<endl<<"无安全序列，请求有危险！！！ 请重新输入。" << endl;

		return 0;
	}
}
void Banker(int c)
{
	if (Need[c][0] >= Request[0] && Need[c][1] >= Request[1] && Need[c][2] >= Request[2]) {     //判定请求是否大于所需
		if (Request[0] <= Available[0] && Request[1] <= Available[1] && Request[2] <= Available[2]) {   //判定请求是否大于可分配
			cout << "尝试分配资源中！！！" << endl;
			for (int j = 0; j < m; j++) {
				//试分配
				Available[j] = Available[j] - Request[j];
				Allocation[c][j] = Allocation[c][j] + Request[j];
				Need[c][j] = Need[c][j] - Request[j];
			}
			if (Scurity() == 1) {
				cout <<endl<< "请求正在分配！" << endl;

			}
			else {
				cout << "已将数据复原！" << endl;
				for (int j = 0; j < m; j++) {
					Available[j] = Available[j] + Request[j];
					Allocation[c][j] = Allocation[c][j] - Request[j];
					Need[c][j] = Need[c][j] + Request[j];
				}
			}
		}
		else cout << "所请求的资源数大于可分配的资源数！！！ 请重新输入！" << endl;
	}
	else cout << "所请求的资源大于所需要的资源数！！！ 请重新输入！！" << endl;
}



int main()
{
	int b = 0;
	cout << "正在进入系统中..." << endl;
	Sleep(1000);
	cout << "已进入系统。" << endl;
	do
	{
		Sleep(700);
		cout <<endl<< "Max矩阵" << endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				cout << Max[i][j] << "  ";
			}
			cout << endl;
		}
		cout << "Allocation矩阵" << endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				cout << Allocation[i][j] << "  ";
			}
			cout << endl;
		}
		cout << "Need矩阵" << endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				cout << Need[i][j] << "  ";
			}
			cout << endl;
		}
		cout << "Available矩阵" << endl;
		for (int i = 0; i < m; i++) {
			cout << Available[i] << "  ";
		}
		cout << endl;
		int PID;
		//请求前进行安全判定
		if (Scurity() == 1) {}
		cout << endl << "请输入要修改的进程（1-5）： ";
		cin >> PID;
		cout << "请输入请求资源（格式为1 2 3）: ";
		cin >> Request[0] >> Request[1] >> Request[2];
		int h = PID - 1;
		Banker(h);
		Sleep(1000);
		cout << endl <<"分配已完成！" << endl;
		cout<<"请输入(输入1继续，输入0退出):  ";
		
		cin >> b;
	} while (b>0);
	system("pause");
	return 0;
}