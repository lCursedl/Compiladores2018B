#pragma once

using namespace System;

namespace Compiler_Project_2018B {

	public enum class ERROR_PHASE
	{
		LEXICO = 0,
		SINTACTICO,
		SEMANTICO
	};

	public ref class CErrorModule
	{
	private:
		int m_maxErrors;
		int m_numErrorsLex;
		cli::array<String^>^m_errors;
	public:
		CErrorModule();
		void AddError(ERROR_PHASE p, int LineNum, String ^ desc, String ^ line);
		int GetNumErrors();
	};
}