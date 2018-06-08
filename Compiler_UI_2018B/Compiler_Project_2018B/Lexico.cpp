#include "stdafx.h"
#include "Lexico.h"

Compiler_Project_2018B::CLexico::CLexico(CErrorModule ^ err)
{
	m_Err = err;
	m_KeyWords.insert(std::make_pair("var", ""));
	m_KeyWords.insert(std::make_pair("int", ""));
	m_KeyWords.insert(std::make_pair("float", ""));
	m_KeyWords.insert(std::make_pair("bool", ""));
	m_KeyWords.insert(std::make_pair("string", ""));
	m_KeyWords.insert(std::make_pair("function", ""));
	m_KeyWords.insert(std::make_pair("main", ""));
	m_KeyWords.insert(std::make_pair("if", ""));
	m_KeyWords.insert(std::make_pair("else", ""));
	m_KeyWords.insert(std::make_pair("while", ""));
	m_KeyWords.insert(std::make_pair("for", ""));
	m_KeyWords.insert(std::make_pair("switch", ""));
	m_KeyWords.insert(std::make_pair("default", ""));
	m_KeyWords.insert(std::make_pair("return", ""));
	m_KeyWords.insert(std::make_pair("read", ""));
	m_KeyWords.insert(std::make_pair("print", ""));
	m_KeyWords.insert(std::make_pair("case", ""));
	m_KeyWords.insert(std::make_pair("void", ""));
}

