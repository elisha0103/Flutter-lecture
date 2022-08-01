#include <string.h>
#include <stdlib.h>
#include "InfixToPostfix.h"  // ConvToRPNExp �Լ��� ȣ���� ����
#include "PostCalculator.h"  // EvalRPNExp �Լ��� ȣ���� ����
#pragma warning(disable: 4996)

int EvalInfixExp(char exp[])
{
	int len = strlen(exp);
	int ret;
	char* expcpy = (char*)malloc(len + 1);  // ���ڿ� ������� ����
	strcpy(expcpy, exp);  // ���޵� ���ڿ��� ������ ���� ���� �ٸ� �迭�� ����

	ConvToRPNExp(expcpy);  // ���� ǥ����� �������� ��ȯ
	ret = EvalRPNExp(expcpy);  // ��ȭ�� ������ ���

	free(expcpy);  // ���ڿ� ������� ����
	return ret;  // ����� ��ȯ
}