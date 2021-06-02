#include <stdio.h>
#include <memory.h> 
#include <stdlib.h>
typedef struct int_stack {	//배열 스택 구조체
	int top; int stack[100]; 
};

typedef  struct  StackNode { //연결 스택 구조체
	int      item; struct  StackNode   *link; 
}; 


int is_empty(int_stack *st) //삭제할 때 사용 : 스택이 비었는지 검사해서 0/1 리턴
{ if (st->top == -1) return 1; else return 0;  }
int is_full(int_stack *st) //삽입할 때 사용 : 스택이 가득차있는지 검사해서 1/0 리턴
{ if (st->top == 99) return 1; else return 0;  }

void int_push(int_stack *st, int item) //st가 가리키는 구조체에 item을 삽입하는 함수
{
	if (is_full(st) == 0)  st->stack[++st->top] = item;	     
	else  printf("\n\n 스택이 가득차 있으므로 삽입 불가!!! \n\n");
}
int int_pop(int_stack *st)//st가 가리키는 구조체에서 top에 위치한 값을 삭제하고 리턴하는 함수
{
	int item;
	if (is_empty(st) == 0) {item = st->stack[st->top--]; return item; }
	else  { printf("\n\n 스택이 비어 있으므로 삭제 불가!!! \n\n"); return -99999; }
}
void st_print(int_stack *st) //스택의 내용ㅇ르 삭제하지 않고 출력만 하는 함수
{
	printf("\n\n 스택에 저장된 데이터 : ");
	for (int i=st->top; i>=0; i--)
		printf(" %d -->", st->stack[i]);
}

StackNode * linked_push(StackNode *stack2, int item)
{
	StackNode  *n = (StackNode *)malloc(sizeof(StackNode)); 
	if(n == NULL){   // 항상 새롭게 생성된 동적구조는 확인절차 필요함
        fprintf(stderr, "메모리 할당에러\n"); return NULL; 
	}
	else {  
		n->item = item;   // 새 노드에 데이터 저장
		n->link = stack2; 
		stack2 = n;
		return stack2;  //연결스택의 구조가 변경되었으므로 헤더포인터 리턴
	}
}

int linked_pop(StackNode *stack2)
{
	if (stack2 == NULL) { printf("\n\n 빈 스택이므로 pop 불가 \n");
	                      return -9999; }
	else {
		int data = stack2->item;
		stack2 = stack2->link;
		return data;
	}
}
void matching() //문자형 스택
{  //문자열 입력-한개씩 입력하면서 엔터키 아닐동안 괄호 비교
	int_stack *paren;  //문자 저장할 스택 선언
	paren = (int_stack *)malloc(sizeof(int_stack));	//배열스택의 포인터 선언
	paren->top = -1;   //스택 초기화
	char ch, p;
	ch = getchar();  //엔터키 걸러내기

	printf("\n 괄호있는 문자열 입력 : ");  //입력 예 ({[x = 25;]})
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
						{  printf("\n\n 여는 괄호가 부족해서 에러!!!\n\n");
					       exit(1); //함수 종료
					    }
			         if ((p=='(' && ch == ')') || (p=='{' && ch == '}') ||
						 (p=='[' && ch == ']')) continue;
					 else printf("\n\n 괄호 유형이 달라서 에러!!!\n\n");
		  default: continue;  break;
		}
    }
	//스택에 아직 괄호가 남았는지 검사 ==> 닫는 괄호가 부족해서 에러
	if (paren->top >= 0)
		printf("\n\n 닫는 괄호가 부족해서 에러!!!\n\n" );
	else
		printf("\n괄호 매칭이 정상적으로 수행됨 ...\n");
}

