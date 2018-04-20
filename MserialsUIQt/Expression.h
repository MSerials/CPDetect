#pragma once


/*




client	-------->	context
|
------->	AbstractExpression<-------
+Interpret()			|
^					|
|					|
--------------------|
|					|
TerminallExpression		NonterminalExpress




*/


#include <stack>
#include <iostream>
#include "../../QtCommon/common.h"
using namespace std;
class Object;
class Context;
















#ifndef _________EXPRESSION___________
#define _________EXPRESSION___________

#include <map>
#include <string>
using namespace std;



class Context
{
private:
	map<string, int> valueMap;

};


class Expression
{
	
private:
	map<string, int> valueMap;


public:
	Expression();
	~Expression();


	virtual Object* interpreter(Context *ctx) = 0
	{
		cout << "Express interpreter is NULL" << endl;
		DLOG(LOG_INFO, "Express interpreter is NULL");
		return NULL;
	}
};

class TerminalExpression :public Expression
{
	Object * interpreter(Context* ctx)
	{
		cout << "TerminalExpression::interprter" << endl;
		DLOG(LOG_INFO, "TerminalExpression::interpreter");
		return NULL;
	}

};


//ÿ�����ս�����ʽ����ʾһ���ķ�����ÿ���ķ�������ֻ�����ܱ��ķ�����Ľ�������Ծͻ��еݹ���ö�����
//���ս�����ʽ
class NonterminalExpression :public Expression
{
public:
	NonterminalExpression(Expression* x1, ...)
	{
		for (int i = 0; i < 4; ++i)
		{
			_st.push(x1);
		}
	}
	Object *interpreter(Context*ctx)
	{
		//����֧����������������ķ��������Ҳ����ݹ����
		//if(typeid().name() != "TerminalExpression")
		//�ݹ����
		//�ķ�����
		while (!_st.empty())
		{
			Expression* tp = _st.top();
			_st.pop();
			cout << "NoterminalExpression::interpreter" << endl;
			DLOG(LOG_INFO, "NoterminalExpression::interpreter");
			tp->interpreter(ctx);
		}
		return NULL;
	}
private:
	stack <Expression*> _st;
};



class Client
{
public:
	void operator()()
	{
		Context *ctx = new Context();
		stack<Expression*> st;
		for (int i = 0; i < 5; ++i)
		{
			//�����﷨�жϣ����Ҳ����ݹ����
			st.push(new TerminalExpression());
			st.push(new NonterminalExpression(new TerminalExpression()));
		}
		//for (int i = 0; i < 5; ++i)
		//{
		//    //�����﷨�жϣ����Ҳ����ݹ����
		//    st.push(new NonterminalExpression(new TerminalExpression()));
		//    st.push(new TerminalExpression());
		//}
		//����һ���������﷨�����ɸ���������﷨�������н���
		Expression *exp = st.top();
		exp->interpreter(ctx);
	}
};



#endif