bool Compiler_Project_2018B::CLexico::ParseCode(const char * src)
{
	int currentLine = 1;
	const char * currChar = src;
	const char * currLine = src;
	std::string tokenBuffer;
	bool used_point = false;
	m_State = LEX_STATE::START;
	ClearTokens();
	while (*currChar != '\0')
	{
		switch (m_State)
		{
		case LEX_STATE::START:
		{
			//Checking letter/underscore
			if (isalpha(*currChar) || *currChar == '_')
			{
				tokenBuffer.clear();
				tokenBuffer.append(currChar, 1);
				m_State = LEX_STATE::PARSING_ID;
				currChar++;
			}
			//Checking number
			else if (isdigit(*currChar))
			{
				tokenBuffer.clear();
				tokenBuffer.append(currChar, 1);
				m_State = LEX_STATE::PARSING_INT;
				currChar++;
			}
			//Cheking point
			else if (*currChar == '.')
			{
				tokenBuffer.clear();
				tokenBuffer.append(currChar, 1);
				m_State = LEX_STATE::PARSING_FLOAT;
				currChar++;
			}
			//Checking string
			else if (*currChar == '"')
			{
				tokenBuffer.clear();
				tokenBuffer.append(currChar, 1);
				m_State = LEX_STATE::PARSING_STRING;
				currChar++;
			}
			//Checking less than
			else if (*currChar == '<')
			{
				tokenBuffer.clear();
				tokenBuffer.append(currChar, 1);
				m_State = LEX_STATE::PARSING_LESS;
				currChar++;
			}
			//Checking more than
			else if (*currChar == '>')
			{
				tokenBuffer.clear();
				tokenBuffer.append(currChar, 1);
				m_State = LEX_STATE::PARSING_MORE;
				currChar++;
			}
			//Checking equals
			else if (*currChar == '=')
			{
				tokenBuffer.clear();
				tokenBuffer.append(currChar, 1);
				m_State = LEX_STATE::PARSING_EQUALS;
				currChar++;
			}
			//Checking negation
			else if (*currChar == '!')
			{
				tokenBuffer.clear();
				tokenBuffer.append(currChar, 1);
				m_State = LEX_STATE::PARSING_NOT;
				currChar++;
			}
			//Cheking groupers
			else if (*currChar == '(' || *currChar == ')' || *currChar == '[' || *currChar == ']' || *currChar == '{' || *currChar == '}')
			{
				tokenBuffer.clear();
				tokenBuffer.append(currChar, 1);
				CToken* T = new CToken(tokenBuffer, TOKEN_TYPE::GROUPING, currentLine);
				m_Tokens.push_back(T);
				currChar++;
			}
			//Checking separators
			else if (*currChar == ',' || *currChar == ';' || *currChar == ':')
			{
				tokenBuffer.clear();
				tokenBuffer.append(currChar, 1);
				CToken * T = new CToken(tokenBuffer, TOKEN_TYPE::SEPARATOR, currentLine);
			}
			//Checking log op AND
			else if (*currChar == '&')
			{
				tokenBuffer.clear();
				tokenBuffer.append(currChar, 1);
				currChar++;
				if (*currChar == '&')
				{
					tokenBuffer.append(currChar, 1);
					currChar++;
				}
				else
				{
					tokenBuffer.clear();
				}
			}
			//Checking log op OR
			else if (*currChar == '|')
			{
				tokenBuffer.clear();
				tokenBuffer.append(currChar, 1);
				currChar++;
				if (*currChar == '|')
				{
					tokenBuffer.append(currChar, 1);
					currChar++;
				}
				else
				{
					tokenBuffer.clear();
				}
			}
			//Checking aritmetic op
			else if (*currChar == '+' || *currChar == '-' || *currChar == '*' || *currChar == '/')
			{
				tokenBuffer.clear();
				tokenBuffer.append(currChar, 1);
				m_State = LEX_STATE::PARSING_ARITMETHIC_OP;
			}
			//Checking enter
			else if (*currChar == '\r')
			{
				currChar++;
				currentLine++;
			}
			//Checking new line
			else if (*currChar == '\n')
			{
				currChar++;
			}
			//Checking space/tab
			else if (*currChar == ' ' || *currChar == '\t')
			{
				currChar++;
			}
		}
		break;
		case LEX_STATE::PARSING_ID:
		{
			if (isalpha(*currChar) || isdigit(*currChar) || *currChar == '_')
			{
				tokenBuffer.append(currChar, 1);
				currChar++;
				if (*currChar == '\0')
				{
					CToken *T;
					if (m_KeyWords.find(tokenBuffer) != m_KeyWords.end())
					{
						T = new CToken(tokenBuffer, TOKEN_TYPE::KEYWORD, currentLine);
					}
					else
					{
						T = new CToken(tokenBuffer, TOKEN_TYPE::ID, currentLine);
					}
					m_Tokens.push_back(T);
					break;
				}
			}
			else
			{
				CToken *T;
				if (m_KeyWords.find(tokenBuffer) != m_KeyWords.end())
				{
					T = new CToken(tokenBuffer, TOKEN_TYPE::KEYWORD, currentLine);
				}
				else
				{
					T = new CToken(tokenBuffer, TOKEN_TYPE::ID, currentLine);
				}
				m_Tokens.push_back(T);
				m_State = LEX_STATE::START;
			}
		}
		break;
		case LEX_STATE::PARSING_INT:
		{
			if (isdigit(*currChar))
			{
				tokenBuffer.append(currChar, 1);
				currChar++;
				if (*currChar == '\0')
				{
					CToken *T;
					T = new CToken(tokenBuffer, TOKEN_TYPE::INT, currentLine);
					m_Tokens.push_back(T);
					break;
				}
			}
			else if (*currChar == '.')
			{
				m_State = LEX_STATE::PARSING_FLOAT;
			}
			else
			{
				CToken *T;
				T = new CToken(tokenBuffer, TOKEN_TYPE::INT, currentLine);
				m_Tokens.push_back(T);
				m_State = LEX_STATE::START;
			}
		}
		break;
		case LEX_STATE::PARSING_FLOAT:
		{
			if (*currChar == '.')
			{
				if (!used_point)
				{
					used_point = true;
					tokenBuffer.append(currChar, 1);
					currChar++;
				}
				else
				{
					//Call error module
				}
				
			}
			else if (isdigit(*currChar))
			{
				tokenBuffer.append(currChar, 1);
				currChar++;
				if (*currChar == '\0')
				{
					CToken *T;
					T = new CToken(tokenBuffer, TOKEN_TYPE::FLOAT, currentLine);
					m_Tokens.push_back(T);
					break;
				}
			}
			else
			{
				CToken *T;
				T = new CToken(tokenBuffer, TOKEN_TYPE::FLOAT, currentLine);
				m_Tokens.push_back(T);
				m_State = LEX_STATE::START;
			}
		}
		break;
		case LEX_STATE::PARSING_STRING:
		{
			if (*currChar != '\0')
			{
				if (*currChar != '"')
				{
					tokenBuffer.append(currChar, 1);
					currChar++;
				}
				else
				{

				}
			}
		}
		break;
		}
	}

	return false;
}

void Compiler_Project_2018B::CLexico::ClearTokens()
{
	m_Tokens.clear();
}

int Compiler_Project_2018B::CLexico::GetNumTokens()
{
	return m_Tokens.size();
}