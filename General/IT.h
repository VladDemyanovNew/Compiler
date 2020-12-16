#pragma once
#include <vector>
#define ID_MAXSIZE		30			// ���� ���-�� �������� � ��������������
#define TI_MAXSIZE		4096		// ���� ���-�� ����� � ������� ���������������
#define TI_INT_DEFAULT	0x00000000	// �������� �� ��������� ��� ���� integer
#define TI_STR_DEFAULT	' '			// �������� �� ��������� ��� ���� string
#define SIGN_DEFAULT	" "			// ������� �� �������� ����������
#define TI_NULLIDX		0xffffffff	// ��� �������� ������� ���������������
#define TI_STR_MAXSIZE  255

namespace IT										// ������� �������������
{
	enum IDDATATYPE {INT=1, STR=2, SYBM=3, NDT=4};					// ���� ������ ���������������: integer, string, symbol
	enum IDTYPE		{V = 1, F = 2, P = 3, L = 4, NT = 5};	// ���� ���������������: ����������, �������, ��������, ������� 

	struct Entry									// ������ ������� ���������������
	{
		int			idxfirstLE;						// ������ ������ ������ � ������� ������
		char*		id;								// ������������� (������������� ��������� �� ID_MAXSIZE)
		IDDATATYPE	iddatatype;						// ��� ������
		IDTYPE		idtype;							// ��� ������������
		std::vector<int> parameters;
		union
		{
			int vint;								// �������� integer
			struct
			{
				int len;							// ���������� �������� � string
				char* str;							// ������� string
			} vstr[TI_STR_MAXSIZE];					// �������� string
		} value;									// �������� ��������������
	};

	struct IdTable									// ��������� ������� ���������������
	{
		int maxsize;								// ������� ������� ��������������� < TI_MAXSIZE
		int size;									// ������� ������ ������� ��������������� < maxsize
		Entry* table;								// ������ ����� ������� ���������������
	};

	IdTable Create(int size);						// ������� ������� ���������������, size - ������� ������� ��������������� < TI_MAXSIZE
	void Add(IdTable& idtable, Entry entry);		// �������� ������ � ������� ���������������
	//int IsId(IdTable& idtable, char id[ID_MAXSIZE], int beginPosition, IDDATATYPE currentIDDT, IDTYPE currentIDT);
	int IsId(IdTable& idtable, char id[ID_MAXSIZE], int beginPosition);
	Entry GetEntry(IdTable& idtable, int n);		// �������� ������ ������� ���������������, n - ����� ���������� ������
	int IsId(IdTable& idtable, char id[ID_MAXSIZE]);// �������: ����� ������ (���� ����), TI_NULLIDX(���� ���)
	void Delete(IdTable& idtable);					// ������� ������� ������ (���������� ������)
}