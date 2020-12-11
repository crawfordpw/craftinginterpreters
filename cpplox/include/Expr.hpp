#include <string>
#include "Token.hpp"

using namespace std;

class Expr {

	public: 

		virtual ~Expr() { }

};

class Binary : public Expr 
{
	public: 

		Binary(Expr Left, Token Operator, Expr Right)
			: mLeft(Left), mOperator(Operator), mRight(Right){ }

	private: 

		Expr mLeft;
		Token mOperator;
		Expr mRight;
};

class Grouping : public Expr 
{
	public: 

		Grouping(Expr Expression)
			: mExpression(Expression){ }

	private: 

		Expr mExpression;
};

class Literal : public Expr 
{
	public: 

		Literal(string Value)
			: mValue(Value){ }

	private: 

		string mValue;
};

class Unary : public Expr 
{
	public: 

		Unary(Token Operator, Expr Right)
			: mOperator(Operator), mRight(Right){ }

	private: 

		Token mOperator;
		Expr mRight;
};

