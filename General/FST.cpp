
#include "Headers.h"

namespace FST
{
	FST::FST() {};
	RELATION::RELATION(char c, short nn)
	{
		symbol = c; // ������ ��������
		nnode = nn; // ����� ������� �������
	};

	NODE::NODE()
	{
		n_relation = 0; // ���������� ����������� ����
		RELATION* relations = NULL; // ����������� ����
	};

	NODE::NODE(short n, RELATION rel, ...)
	{
		n_relation = n;
		RELATION* p = &rel;
		relations = new RELATION[n];
		for (short i = 0; i < n; i++) relations[i] = p[i];
	}

	FST::FST(const char* s, short ns, char l, LEXTYPE l_t, NODE n, ...)
	{
		lex = l;
		string = s; // �������
		nstates = ns; // ���������� ��������� ��������
		nodes = new NODE[ns]; // ���� ���������
		NODE* p = &n;
		for (int k = 0; k < ns; k++) nodes[k] = p[k];
		rstates = new short[nstates]; // ��������� ��������� �������� �� ������ �������
		memset(rstates, 0xff, sizeof(short) * nstates);
		rstates[0] = 0;
		position = -1; // ������� ������� � �������
		lex_type = l_t;
	}

	bool execute(FST& fst)
	{
		short* rstates = new short[fst.nstates];
		memset(rstates, 0xff, sizeof(short) * fst.nstates);
		short lstring = strlen(fst.string);
		bool rc = true;
		for (short i = 0; i < lstring && rc; i++)
		{
			fst.position++;
			rc = step(fst, rstates);
		}
		delete[] rstates;
		return (rc ? (fst.rstates[fst.nstates - 1] == lstring) : rc);
	}

	bool step(FST& fst, short*& rstates)
	{
		bool rc = false;
		std::swap(rstates, fst.rstates);
		for (short i = 0; i < fst.nstates; i++)
		{
			if (rstates[i] == fst.position)
				for (short j = 0; j < fst.nodes[i].n_relation; j++)
				{
					if (fst.nodes[i].relations[j].symbol == fst.string[fst.position])
					{
						fst.rstates[fst.nodes[i].relations[j].nnode] = fst.position + 1;
						rc = true;
					}
				}
		}
		return rc;
	}

