#pragma once
#include <Windows.h>
#include <vcclr.h>
#include <map>
#include <vector>
#include <string>
#include "ErrorModule.h"
#include "Token.h"

namespace Compiler_Project_2018B
{
	public enum class LEX_STATE
	{
		START = 0,
		PARSING_ID,
		PARSING_INT,
		PARSING_FLOAT,
		PARSING_STRING,
		PARSING_LESS,
		PARSING_LESS_EQUAL,
		PARSING_MORE,
		PARSING_MORE_EQUAL,
		PARSING_EQUALS,
		PARSING_COMPARISON,
		PARSING_NOT,
		PARSING_DIFFERENT,
		PARSING_DIMENSION,
		PARSING_ARITMETHIC_OP,
		PARSING_COMMENT
	};

	class CLexico
	{
	private:
		msclr::gcroot<CErrorModule^>m_Err;
		std::vector<CToken *>m_Tokens;
		std::map<std::string, std::string>m_KeyWords;
	public:
		CLexico(CErrorModule ^ err);
		bool ParseCode(const char * src);
		LEX_STATE m_State;
		void ClearTokens();
		int GetNumTokens();
		std::vector<CToken*>GetTokens();
		cli::array<String^>^GetToken();
	};
}