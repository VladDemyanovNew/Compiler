#pragma once
#include <stack>
#include <iomanip>
#include "GRB.h"
#include "Log.h"
#include <iostream>


#define MFST_DIAGN_MAXSIZE 2*ERROR_MAXSIZE_MESSAGE
#define MFST_DIAGN_NUMBER 3
#define MFST_TRACE_START(syn) *(syn.stream)<<std::setw( 4)<<std::left<<"���"<<":"\
									<<std::setw(20)<<std::left<<"�������"\
									<<std::setw(30)<<std::left<<"������� �����"\
									<<std::setw(20)<<std::left<<"����"<<std::endl;

typedef std::stack<short> MFSTSTSTACK;	// ���� ��������

namespace MFST				// ���������� �������
{
	template<class T>T getStackElement(const std::stack<T>& st, size_t element)
	{
		using base = std::stack<T>;
		struct acces : base { using base::c; };
		return (st.* & acces::c)[element];
	}

	struct MfstState		// ��������� �������� (��� ����������)
	{
		short lenta_position;		// ������� �� �����
		short nrule;				// ����� �������� �������
		short nrulechain;			// ����� ������� �������
		MFSTSTSTACK stack;			// ���� ��������
		MfstState();
		MfstState(
			short pposition,       // ������� �� �����
			MFSTSTSTACK pst,       // ���� ��������
			short pnrulechain      // ����� ������� �������
		);
		MfstState(
			short pposition,       // ������� �� �����
			MFSTSTSTACK pst,       // ���� ��������
			short pnrule,		   // ����� �������� �������		
			short pnrulechain      // ����� ������� �������
		);
	};

	struct Mfst			// ���������� �������
	{
		enum RC_STEP {				// ��� �������� ������� step
			NS_OK,					// ������� ������� � �������, ������� �������� � ����
			NS_NORULE,				// �� ������� ������� ���������� (������ � ����������)
			NS_NORULECHAIN,			// �� ������� ���������� ������� ������� (������ � �������� ����)
			NS_ERROR,				// ����������� �������������� ������ ����������
			TS_OK,					// ���. ������ ����� == ������� �����, ������������ �����, pop �����
			TS_NOK,					// ���. ������ ����� != ������� �����, ������������� ��������� 
			LENTA_END,				// ������� ������� ����� >= lenta_size
			SURPRISE				// ����������� ��� �������� (������ � step)
		};

		struct MfstDiagnosis				// �����������
		{
			short lenta_position;			// ������� �� �����
			RC_STEP rc_step;				// ��� ���������� ����
			short nrule;					// ����� �������
			short nrule_chain;				// ����� ������� �������
			MfstDiagnosis();
			MfstDiagnosis(				// ����������
				short plenta_position,	// ������� �� �����
				RC_STEP prc_step,		// ��� ���������� ����
				short pnrule,			// ����� ������� 
				short pnrule_chain		// ����� ������� �������
			);
		} diagnosis[MFST_DIAGN_NUMBER];		// ��������� ����� �������� ���������

		GRBALPHABET* lenta;					// ���������������� (TS/NS) ����� (�� LEX)
		short lenta_position;				// ������� ������� �� �����
		short nrule;						// ����� �������� �������
		short nrulechain;					// ����� ������� ������� �������� �������
		short lenta_size;					// ������ �����
		GRB::Greibach greibach;				// ���������� �������
		LR::Tables lex;						// ��������� ������ ������������ �����������
		MFSTSTSTACK stack;					// ���� ��������
		std::stack<MfstState> storestate;	// ���� ��� ���������� ���������
		Mfst();
		Mfst(
			LR::Tables plex,				// ��������� ������ ������������ �����������
			GRB::Greibach pgrebach		// ���������� �������
		);

		char* getCStack(char* buf);								// �������� ���������� �����
		char* getCLenta(char* buf, short pos, short n = 25);	// �����: n �������� � pos
		char* getDiagnosis(short n, char* buf);					// �������� n-�� ������ ����������� ��� 0�00
		bool saveState(Log::LOG syn);										// ��������� ��������� ��������
		bool restState(Log::LOG syn);										// ������������ ��������� ��������
		bool push_chain(										// ��������� ������� ������� � ����
			GRB::Rule::Chain chain								// ������� ������
		);
		RC_STEP step(Log::LOG syn);							// ��������� ��� ��������
		bool start(Log::LOG syn);							// ��������� �������
		bool saveDiagnosis(
			RC_STEP pprc_step					// ��� ���������� ����
		);
		void printRules(Log::LOG syn);						// ������� ������������������ ������

		struct Deducation	// �����
		{
			short size;					// ��������� ����� � ������
			short* nrules;				// ������ ������ ����������
			short* nrulechains;			// ������ ������� ������ ���������� (nrules)
			Deducation() { size = 0; nrules = 0; nrulechains = 0; };
		} deducation;
		bool saveDeducation();			// ��������� ������ ������
	};
}