void calc() //후위표기식을 입력하면 계산해서 출력하는 함수
{
	int_stack *in; 
	char ch; int data1, data2;
	in = (int_stack *)malloc(sizeof(int_stack));
	in->top = -1;   //스택 초기화	
	ch = getchar();  //엔터키 걸러내기
	printf("\n 후위표기식 입력(예 : 82/3-45*+) : ");  

	while (1) {
		ch = getchar();
		if (ch == '\n') break;
		if (ch != '+' && ch != '-' && ch != '*' && ch != '/')
			int_push(in, ch-'0');  //데이터이므로 정수처리해서 스택에 push
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
	printf("\n\n 후위표기식의 연산결과 = %d \n\n", int_pop(in));
}
int prec(char op) //연산자 우선순위 값 리턴
{
	switch (op) {
        case '(' : case ')'  : return 0; // 제일 꼴지
        case '+' : case '-'  : return 1; // 중간 순위
        case '*' : case '/'  : return 2; // 최강 순위
    }
    return -1;
 }

void postfix()//중위표기식을 입력하면 후위표기식으로 출력하는 함수
{
	int_stack *post; 
	char ch, p; 
	post = (int_stack *)malloc(sizeof(int_stack));
	post->top = -1;   //스택 초기화	
	ch = getchar();  //엔터키 걸러내기
	printf("\n 중위표기식 입력(예 : (1+2)*(3-4) : ");  
	while (1) {
		ch = getchar();
		if (ch == '\n') break;
		switch (ch)
		{ //연산자일 때
		  case '+' : case '-' : case '*' : case '/' : 
			  if (prec(ch) > prec(post->stack[post->top])) //입력 연산자 > 스택 연산자       
				  int_push(post, ch);
			  else  //입력 연산자 <= 스택 연산자       
			  {   while (prec(ch) <= prec(post->stack[post->top]))
				     putchar(int_pop(post));
			      int_push(post, ch);
			  }
			  break;
          //데이터일 때
		  case '0' : case '1' : case '2' : case '3' : 
		  case '4' : case '5' : case '6' : case '7' :
		  case '8' : case '9' : putchar(ch);
			         break;
          //open 괄호일 때
		  case '(' : int_push(post, ch); break;

		  //closed 괄호일 때
		  case ')' : while (post->stack[post->top] != '(')
						  putchar(int_pop(post));
			         p = int_pop(post);  //여는 괄호를 pop해서 버림
			         break;
		default: break;
		}
	}
	//while문을 빠져나오면 스택의 모든 연산자를 차례대로 출력
	while (post->top > -1)  putchar(int_pop(post));
}

void main()
{
	int menu, item;
	int_stack *stack1;   
	StackNode *stack2, *p;
	stack1 = (int_stack *)malloc(sizeof(int_stack));	//배열스택의 포인터 선언
	stack2 = (StackNode *)malloc(sizeof(StackNode));	//여결스택의 포인터 선언
	stack1->top = -1;  //배열스택 초기화
	stack2 = NULL;     //연결스택 초기화

	while (1) {
		printf("\n\n 5장 스택 1)배열push 2)배열pop  3)배열스택 출력 4)연결push  5)연결pop  6)연결스택 출력  7)괄호매칭  8)연산  9)수식입력  10)종료 : ");
		scanf_s("%d", &menu); 
		if (menu == 10) break;
		switch (menu)
		{
		case 1: printf("\n 스택에 푸시할 정수 : "); scanf_s("%d", &item);
			    int_push(stack1, item); break;
		case 2: item = int_pop(stack1);
			    printf("\n\n 방금 스택에서 팝된 정수 : %d", item);
			    break;	
		case 3: st_print(stack1); 
			    break;	
		case 4: //연결스택에서의 동작
			    printf("\n 스택에 푸시할 정수 : "); scanf_s("%d", &item);
			    stack2 = linked_push(stack2, item); break;
		case 5: item = linked_pop(stack2);
			    printf("\n\n 방금 스택에서 팝된 정수 : %d", item);
			    break;	
		case 6: p = stack2;
   			    while (p != NULL) 
			    { printf(" %d-->", p->item); p = p->link; }
				break;
		case 7: p = stack2;//괄호가 있는 문자열을 입력하여 괄호 매칭 검사
				while (p != NULL){
				
				}
			    matching(); break;
		case 8 ://후위표기식을 입력하면 계산해서 출력하는 메뉴
			    calc();  break;
		case 9 : //중위표기식을 입력하면 후위표기식으로 출력하는 메뉴
			    postfix();  break;
		default: printf("\n 메뉴선택 오류, 재선택...\n"); break;
		}
	}
}