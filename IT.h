#pragma once
#define ID_MAXSIZE		5			// ���� ���-�� �������� � ��������������
#define TI_MAXSIZE		4096		// ���� ���-�� ����� � ������� ���������������
#define TI_INT_DEFAULT	0x00000000	// �������� �� ��������� ��� ���� integer
#define TI_STR_DEFAULT	0x00		// �������� �� ��������� ��� ���� string
#define TI_NULLIDX		0xffffffff	// ��� �������� ������� ���������������
#define TI_STR_MAXSIZE  255

namespace IT										// ������� �������������
{
	enum IDDATATYPE {INT=1, STR=2};					// ���� ������ ���������������: integer, string
	enum IDTYPE		{V = 1, F = 2, P = 3, L = 3};	// ���� ���������������: ����������, �������, ��������, ������� 

	struct Entry									// ������ ������� ���������������
	{
		int			idxfirstLE;						// ������ ������ ������ � ������� ������
		char*		id;								// ������������� (������������� ��������� �� ID_MAXSIZE)
		IDDATATYPE	iddatatype;						// ��� ������
		IDTYPE		idtype;							// ��� ������������
		union
		{
			int vint;								// �������� integer
			struct
			{
				char len;							// ���������� �������� � string
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
	Entry GetEntry(IdTable& idtable, int n);		// �������� ������ ������� ���������������, n - ����� ���������� ������
	int IsId(IdTable& idtable, char id[ID_MAXSIZE]);// �������: ����� ������ (���� ����), TI_NULLIDX(���� ���)
	void Delete(IdTable& idtable);					// ������� ������� ������ (���������� ������)
}