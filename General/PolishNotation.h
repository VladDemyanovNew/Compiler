#pragma once
#include "IT.h"
#include "LT.h"
#include "Log.h"

#define EXP1 28		// ������� ������� ���������
#define EXP2 50		// ������� ������� ���������
#define EXP3 66		// ������� �������� ���������

namespace PN
{
	std::list <LT::Entry> ConvertToPN(
		int				lextable_pos,	// ������� ��������� � lextable
		LT::LexTable&	lextable,
		IT::IdTable&	idtable,
		int&			semicolon,
		Log::LOG		pn
	);
	LT::LexTable PolishNotation(LT::LexTable& lextable, IT::IdTable& idtable, Log::LOG pn);
}