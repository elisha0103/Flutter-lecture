#include <string.h>
#include <ctype.h>
#include "ListBaseStack.h"

int EvalRPNExp(char exp[])
{
	Stack stack;
	int explen = strlen(exp);
	int i;
	char tok, op1, op2;

	StackInit(&stack);

	for (i = 0; i < explen; i++)  // ������ �����ϴ� ���� ������ ������� �ݺ�
	{
		tok = exp[i];  // �� ���ھ� tok�� �����ϰ�,

		if (isdigit(tok))  // '����'�� ������ �������� Ȯ��
		{
			SPush(&stack, tok - '0');  // ������ ���ڷ� ��ȯ �� ���ÿ� PUSH
		}
		else
		{
			op2 = SPop(&stack);  // ���ÿ��� �� ��° �ǿ����ڸ� ������.
			op1 = SPop(&stack);  // ���ÿ��� ù ��° �ǿ����ڸ� ������.

			switch (tok)  // �����ϰ� �� ����� �ٽ� ���ÿ� PUSH
			{
			case '+':
				SPush(&stack, op1 + op2);
				break;
			case '-':
				SPush(&stack, op1 - op2);
				break;
			case '*':
				SPush(&stack, op1 * op2);
				break;
			case '/':
				SPush(&stack, op1 / op2);
				break;
			}
		}
	}
	return SPop(&stack);  // ������ �������� ���ÿ��� ������ ��ȯ
}