#include <stdio.h>
#include <memory.h> 
#include <stdlib.h>
typedef struct int_stack {	//�迭 ���� ����ü
	int top; int stack[100]; 
};

typedef  struct  StackNode { //���� ���� ����ü
	int      item; struct  StackNode   *link; 
}; 


int is_empty(int_stack *st) //������ �� ��� : ������ ������� �˻��ؼ� 0/1 ����
{ if (st->top == -1) return 1; else return 0;  }
int is_full(int_stack *st) //������ �� ��� : ������ �������ִ��� �˻��ؼ� 1/0 ����
{ if (st->top == 99) return 1; else return 0;  }

void int_push(int_stack *st, int item) //st�� ����Ű�� ����ü�� item�� �����ϴ� �Լ�
{
	if (is_full(st) == 0)  st->stack[++st->top] = item;	     
	else  printf("\n\n ������ ������ �����Ƿ� ���� �Ұ�!!! \n\n");
}
int int_pop(int_stack *st)//st�� ����Ű�� ����ü���� top�� ��ġ�� ���� �����ϰ� �����ϴ� �Լ�
{
	int item;
	if (is_empty(st) == 0) {item = st->stack[st->top--]; return item; }
	else  { printf("\n\n ������ ��� �����Ƿ� ���� �Ұ�!!! \n\n"); return -99999; }
}
void st_print(int_stack *st) //������ ���뤷�� �������� �ʰ� ��¸� �ϴ� �Լ�
{
	printf("\n\n ���ÿ� ����� ������ : ");
	for (int i=st->top; i>=0; i--)
		printf(" %d -->", st->stack[i]);
}

StackNode * linked_push(StackNode *stack2, int item)
{
	StackNode  *n = (StackNode *)malloc(sizeof(StackNode)); 
	if(n == NULL){   // �׻� ���Ӱ� ������ ���������� Ȯ������ �ʿ���
        fprintf(stderr, "�޸� �Ҵ翡��\n"); return NULL; 
	}
	else {  
		n->item = item;   // �� ��忡 ������ ����
		n->link = stack2; 
		stack2 = n;
		return stack2;  //���ὺ���� ������ ����Ǿ����Ƿ� ��������� ����
	}
}

int linked_pop(StackNode *stack2)
{
	if (stack2 == NULL) { printf("\n\n �� �����̹Ƿ� pop �Ұ� \n");
	                      return -9999; }
	else {
		int data = stack2->item;
		stack2 = stack2->link;
		return data;
	}
}
void matching() //������ ����
{  //���ڿ� �Է�-�Ѱ��� �Է��ϸ鼭 ����Ű �ƴҵ��� ��ȣ ��
	int_stack *paren;  //���� ������ ���� ����
	paren = (int_stack *)malloc(sizeof(int_stack));	//�迭������ ������ ����
	paren->top = -1;   //���� �ʱ�ȭ
	char ch, p;
	ch = getchar();  //����Ű �ɷ�����

	printf("\n ��ȣ�ִ� ���ڿ� �Է� : ");  //�Է� �� ({[x = 25;]})
	while (1)
    {
		ch = getchar();
		if (ch == '\n') break;
		switch (ch)	{
		  case '(' : 
		  case '{' : 
		  case '[' :  int_push(paren, ch); break; 
		  case ')' :
		  case '}' :
		  case ']' : p = int_pop(paren);
			         if (p == -99999) 
						{  printf("\n\n ���� ��ȣ�� �����ؼ� ����!!!\n\n");
					       exit(1); //�Լ� ����
					    }
			         if ((p=='(' && ch == ')') || (p=='{' && ch == '}') ||
						 (p=='[' && ch == ']')) continue;
					 else printf("\n\n ��ȣ ������ �޶� ����!!!\n\n");
		  default: continue;  break;
		}
    }
	//���ÿ� ���� ��ȣ�� ���Ҵ��� �˻� ==> �ݴ� ��ȣ�� �����ؼ� ����
	if (paren->top >= 0)
		printf("\n\n �ݴ� ��ȣ�� �����ؼ� ����!!!\n\n" );
	else
		printf("\n��ȣ ��Ī�� ���������� ����� ...\n");
}

