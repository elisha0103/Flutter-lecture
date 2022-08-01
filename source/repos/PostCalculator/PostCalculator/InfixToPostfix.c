#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "ListBaseStack.h"
#pragma warning(disable: 4996)

int GetOpPrec(char op)  // �������� ���� �켱���� ������ ��ȯ�Ѵ�.
{
	switch(op)
	{
		case '*':
		case '/':
			return 5;  // ���� ���� ������ �켱����
		case '+':
		case '-':
			return 3;  // �߰� ������ �켱����
		case '(':
			return 1;  // ���� ���� ������ �켱����
	}

	return -1;  // ��ϵ��� ���� ���������� �˸�
}

int WhoPrecOp(char op1, char op2)
{
	int op1prec = GetOpPrec(op1);
	int op2prec = GetOpPrec(op2);

	if (op1prec > op2prec)  // op1�� �켱������ �� ���� ���
		return 1;
	else if (op1prec < op2prec)  // op2�� �켱������ �� ���� ���
		return -1;
	else
		return 0;  // ���� �켱������ ���� ���
}

void ConvToRPNExp(char exp[])  // ���� ǥ������ ���� ǥ�������� ��ȯ�ϴ� �Լ�
{
	Stack stack;
	int explen = strlen(exp);
	char* convExp = (char*)malloc(explen + 1);  // ��ȯ�� ������ ���� ���� ����, ���ڿ� ���� + ���ڿ� ���� �˸��� ������ ���� ������ŭ �޸� �Ҵ�

	int i, idx = 0;
	char tok, popOp;

	memset(convExp, 0, sizeof(char) * explen + 1);  // �Ҵ�� �迭�� 0���� �ʱ�ȭ
	// convExp �޸� ���ۺ��� sizeof(char)*explen + 1 ����Ʈ�� 0�� ������ ä���.
	StackInit(&stack);

	for (i = 0; i < explen; i++)
	{
		tok = exp[i];  // exp�� ���޵� ������ �� ���ھ� tok�� ����
		if (isdigit(tok))  // tok�� ����� '����'�� �������� Ȯ��
		{
			convExp[idx++] = tok;  // �����̸� �迭 convExp�� �׳� ����
		}
		else  // ���ڰ� �ƴ� �����ڶ��
		{
			switch (tok)
			{
			case '(':  // ���� �Ұ�ȣ���
				SPush(&stack, tok);  // ���ÿ� �װ�
				break;

			case ')':  // �ݴ� �Ұ�ȣ���
				while (1)  // ��� �ݺ��ؼ�
				{
					popOp = SPop(&stack);  // ���ÿ��� �����ڸ� ������.
					if (popOp == '(')  // ���� �Ұ�ȣ�� ���� �� ����
						break;
					convExp[idx++] = popOp;  // �迭 convExp�� �����Ѵ�.
				}
				break;

			case '+': case '-':  // ��Ģ�����ڶ��
			case '*': case '/':
				while (!SIsEmpty(&stack) && WhoPrecOp(SPeek(&stack), tok) >= 0)
					// �ݺ��� �ϴµ�, ������ �Ⱥ�� �ְ� ���ÿ� �̹� �ִ� �켱������ ���� �����ϴ� �켱�������� ���ų� �������
					convExp[idx++] = SPop(&stack);  // ���ÿ��� ������ ���ο� �迭�� ����

				SPush(&stack, tok);  // �� while ���� ���������� ���ο� �����ڰ� ���ÿ� ����� ������ ��ġ�� ã����Ȳ. ���� ���ÿ� push ����
				break;
			}
		}
	}

	while (!SIsEmpty(&stack))  // ���ÿ� �����ִ� �����ڸ� ��� �迭 convExp�� ����
		convExp[idx++] = SPop(&stack);

	strcpy(exp, convExp);  // ���� ���ڿ��� ���� ǥ������� ����� ���ڿ��� ����
	free(convExp);  // ��ȯ�� ���� convExp�� �Ҹ�
}
