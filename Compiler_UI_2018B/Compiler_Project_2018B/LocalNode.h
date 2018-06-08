#pragma once
namespace Compiler_Project2018
{
	enum class Symbol_Category
	{
		VAR_GLOBAL = 0,
		FUNCTION,
		VAR_LOCAL,
		PARAM,
		INDEF
	};

	enum class Symbol_Type
	{
		INT = 0,
		BOOL,
		FLOAT,
		STRING,
		VOID,
		INDEF
	};

	class CLocalNode
	{
	public:
		CLocalNode();
	};
}