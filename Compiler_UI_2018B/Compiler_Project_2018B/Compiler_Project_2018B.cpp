// This is the main DLL file.
#include "stdafx.h"
#include "Compiler_Project_2018B.h"

Compiler_Project_2018B::Manager::Manager()
{
	m_err = gcnew CErrorModule();
	m_lex = new CLexico(m_err);
}

Compiler_Project_2018B::Manager::~Manager()
{
	delete m_lex;
	m_lex = nullptr;
}

cli::array<String^>^ Compiler_Project_2018B::Manager::Compile(String ^ src)
{
	cli::array<String^>^Compilation_Details;
	m_lex->ParseCode((const char*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(src).ToPointer());
	int numErrors = m_err->GetNumErrors();
	Compilation_Details = gcnew cli::array<String^>(numErrors + 1 + m_lex->GetNumTokens());
	return Compilation_Details;
}