void calc() //����ǥ����� �Է��ϸ� ����ؼ� ����ϴ� �Լ�
{
	int_stack *in; 
	char ch; int data1, data2;
	in = (int_stack *)malloc(sizeof(int_stack));
	in->top = -1;   //���� �ʱ�ȭ	
	ch = getchar();  //����Ű �ɷ�����
	printf("\n ����ǥ��� �Է�(�� : 82/3-45*+) : ");  

	while (1) {
		ch = getchar();
		if (ch == '\n') break;
		if (ch != '+' && ch != '-' && ch != '*' && ch != '/')
			int_push(in, ch-'0');  //�������̹Ƿ� ����ó���ؼ� ���ÿ� push
		else {
			switch (ch)	{
			case '+' :data2 = int_pop(in);  data1 = int_pop(in);
				       int_push(in, data1+data2);   break;
			case '-' :data2 = int_pop(in);  data1 = int_pop(in);
				       int_push(in, data1-data2);   break;
			case '*' :data2 = int_pop(in);  data1 = int_pop(in);
				       int_push(in, data1*data2);   break;
			case '/' : data2 = int_pop(in);  data1 = int_pop(in);
				       int_push(in, data1/data2);   break;
			default: break;
			}
		}
	}
	printf("\n\n ����ǥ����� ������ = %d \n\n", int_pop(in));
}
int prec(char op) //������ �켱���� �� ����
{
	switch (op) {
        case '(' : case ')'  : return 0; // ���� ����
        case '+' : case '-'  : return 1; // �߰� ����
        case '*' : case '/'  : return 2; // �ְ� ����
    }
    return -1;
 }

void postfix()//����ǥ����� �Է��ϸ� ����ǥ������� ����ϴ� �Լ�
{
	int_stack *post; 
	char ch, p; 
	post = (int_stack *)malloc(sizeof(int_stack));
	post->top = -1;   //���� �ʱ�ȭ	
	ch = getchar();  //����Ű �ɷ�����
	printf("\n ����ǥ��� �Է�(�� : (1+2)*(3-4) : ");  
	while (1) {
		ch = getchar();
		if (ch == '\n') break;
		switch (ch)
		{ //�������� ��
		  case '+' : case '-' : case '*' : case '/' : 
			  if (prec(ch) > prec(post->stack[post->top])) //�Է� ������ > ���� ������       
				  int_push(post, ch);
			  else  //�Է� ������ <= ���� ������       
			  {   while (prec(ch) <= prec(post->stack[post->top]))
				     putchar(int_pop(post));
			      int_push(post, ch);
			  }
			  break;
          //�������� ��
		  case '0' : case '1' : case '2' : case '3' : 
		  case '4' : case '5' : case '6' : case '7' :
		  case '8' : case '9' : putchar(ch);
			         break;
          //open ��ȣ�� ��
		  case '(' : int_push(post, ch); break;

		  //closed ��ȣ�� ��
		  case ')' : while (post->stack[post->top] != '(')
						  putchar(int_pop(post));
			         p = int_pop(post);  //���� ��ȣ�� pop�ؼ� ����
			         break;
		default: break;
		}
	}
	//while���� ���������� ������ ��� �����ڸ� ���ʴ�� ���
	while (post->top > -1)  putchar(int_pop(post));
}

void main()
{
	int menu, item;
	int_stack *stack1;   
	StackNode *stack2, *p;
	stack1 = (int_stack *)malloc(sizeof(int_stack));	//�迭������ ������ ����
	stack2 = (StackNode *)malloc(sizeof(StackNode));	//���ὺ���� ������ ����
	stack1->top = -1;  //�迭���� �ʱ�ȭ
	stack2 = NULL;     //���ὺ�� �ʱ�ȭ

	while (1) {
		printf("\n\n 5�� ���� 1)�迭push 2)�迭pop  3)�迭���� ��� 4)����push  5)����pop  6)���ὺ�� ���  7)��ȣ��Ī  8)����  9)�����Է�  10)���� : ");
		scanf_s("%d", &menu); 
		if (menu == 10) break;
		switch (menu)
		{
		case 1: printf("\n ���ÿ� Ǫ���� ���� : "); scanf_s("%d", &item);
			    int_push(stack1, item); break;
		case 2: item = int_pop(stack1);
			    printf("\n\n ��� ���ÿ��� �˵� ���� : %d", item);
			    break;	
		case 3: st_print(stack1); 
			    break;	
		case 4: //���ὺ�ÿ����� ����
			    printf("\n ���ÿ� Ǫ���� ���� : "); scanf_s("%d", &item);
			    stack2 = linked_push(stack2, item); break;
		case 5: item = linked_pop(stack2);
			    printf("\n\n ��� ���ÿ��� �˵� ���� : %d", item);
			    break;	
		case 6: p = stack2;
   			    while (p != NULL) 
			    { printf(" %d-->", p->item); p = p->link; }
				break;
		case 7: p = stack2;//��ȣ�� �ִ� ���ڿ��� �Է��Ͽ� ��ȣ ��Ī �˻�
				while (p != NULL){
				
				}
			    matching(); break;
		case 8 ://����ǥ����� �Է��ϸ� ����ؼ� ����ϴ� �޴�
			    calc();  break;
		case 9 : //����ǥ����� �Է��ϸ� ����ǥ������� ����ϴ� �޴�
			    postfix();  break;
		default: printf("\n �޴����� ����, �缱��...\n"); break;
		}
	}
}