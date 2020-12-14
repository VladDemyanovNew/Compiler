#pragma once
#include <list>
#include <stack>
#include <vector>
#define LEXEMA_FIXSIZE				1				// ���� ������ �������
#define LT_MAXSIZE					4096			// ���� ���-�� ����� � ������� ������
#define LT_TI_NULLIDX				0xffffffff		// ��� �������� ������� ���������������

#define LEX_MAIN	 				'g'				// go
#define LEX_FUNCTION				'f'				// func
#define LEX_RETURN					'r'				// ret
#define LEX_PRINT					'p'				// puts
#define LEX_IF						'q'				// if
#define LEX_UNTIL					'u'				// until
#define LEX_LOOP					'l'				// loop
#define LEX_ELSE					'e'				// else
#define LEX_END						'd'				// end

#define LEX_TYPE					't'				// ���
#define LEX_ID						'i'				// �������������
#define LEX_SYMBOL_LITERAL			'c'				// symbol
#define LEX_STRING_LITERAL			's'				// ��������� �������
#define LEX_NUMERICAL_LITERAL		'n'				// �������� �������
#define LEX_FUNC_CALL				'@'				// ����� �������

#define LEX_DECLARE					'$'				// $
#define LEX_SEMICOLON				';'				// ;
#define LEX_COMMA					','				// ,
#define LEX_LEFTBRACE				'{'				// {
#define LEX_BRACELET				'}'				// }
#define LEX_LEFTHESIS				'('				// (
#define LEX_RIGHTHESIS				')'				// )
#define LEX_ACTION					'v'
#define LEX_PLUS					'+'				// +
#define LEX_MINUS					'-'				// -
#define LEX_STAR					'*'				// *
#define LEX_DIRSLASH				'/'				// /
#define LEX_EQUAL					'='				// =
#define LEX_MORE					'w'				// >
#define LEX_LESS					'w'				// <
#define LEX_COMPARE_EQUAL			'w'				// ==
#define LEX_COMPARE_LESS			'w'				// <=
#define LEX_COMPARE_MORE			'w'				// >=

namespace LT									// ������� ������
{
	struct Entry								// ������ ������� ������
	{
		char lexema;							// �������
		int lineSource;							// ����� ������ � �������� ����
		int indexIdTable;						// ������ � ������� ��������������� ��� LT_TI_NULLIDX
		char* sign;
		int numberOfParams;
		Entry();
		Entry(char l, int n);
		Entry(char l, int ls, int i, char* s);
	};

	struct LexTable								// ��������� ������� ������
	{
		int maxsize;							// ������� ������� ������ < LT_MAXSIZE
		int size;								// ������� ������ ������� ������ < maxsize
		std::vector<int> refsToAssigns;			// ������� ������� ������, ������� �������� =
		Entry* table;							// ������ ����� ������� ������
	};

	LexTable Create(int size);					// ������� ������� ������, ������� ������� ������ < LT_MAXSIZE
	void Add(LexTable& lextable, Entry entry);	// �������� ������ � ������� ������ 
	Entry GetEntry(LexTable& lextable, int n);	// �������� ������ ������� ������, n - ����� ���������� ������
	void Delete(LexTable& lextable);			// ������� ������� ������ (���������� ������)
	void AddList(LexTable& lextable, std::list <LT::Entry> list_of_LT_Entries);
}