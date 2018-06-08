#include "stdafx.h"
#include "ErrorModule.h"

Compiler_Project_2018B::CErrorModule::CErrorModule()
{
}

void Compiler_Project_2018B::CErrorModule::AddError(ERROR_PHASE p, int LineNum, String ^ desc, String ^ line)
{
	String ^ S = p.ToString() + " " + LineNum + " " + desc + " " + line;
	//Add to m_errors
}

int Compiler_Project_2018B::CErrorModule::GetNumErrors()
{
	return m_numErrorsLex;
}