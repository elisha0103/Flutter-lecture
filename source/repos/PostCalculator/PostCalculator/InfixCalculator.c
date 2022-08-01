#include <string.h>
#include <stdlib.h>
#include "InfixToPostfix.h"  // ConvToRPNExp 함수의 호출을 위함
#include "PostCalculator.h"  // EvalRPNExp 함수의 호출을 위함
#pragma warning(disable: 4996)

int EvalInfixExp(char exp[])
{
	int len = strlen(exp);
	int ret;
	char* expcpy = (char*)malloc(len + 1);  // 문자열 저장공간 마련
	strcpy(expcpy, exp);  // 전달된 문자열의 변경을 막기 위해 다른 배열에 복사

	ConvToRPNExp(expcpy);  // 후위 표기법의 수식으로 변환
	ret = EvalRPNExp(expcpy);  // 변화된 수식의 계산

	free(expcpy);  // 문자열 저장공간 해제
	return ret;  // 계산결과 반환
}