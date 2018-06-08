#pragma once
#include <string>

namespace Compiler_Project_2018B
{
	public enum class TOKEN_TYPE
	{
		UNDEFINED = 0,
		ID,
		INT,
		FLOAT,
		STRING,
		KEYWORD,
		RELATIONAL_OP,
		ARITHMETIC_OP,
		LOGICAL_OP,
		NEGATION_OP,
		SEPARATOR,
		ASSIGN,
		DIMENSION,
		GROUPING
	};

	public class CToken
	{
	private:
		std::string m_Lexema;
		TOKEN_TYPE m_Type;
		int LineNum;
	public:
		CToken(std::string lex, TOKEN_TYPE t, int LineN);
		std::string GetLex();
		TOKEN_TYPE getTokenType();
		int GetLineNum();
		void AddLineNum();
	};
}