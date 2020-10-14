#pragma once
#define LEXEMA_FIXSIZE				1				// ���� ������ �������
#define LT_MAXSIZE					4096			// ���� ���-�� ����� � ������� ������
#define LT_TI_NULLIDX				0xffffffff		// ��� �������� ������� ���������������
#define LEX_MAIN					'm'				// main
#define LEX_TYPE					't'
#define LEX_INTEGER					'x'				// integer
#define LEX_STRING					'y'				// string
#define LEX_ID						'i'				// �������������
#define LEX_LITERAL					'l'				// �������
#define LEX_STRING_LITERAL			's'				// ��������� �������
#define LEX_NUMERICAL_LITERAL		'n'				// �������� �������
#define LEX_FUNCTION				'f'				// function
#define LEX_DECLARE					'd'				// declare
#define LEX_RETURN					'r'				// return
#define LEX_PRINT					'p'				// print
#define LEX_SEMICOLON				';'				// ;
#define LEX_COMMA					','				// ,
#define LEX_LEFTBRACE				'{'				// {
#define LEX_BRACELET				'}'				// }
#define LEX_LEFTHESIS				'('				// (
#define LEX_RIGHTHESIS				')'				// )
#define LEX_PLUS					'v'				// +
#define LEX_MINUS					'v'				// -
#define LEX_STAR					'v'				// *
#define LEX_DIRSLASH				'v'				// /
#define LEX_EQUAL					'='				// =

namespace LT									// ������� ������
{
	struct Entry								// ������ ������� ������
	{
		char lexema;							// �������
		int lineSource;							// ����� ������ � �������� ����
		int indexIdTable;						// ������ � ������� ��������������� ��� LT_TI_NULLIDX	
	};

	struct LexTable								// ��������� ������� ������
	{
		int maxsize;							// ������� ������� ������ < LT_MAXSIZE
		int size;								// ������� ������ ������� ������ < maxsize
		Entry* table;							// ������ ����� ������� ������
	};

	LexTable Create(int size);					// ������� ������� ������, ������� ������� ������ < LT_MAXSIZE
	void Add(LexTable& lextable, Entry entry);	// �������� ������ � ������� ������ 
	Entry GetEntry(LexTable& lextable, int n);	// �������� ������ ������� ������, n - ����� ���������� ������
	void Delete(LexTable& lextable);			// ������� ������� ������ (���������� ������)
	
}