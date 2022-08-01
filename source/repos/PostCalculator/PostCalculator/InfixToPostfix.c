#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "ListBaseStack.h"
#pragma warning(disable: 4996)

int GetOpPrec(char op)  // 연산자의 연산 우선순위 정보를 반환한다.
{
	switch(op)
	{
		case '*':
		case '/':
			return 5;  // 가장 높은 연산의 우선순위
		case '+':
		case '-':
			return 3;  // 중간 연산의 우선순위
		case '(':
			return 1;  // 가장 낮은 연산의 우선순위
	}

	return -1;  // 등록되지 않은 연산자임을 알림
}

int WhoPrecOp(char op1, char op2)
{
	int op1prec = GetOpPrec(op1);
	int op2prec = GetOpPrec(op2);

	if (op1prec > op2prec)  // op1의 우선순위가 더 높은 경우
		return 1;
	else if (op1prec < op2prec)  // op2의 우선순위가 더 높은 경우
		return -1;
	else
		return 0;  // 둘의 우선순위가 같은 경우
}

void ConvToRPNExp(char exp[])  // 중위 표현식을 후위 표현식으로 변환하는 함수
{
	Stack stack;
	int explen = strlen(exp);
	char* convExp = (char*)malloc(explen + 1);  // 변환된 수식을 담을 공간 마련, 문자열 길이 + 문자열 끝을 알리는 공백을 넣을 공간만큼 메모리 할당

	int i, idx = 0;
	char tok, popOp;

	memset(convExp, 0, sizeof(char) * explen + 1);  // 할당된 배열을 0으로 초기화
	// convExp 메모리 시작부터 sizeof(char)*explen + 1 바이트를 0의 값으로 채운다.
	StackInit(&stack);

	for (i = 0; i < explen; i++)
	{
		tok = exp[i];  // exp로 전달된 수식을 한 문자씩 tok에 저장
		if (isdigit(tok))  // tok에 저장된 '문자'가 숫자인지 확인
		{
			convExp[idx++] = tok;  // 숫자이면 배열 convExp에 그냥 저장
		}
		else  // 숫자가 아닌 연산자라면
		{
			switch (tok)
			{
			case '(':  // 여는 소괄호라면
				SPush(&stack, tok);  // 스택에 쌓고
				break;

			case ')':  // 닫는 소괄호라면
				while (1)  // 계속 반복해서
				{
					popOp = SPop(&stack);  // 스택에서 연산자를 꺼낸다.
					if (popOp == '(')  // 여는 소괄호를 만날 때 까지
						break;
					convExp[idx++] = popOp;  // 배열 convExp에 저장한다.
				}
				break;

			case '+': case '-':  // 사칙연산자라면
			case '*': case '/':
				while (!SIsEmpty(&stack) && WhoPrecOp(SPeek(&stack), tok) >= 0)
					// 반복을 하는데, 스택이 안비어 있고 스택에 이미 있는 우선순위가 새로 참조하는 우선순위보다 높거나 같은경우
					convExp[idx++] = SPop(&stack);  // 스택에서 꺼내어 새로운 배열에 저장

				SPush(&stack, tok);  // 위 while 문을 빠져나오면 새로운 연산자가 스택에 저장될 적당한 위치를 찾은상황. 따라서 스택에 push 연산
				break;
			}
		}
	}

	while (!SIsEmpty(&stack))  // 스택에 남아있는 연산자를 모두 배열 convExp에 저장
		convExp[idx++] = SPop(&stack);

	strcpy(exp, convExp);  // 기존 문자열을 후위 표기법으로 변경된 문자열로 복사
	free(convExp);  // 변환에 사용된 convExp는 소멸
}
