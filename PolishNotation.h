#pragma once
#include "IT.h"
#include "LT.h"

#define EXP1 28		// ������� ������� ���������
#define EXP2 50		// ������� ������� ���������
#define EXP3 66		// ������� �������� ���������

namespace PN
{
	bool PolishNotation(
		int				lextable_pos,	// ������� ��������� � lextable
		LT::LexTable&	lextable,
		IT::IdTable&	idtable
	);

}