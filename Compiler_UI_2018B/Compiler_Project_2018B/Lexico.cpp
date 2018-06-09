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
	String^dError;
	String^lError;
	std::string tokenBuffer;
	bool fHasNumber = false;
	m_State = LEX_STATE::START;
	ClearTokens();

	std::string StringError("Literal constant not closed");

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
				fHasNumber = false;
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
			//Checking less/more than
			else if (*currChar == '<' || *currChar == '>')
			{
				tokenBuffer.clear();
				tokenBuffer.append(currChar, 1);
				currChar++;
				if (*currChar == '=')
				{
					tokenBuffer.append(currChar, 1);
					currChar++;
				}
				CToken *T;
				T = new CToken(tokenBuffer, TOKEN_TYPE::RELATIONAL_OP, currentLine);
				m_Tokens.push_back(T);
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
				m_Tokens.push_back(T);
				currChar++;
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
					CToken * T = new CToken(tokenBuffer, TOKEN_TYPE::LOGICAL_OP, currentLine);
					m_Tokens.push_back(T);
					currChar++;
				}
				else
				{
					tokenBuffer.clear();
					//m_Err->AddError(ERROR_PHASE::LEXICO, currentLine, , currLine);
					//Call error module for incomplete log op
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
					CToken * T = new CToken(tokenBuffer, TOKEN_TYPE::LOGICAL_OP, currentLine);
					m_Tokens.push_back(T);
					currChar++;
				}
				else
				{
					tokenBuffer.clear();
					//Call error module for incomplete log op
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
				currLine = currChar;
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
			//Check if valid char
			if (isalpha(*currChar) || isdigit(*currChar) || *currChar == '_')
			{
				tokenBuffer.append(currChar, 1);
				currChar++;
				//If somehow eof is reached before creating token
				if (*currChar == '\0')
				{
					CToken *T;
					//Check if posible ID is a keyword
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
			//Else send whatever could be stored
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
				tokenBuffer.append(currChar, 1);
				m_State = LEX_STATE::PARSING_FLOAT;
				fHasNumber = false;
				currChar++;
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
			if (isdigit(*currChar))
			{
				fHasNumber = true;
				tokenBuffer.append(currChar, 1);
				currChar++;
			}
			else if (*currChar == '.')
			{
				if (fHasNumber)
				{
					fHasNumber = false;
					CToken *T;
					T = new CToken(tokenBuffer, TOKEN_TYPE::FLOAT, currentLine);
					m_Tokens.push_back(T);
					m_State = LEX_STATE::START;
				}
				else
				{
					//call error module
					tokenBuffer.clear();
					m_State = LEX_STATE::START;
				}
			}
			else
			{
				if (fHasNumber)
				{
					CToken *T;
					T = new CToken(tokenBuffer, TOKEN_TYPE::FLOAT, currentLine);
					m_Tokens.push_back(T);
					m_State = LEX_STATE::START;
				}
				else
				{
					tokenBuffer.clear();
					m_State = LEX_STATE::START;
					//call error module
				}
				
			}
		}
		break;
		case LEX_STATE::PARSING_STRING:
		{
			if (*currChar != '\r')
			{
				tokenBuffer.append(currChar, 1);
				currChar++;
				if (*currChar == '"')
				{
					tokenBuffer.append(currChar, 1);
					CToken* T = new CToken(tokenBuffer, TOKEN_TYPE::STRING, currentLine);
					m_Tokens.push_back(T);
					currChar++;
					m_State = LEX_STATE::START;
				}
			}
			else
			{
				//Call error module for unfinished string
				/*dError = gcnew String(StringError.c_str());
				lError = gcnew String("");
				m_Err->AddError(ERROR_PHASE::LEXICO, currentLine, dError, dError);*/
				m_State = LEX_STATE::START;
				tokenBuffer.clear();
			}			
		}
		break;
		case LEX_STATE::PARSING_EQUALS:
		{
			if (*currChar == '=')
			{
				tokenBuffer.append(currChar, 1);
				CToken* T = new CToken(tokenBuffer, TOKEN_TYPE::RELATIONAL_OP, currentLine);
				m_Tokens.push_back(T);
				currChar++;
				m_State = LEX_STATE::START;
			}
			else
			{
				CToken* T = new CToken(tokenBuffer, TOKEN_TYPE::ASSIGN, currentLine);
				m_Tokens.push_back(T);
				m_State = LEX_STATE::START;
			}
		}
		break;
		case LEX_STATE::PARSING_NOT:
		{
			if (*currChar == '=')
			{
				tokenBuffer.append(currChar, 1);
				CToken* T = new CToken(tokenBuffer, TOKEN_TYPE::RELATIONAL_OP, currentLine);
				m_Tokens.push_back(T);
				currChar++;
				m_State = LEX_STATE::START;
			}
			else
			{
				CToken* T = new CToken(tokenBuffer, TOKEN_TYPE::LOGICAL_OP, currentLine);
				m_Tokens.push_back(T);
				m_State = LEX_STATE::START;
			}
		}
		break;
		case LEX_STATE::PARSING_ARITMETHIC_OP:
		{
			if (*currChar == '/')
			{
				currChar++;
				if (*currChar == '*')
				{
					tokenBuffer.clear();
					m_State = LEX_STATE::PARSING_COMMENT;
					currChar++;
				}
				else
				{
					CToken* T = new CToken(tokenBuffer, TOKEN_TYPE::ARITHMETIC_OP, currentLine);
					m_Tokens.push_back(T);
					m_State = LEX_STATE::START;
				}
			}
			else
			{
				CToken* T = new CToken(tokenBuffer, TOKEN_TYPE::ARITHMETIC_OP, currentLine);
				m_Tokens.push_back(T);
				currChar++;
				m_State = LEX_STATE::START;
			}
		}
		break;
		case LEX_STATE::PARSING_COMMENT:
		{
			if (*currChar != '\0')
			{
				if (*currChar == '*')
				{
					currChar++;
					if (*currChar != '\0')
					{
						if (*currChar == '/')
						{
							currChar++;
							m_State = LEX_STATE::START;
						}
					}
					else
					{
						//Call error module for unfinished comment
						tokenBuffer.clear();
					}
				}
				else
				{
					currChar++;
					if (*currChar == '\0')
					{
						//Call error module
						tokenBuffer.clear();
					}
				}				
			}
			else
			{
				//Call error module for unfinished comment
				tokenBuffer.clear();
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

std::vector<Compiler_Project_2018B::CToken*> Compiler_Project_2018B::CLexico::GetTokens()
{
	return m_Tokens;
}

cli::array<String^>^ Compiler_Project_2018B::CLexico::GetToken()
{
	cli::array<String^>^m_TokenString = gcnew cli::array<String^>(m_Tokens.size());
	String^ S;

	for (int i = 0; i < m_Tokens.size(); i++)
	{
		m_TokenString[i] = gcnew String("");
	}

	for (int i = 0; i < m_Tokens.size(); i++)
	{
		S = gcnew String(m_Tokens[i]->GetLex().c_str());
		m_TokenString->SetValue(String::Format("{0}\t{1}", S, m_Tokens[i]->getTokenType().ToString()), i);
	}
	return m_TokenString;
}