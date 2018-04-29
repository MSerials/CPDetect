 #include "stdafx.h"
#include "MserialsUIQt.h"
#include <QtWidgets/QApplication>
//#include "QtFunctionListView.h"
#include "qformlayout.h"
#include "Ini.h"
#include "Machine.h"
#include "MSerialsCam.h"


#include <iostream>
#include <stack>
//一个栈可能所有出栈的序列
using namespace std;



int main(int argc, char *argv[])
{
	//初始化顺序
	//1参数 2硬件 3界面

	//项目配置文件
	Preference::GetIns()->sys->SetFilePos(QString("sys.ini"));
	QString Path = Preference::GetIns()->sys->para.Project_Name + "/prj.ini";
	Preference::GetIns()->prj->SetFilePos(Path);
	QDir d; d.mkdir("DL");
	//单例模式判断后才能进行硬件的初始化，否则可能打架
	Machine::GetIns()->MachineName();
	QApplication a(argc, argv);
	//系统配置文件
	MserialsUIQt w;
	w.show();
	//初始化界面
	w.OnInitDiaog();

	//程序结构不太好，导致耦合度太高，这个地方才能启动machine的线程
	Machine::GetIns()->Start();
	return a.exec();
}



static int counter = 0;
void outprint(stack<int> q) {
	while (q.size() != 0) {
		cout << q.top() << "-> ";
		q.pop();
	}
	cout << endl;
	counter++;
	return;
}
//q 存放入栈序列
//stk 用于模拟入栈过程
//output 用于存放可能的出栈序列
void allPopSeq(stack<int> q, stack<int> stk, stack<int> output) {
	if ((q.size() == 0) && (stk.size() == 0) && (output.size() == 5)) {
		outprint(output);
		return;
	}
	if (q.size() != 0) {//入栈
		int v = q.top();
		stk.push(v);
		q.pop();
		allPopSeq(q, stk, output);
		stk.pop();
		q.push(v);//回溯恢复
	}
	if (stk.size() != 0) //出栈
	{
		int v = stk.top();
		stk.pop();
		output.push(v);
		allPopSeq(q, stk, output);
		output.pop();
		stk.push(v);//回溯恢复
	}
	return;
}
void test() {
	int arr[5] = { 1,2,3,4,5 };
	stack<int> stkValues;
	stack<int> stkOutput;
	stack<int> tmp;
	int i;
	for (i = 0; i != 5; ++i) {
		stkValues.push(arr[i]);
	}
	allPopSeq(stkValues, tmp, stkOutput);
	cout << counter << endl;
}

