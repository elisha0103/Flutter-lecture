#ifndef __LB_STACK_H__
#define __LB_STACK_H__

#define TRUE 1
#define FALSE 0

typedef int Data;

typedef struct _node  // ���� ����Ʈ�� ��带 ǥ���� ����ü
{
	Data data;
	struct _node* next;
} Node;

typedef struct _liststack  // ���� ����Ʈ ��� ������ ǥ���� ����ü
{
	Node* head;
} ListStack;

typedef ListStack Stack;

void StackInit(Stack* pstack);  // ���� �ʱ�ȭ
int SIsEmpty(Stack* pstack);  // ������ ������� Ȯ��

void SPush(Stack* pstack, Data data);  // ������ push ����
Data SPop(Stack* pstack);  // ������ pop ����
Data Speek(Stack* pstack);  // ������ peek ����

#endif