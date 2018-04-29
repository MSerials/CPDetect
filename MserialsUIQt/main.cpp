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
//һ��ջ�������г�ջ������
using namespace std;



int main(int argc, char *argv[])
{
	//��ʼ��˳��
	//1���� 2Ӳ�� 3����

	//��Ŀ�����ļ�
	Preference::GetIns()->sys->SetFilePos(QString("sys.ini"));
	QString Path = Preference::GetIns()->sys->para.Project_Name + "/prj.ini";
	Preference::GetIns()->prj->SetFilePos(Path);
	QDir d; d.mkdir("DL");
	//����ģʽ�жϺ���ܽ���Ӳ���ĳ�ʼ����������ܴ��
	Machine::GetIns()->MachineName();
	QApplication a(argc, argv);
	//ϵͳ�����ļ�
	MserialsUIQt w;
	w.show();
	//��ʼ������
	w.OnInitDiaog();

	//����ṹ��̫�ã�������϶�̫�ߣ�����ط���������machine���߳�
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
//q �����ջ����
//stk ����ģ����ջ����
//output ���ڴ�ſ��ܵĳ�ջ����
void allPopSeq(stack<int> q, stack<int> stk, stack<int> output) {
	if ((q.size() == 0) && (stk.size() == 0) && (output.size() == 5)) {
		outprint(output);
		return;
	}
	if (q.size() != 0) {//��ջ
		int v = q.top();
		stk.push(v);
		q.pop();
		allPopSeq(q, stk, output);
		stk.pop();
		q.push(v);//���ݻָ�
	}
	if (stk.size() != 0) //��ջ
	{
		int v = stk.top();
		stk.pop();
		output.push(v);
		allPopSeq(q, stk, output);
		output.pop();
		stk.push(v);//���ݻָ�
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

