#include "stdafx.h"
#include "ErrorModule.h"

Compiler_Project_2018B::CErrorModule::CErrorModule()
{
	m_maxErrors = 30;
	m_numErrorsLex = 0;
	m_errors = gcnew cli::array<String^>(m_maxErrors);

	for (int i = 0; i < m_maxErrors; i++)
	{
		m_errors[i] = gcnew String("");
	}
}

void Compiler_Project_2018B::CErrorModule::AddError(ERROR_PHASE p, int LineNum, String ^ desc, String ^ line)
{
	m_errors->SetValue(String::Format("<{0}>: \t{1}\t\t{2\t\t{3}", p.ToString(), LineNum, desc, line), m_numErrorsLex);
	m_numErrorsLex++;
}

int Compiler_Project_2018B::CErrorModule::GetNumErrors()
{
	return m_numErrorsLex;
}

cli::array<String^>^ Compiler_Project_2018B::CErrorModule::GetErrors()
{
	return m_errors;
}
