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


//每个非终结符表达式都表示一个文法规则，每个文法规则又只关心周边文法规则的结果，所以就会有递归调用而存在
//非终结符表达式
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
		//核心支出在于这里。。进行文法处理，并且产生递归调用
		//if(typeid().name() != "TerminalExpression")
		//递归调用
		//文法处理
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
			//进行语法判断，并且产生递归调用
			st.push(new TerminalExpression());
			st.push(new NonterminalExpression(new TerminalExpression()));
		}
		//for (int i = 0; i < 5; ++i)
		//{
		//    //进行语法判断，并且产生递归调用
		//    st.push(new NonterminalExpression(new TerminalExpression()));
		//    st.push(new TerminalExpression());
		//}
		//产生一个完整的语法树，由各个具体的语法分析进行解析
		Expression *exp = st.top();
		exp->interpreter(ctx);
	}
};



#endif