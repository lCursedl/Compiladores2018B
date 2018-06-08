#include "stdafx.h"
#include "Token.h"

Compiler_Project_2018B::CToken::CToken(std::string lex, TOKEN_TYPE t, int LineN)
{
}

std::string Compiler_Project_2018B::CToken::GetLex()
{
	return m_Lexema;
}

Compiler_Project_2018B::TOKEN_TYPE Compiler_Project_2018B::CToken::getTokenType()
{
	return m_Type;
}

int Compiler_Project_2018B::CToken::GetLineNum()
{
	return LineNum;
}

void Compiler_Project_2018B::CToken::AddLineNum()
{
	LineNum++;
}