// Compiler_Project_2018B.h

#pragma once
#include "Lexico.h"
using namespace System;

namespace Compiler_Project_2018B {

	public ref class Manager
	{
	public:
		//Constructor/Destructor
		Manager();
		~Manager();

		cli::array<String^>^Compile(String^src);
	private:
		CLexico * m_lex;
		CErrorModule ^ m_err;
	};
}