	FST* arrFST()
	{
		FST compareEqualFST("", 3, LEX_COMPARE_EQUAL, ACTION_LEX,
			NODE(1, RELATION('=', 1)),
			NODE(1, RELATION('=', 2)),
			NODE()
		);
		FST compareLessFST("", 3, LEX_COMPARE_LESS, ACTION_LEX,
			NODE(1, RELATION('<', 1)),
			NODE(1, RELATION('=', 2)),
			NODE()
		);
		FST compareMoreFST("", 3, LEX_COMPARE_MORE, ACTION_LEX,
			NODE(1, RELATION('>', 1)),
			NODE(1, RELATION('=', 2)),
			NODE()
		);
		FST equalFST("", 2, LEX_EQUAL, ACTION_LEX,
			NODE(1, RELATION('=', 1)),
			NODE()
		);
		FST morelFST("", 2, LEX_MORE, ACTION_LEX,
			NODE(1, RELATION('>', 1)),
			NODE()
		);
		FST lesslFST("", 2, LEX_LESS, ACTION_LEX,
			NODE(1, RELATION('<', 1)),
			NODE()
		);
		FST dirslashFST("", 2, LEX_ACTION, ACTION_LEX,
			NODE(1, RELATION('/', 1)),
			NODE()
		);
		FST starFST("", 2, LEX_ACTION, ACTION_LEX,
			NODE(1, RELATION('*', 1)),
			NODE()
		);
		FST minusFST("", 2, LEX_ACTION, ACTION_LEX,
			NODE(1, RELATION('-', 1)),
			NODE()
		);
		FST plusFST("", 2, LEX_ACTION, ACTION_LEX,
			NODE(1, RELATION('+', 1)),
			NODE()
		);
		FST righthesisFST("", 2, LEX_RIGHTHESIS, PRIORITY_LEX,
			NODE(1, RELATION(')', 1)),
			NODE()
		);
		FST lefthesisFST("", 2, LEX_LEFTHESIS, PRIORITY_LEX,
			NODE(1, RELATION('(', 1)),
			NODE()
		);
		FST braceletFST("", 2, LEX_BRACELET, COMMON_LEX,
			NODE(1, RELATION('}', 1)),
			NODE()
		);
		FST leftbraceFST("", 2, LEX_LEFTBRACE, COMMON_LEX,
			NODE(1, RELATION('{', 1)),
			NODE()
		);
		FST commaFST("", 2, LEX_COMMA, PRIORITY_LEX,
			NODE(1, RELATION(',', 1)),
			NODE()
		);
		FST semicolonFST("", 2, LEX_SEMICOLON, COMMON_LEX,
			NODE(1, RELATION(';', 1)),
			NODE()
		);
		FST integerFST("", 7, LEX_TYPE, COMMON_LEX,		// +
			NODE(1, RELATION('p', 1)),
			NODE(1, RELATION('o', 2)),
			NODE(1, RELATION('s', 3)),
			NODE(1, RELATION('i', 4)),
			NODE(1, RELATION('n', 5)),
			NODE(1, RELATION('t', 6)),
			NODE()
		);
		FST symbolFST("", 7, LEX_TYPE, COMMON_LEX,		// +
			NODE(1, RELATION('s', 1)),
			NODE(1, RELATION('y', 2)),
			NODE(1, RELATION('m', 3)),
			NODE(1, RELATION('b', 4)),
			NODE(1, RELATION('o', 5)),
			NODE(1, RELATION('l', 6)),
			NODE()
		);
		FST stringFST("", 7, LEX_TYPE, COMMON_LEX,		// +
			NODE(1, RELATION('s', 1)),
			NODE(1, RELATION('t', 2)),
			NODE(1, RELATION('r', 3)),
			NODE(1, RELATION('i', 4)),
			NODE(1, RELATION('n', 5)),
			NODE(1, RELATION('g', 6)),
			NODE()
		);
		FST idFST("", 2, LEX_ID, LEX_ID_TABLE,			// +
			NODE(124,
			RELATION('a', 0), RELATION('b', 0), RELATION('c', 0), RELATION('d', 0),
			RELATION('e', 0), RELATION('f', 0), RELATION('g', 0), RELATION('h', 0),
			RELATION('i', 0), RELATION('j', 0), RELATION('k', 0), RELATION('l', 0),
			RELATION('m', 0), RELATION('n', 0), RELATION('o', 0), RELATION('p', 0),
			RELATION('q', 0), RELATION('r', 0), RELATION('s', 0), RELATION('t', 0),
			RELATION('u', 0), RELATION('v', 0), RELATION('w', 0), RELATION('x', 0),
			RELATION('y', 0), RELATION('z', 0),

			RELATION('A', 0), RELATION('B', 0), RELATION('C', 0), RELATION('D', 0), RELATION('E', 0), RELATION('F', 0),
			RELATION('G', 0), RELATION('H', 0), RELATION('I', 0), RELATION('J', 0), RELATION('K', 0), RELATION('L', 0),
			RELATION('M', 0), RELATION('N', 0), RELATION('O', 0), RELATION('P', 0), RELATION('Q', 0), RELATION('R', 0),
			RELATION('S', 0), RELATION('T', 0), RELATION('U', 0), RELATION('V', 0), RELATION('W', 0), RELATION('X', 0),
			RELATION('Y', 0), RELATION('Z', 0),

			RELATION('1', 0), RELATION('2', 0), RELATION('3', 0), RELATION('4', 0),
			RELATION('5', 0), RELATION('6', 0), RELATION('7', 0), RELATION('8', 0), RELATION('9', 0), RELATION('0', 0),

			RELATION('a', 1), RELATION('b', 1), RELATION('c', 1), RELATION('d', 1),
			RELATION('e', 1), RELATION('f', 1), RELATION('g', 1), RELATION('h', 1),
			RELATION('i', 1), RELATION('j', 1), RELATION('k', 1), RELATION('l', 1),
			RELATION('m', 1), RELATION('n', 1), RELATION('o', 1), RELATION('p', 1),
			RELATION('q', 1), RELATION('r', 1), RELATION('s', 1), RELATION('t', 1),
			RELATION('u', 1), RELATION('v', 1), RELATION('w', 1), RELATION('x', 1),
			RELATION('y', 1), RELATION('z', 1)),

			RELATION('A', 1), RELATION('B', 1), RELATION('C', 1), RELATION('D', 1), RELATION('E', 1), RELATION('F', 1),
			RELATION('G', 1), RELATION('H', 1), RELATION('I', 1), RELATION('J', 1), RELATION('K', 1), RELATION('L', 1),
			RELATION('M', 1), RELATION('N', 1), RELATION('O', 1), RELATION('P', 1), RELATION('Q', 1), RELATION('R', 1),
			RELATION('S', 1), RELATION('T', 1), RELATION('U', 1), RELATION('V', 1), RELATION('W', 1), RELATION('X', 1),
			RELATION('Y', 1), RELATION('Z', 1),

			RELATION('1', 1), RELATION('2', 1), RELATION('3', 1), RELATION('4', 1),
			RELATION('5', 1), RELATION('6', 1), RELATION('7', 1), RELATION('8', 1), RELATION('9', 1), RELATION('0', 1),
			NODE()
		);
		FST numlFST("", 2, LEX_NUMERICAL_LITERAL, LITERAL_LEX,		// +
			NODE(20,
				RELATION('0', 0), RELATION('1', 0), RELATION('2', 0),
				RELATION('3', 0), RELATION('4', 0), RELATION('5', 0),
				RELATION('6', 0), RELATION('7', 0), RELATION('8', 0),
				RELATION('9', 0),

				RELATION('0', 1), RELATION('1', 1), RELATION('2', 1),
				RELATION('3', 1), RELATION('4', 1), RELATION('5', 1),
				RELATION('6', 1), RELATION('7', 1), RELATION('8', 1),
				RELATION('9', 1)),
			NODE()
		);
		FST symbollFST("", 4, LEX_SYMBOL_LITERAL, LITERAL_LEX,		// +
			NODE(2,
				RELATION('#', 1),
				RELATION('#', 2)),
			NODE(138,
				RELATION('A', 2), RELATION('B', 2), RELATION('C', 2), RELATION('D', 2), RELATION('E', 2), RELATION('F', 2),
				RELATION('G', 2), RELATION('H', 2), RELATION('I', 2), RELATION('J', 2), RELATION('K', 2), RELATION('L', 2),
				RELATION('M', 2), RELATION('N', 2), RELATION('O', 2), RELATION('P', 2), RELATION('Q', 2), RELATION('R', 2),
				RELATION('S', 2), RELATION('T', 2), RELATION('U', 2), RELATION('V', 2), RELATION('W', 2), RELATION('X', 2),
				RELATION('Y', 2), RELATION('Z', 2),
				RELATION('a', 2), RELATION('b', 2), RELATION('c', 2), RELATION('d', 2), RELATION('e', 2), RELATION('f', 2),
				RELATION('g', 2), RELATION('h', 2), RELATION('i', 2), RELATION('j', 2), RELATION('k', 2), RELATION('l', 2),
				RELATION('m', 2), RELATION('n', 2), RELATION('o', 2), RELATION('p', 2), RELATION('q', 2), RELATION('r', 2),
				RELATION('s', 2), RELATION('t', 2), RELATION('u', 2), RELATION('v', 2), RELATION('w', 2), RELATION('x', 2),
				RELATION('y', 2), RELATION('z', 2), RELATION('1', 2), RELATION('2', 2), RELATION('3', 2), RELATION('4', 2),
				RELATION('5', 2), RELATION('6', 2), RELATION('7', 2), RELATION('8', 2), RELATION('9', 2), RELATION('0', 2),

				RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2),
				RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2),
				RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2),
				RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2),
				RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2),
				RELATION('�', 2), RELATION('�', 2), RELATION('�', 2),

				RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2),
				RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2),
				RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2),
				RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2),
				RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2),
				RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION(' ', 2), RELATION('.', 2), RELATION(',', 2),
				RELATION('?', 2), RELATION('!', 2), RELATION(';', 2), RELATION(':', 2), RELATION('-', 2), RELATION(')', 2),
				RELATION('(', 2)),
			NODE(1, RELATION('#', 3)),
			NODE()
		);
		FST stringlFST("", 4, LEX_STRING_LITERAL, LITERAL_LEX,		// +
			NODE(2,
				RELATION('#', 1),
				RELATION('#', 2)),
			NODE(276,
				RELATION('A', 1), RELATION('B', 1), RELATION('C', 1), RELATION('D', 1), RELATION('E', 1), RELATION('F', 1),
				RELATION('G', 1), RELATION('H', 1), RELATION('I', 1), RELATION('J', 1), RELATION('K', 1), RELATION('L', 1),
				RELATION('M', 1), RELATION('N', 1), RELATION('O', 1), RELATION('P', 1), RELATION('Q', 1), RELATION('R', 1),
				RELATION('S', 1), RELATION('T', 1), RELATION('U', 1), RELATION('V', 1), RELATION('W', 1), RELATION('X', 1),
				RELATION('Y', 1), RELATION('Z', 1),

				RELATION('a', 1), RELATION('b', 1), RELATION('c', 1), RELATION('d', 1), RELATION('e', 1), RELATION('f', 1),
				RELATION('g', 1), RELATION('h', 1), RELATION('i', 1), RELATION('j', 1), RELATION('k', 1), RELATION('l', 1),
				RELATION('m', 1), RELATION('n', 1), RELATION('o', 1), RELATION('p', 1), RELATION('q', 1), RELATION('r', 1),
				RELATION('s', 1), RELATION('t', 1), RELATION('u', 1), RELATION('v', 1), RELATION('w', 1), RELATION('x', 1),
				RELATION('y', 1), RELATION('z', 1), RELATION('1', 1), RELATION('2', 1), RELATION('3', 1), RELATION('4', 1),
				RELATION('5', 1), RELATION('6', 1), RELATION('7', 1), RELATION('8', 1), RELATION('9', 1), RELATION('0', 1),

				RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1),
				RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1),
				RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1),
				RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1),
				RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1),
				RELATION('�', 1), RELATION('�', 1), RELATION('�', 1),

				RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1),
				RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1),
				RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1),
				RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1),
				RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION('�', 1),
				RELATION('�', 1), RELATION('�', 1), RELATION('�', 1), RELATION(' ', 1), RELATION('.', 1), RELATION(',', 1),
				RELATION('?', 1), RELATION('!', 1), RELATION(';', 1), RELATION(':', 1), RELATION('-', 1), RELATION(')', 1),
				RELATION('(', 1),

				RELATION('A', 2), RELATION('B', 2), RELATION('C', 2), RELATION('D', 2), RELATION('E', 2), RELATION('F', 2),
				RELATION('G', 2), RELATION('H', 2), RELATION('I', 2), RELATION('J', 2), RELATION('K', 2), RELATION('L', 2),
				RELATION('M', 2), RELATION('N', 2), RELATION('O', 2), RELATION('P', 2), RELATION('Q', 2), RELATION('R', 2),
				RELATION('S', 2), RELATION('T', 2), RELATION('U', 2), RELATION('V', 2), RELATION('W', 2), RELATION('X', 2),
				RELATION('Y', 2), RELATION('Z', 2),
				RELATION('a', 2), RELATION('b', 2), RELATION('c', 2), RELATION('d', 2), RELATION('e', 2), RELATION('f', 2),
				RELATION('g', 2), RELATION('h', 2), RELATION('i', 2), RELATION('j', 2), RELATION('k', 2), RELATION('l', 2),
				RELATION('m', 2), RELATION('n', 2), RELATION('o', 2), RELATION('p', 2), RELATION('q', 2), RELATION('r', 2),
				RELATION('s', 2), RELATION('t', 2), RELATION('u', 2), RELATION('v', 2), RELATION('w', 2), RELATION('x', 2),
				RELATION('y', 2), RELATION('z', 2), RELATION('1', 2), RELATION('2', 2), RELATION('3', 2), RELATION('4', 2),
				RELATION('5', 2), RELATION('6', 2), RELATION('7', 2), RELATION('8', 2), RELATION('9', 2), RELATION('0', 2),

				RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2),
				RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2),
				RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2),
				RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2),
				RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2),
				RELATION('�', 2), RELATION('�', 2), RELATION('�', 2),

				RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2),
				RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2),
				RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2),
				RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2),
				RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION('�', 2),
				RELATION('�', 2), RELATION('�', 2), RELATION('�', 2), RELATION(' ', 2), RELATION('.', 2), RELATION(',', 2),
				RELATION('?', 2), RELATION('!', 2), RELATION(';', 2), RELATION(':', 2), RELATION('-', 2), RELATION(')', 2),
				RELATION('(', 2)),
			NODE(1, RELATION('#', 3)),
			NODE()
		);
		FST ifFST("", 3, LEX_IF, COMMON_LEX,	// ?
			NODE(1, RELATION('i', 1)),
			NODE(1, RELATION('f', 2)),
			NODE()
		);
		FST endFST("", 4, LEX_END, COMMON_LEX,	// ?
			NODE(1, RELATION('e', 1)),
			NODE(1, RELATION('n', 2)),
			NODE(1, RELATION('d', 3)),
			NODE()
		); 
		FST untilFST("", 6, LEX_UNTIL, COMMON_LEX,	// ?
			NODE(1, RELATION('u', 1)),
			NODE(1, RELATION('n', 2)),
			NODE(1, RELATION('t', 3)),
			NODE(1, RELATION('i', 4)),
			NODE(1, RELATION('l', 5)),
			NODE()
		);
		FST loopFST("", 5, LEX_LOOP, COMMON_LEX,	// ?
			NODE(1, RELATION('l', 1)),
			NODE(1, RELATION('o', 2)),
			NODE(1, RELATION('o', 3)),
			NODE(1, RELATION('p', 4)),
			NODE()
		);
		FST elseFST("", 5, LEX_ELSE, COMMON_LEX,	// ?
			NODE(1, RELATION('e', 1)),
			NODE(1, RELATION('l', 2)),
			NODE(1, RELATION('s', 3)),
			NODE(1, RELATION('e', 4)),
			NODE()
		);
		FST functionFST("", 5, LEX_FUNCTION, COMMON_LEX,	// +
			NODE(1, RELATION('f', 1)),
			NODE(1, RELATION('u', 2)),
			NODE(1, RELATION('n', 3)),
			NODE(1, RELATION('c', 4)),
			NODE()
		);
		FST declareFST("", 2, LEX_DECLARE, COMMON_LEX,		// +
			NODE(1, RELATION('$', 1)),
			NODE()
		);
		FST returnFST("", 4, LEX_RETURN, COMMON_LEX,		// +
			NODE(1, RELATION('r', 1)),
			NODE(1, RELATION('e', 2)),
			NODE(1, RELATION('t', 3)),
			NODE()
		);
		FST printFST("", 5, LEX_PRINT, COMMON_LEX,			// +
			NODE(1, RELATION('p', 1)),
			NODE(1, RELATION('u', 2)),
			NODE(1, RELATION('t', 3)),
			NODE(1, RELATION('s', 4)),
			NODE()
		);
		FST mainFST("", 3, LEX_MAIN, COMMON_LEX,			// +
			NODE(1, RELATION('g', 1)),
			NODE(1, RELATION('o', 2)),
			NODE()
		);

		FST* result = new FST[FST_ARR_SIZE];
		result[0] = dirslashFST;
		result[1] = compareEqualFST;
		result[2] = compareLessFST;
		result[3] = compareMoreFST;
		result[4] = equalFST;
		result[5] = starFST;
		result[6] = minusFST;
		result[7] = plusFST;
		result[8] = righthesisFST;
		result[9] = lefthesisFST;
		result[10] = braceletFST;
		result[11] = leftbraceFST;
		result[12] = commaFST;
		result[13] = semicolonFST;
		result[14] = integerFST;
		result[15] = stringFST;
		result[16] = mainFST;
		result[17] = printFST;
		result[18] = returnFST;
		result[19] = functionFST;
		result[20] = declareFST;
		result[21] = symbollFST;
		result[22] = stringlFST;
		result[23] = numlFST;
		result[24] = untilFST;
		result[25] = symbolFST;
		result[26] = ifFST;
		result[27] = elseFST;
		result[28] = lesslFST;
		result[29] = endFST;
		result[30] = loopFST;
		result[31] = idFST;
		

		return result;
	}

	FST_RESULT CheckLexem(const char* lex)
	{
		FST* arr_of_FST;
		arr_of_FST = arrFST();
		FST_RESULT result;
		for (int i = 0; i < FST_ARR_SIZE; i++)
		{
			arr_of_FST[i].string = lex;
			if (execute(arr_of_FST[i]))
			{
				result.lex = arr_of_FST[i].lex;
				result.lex_type = arr_of_FST[i].lex_type;
				return result;
			}
		}
		return { NULL, LEX_NOT_FOUND };
	}

}
