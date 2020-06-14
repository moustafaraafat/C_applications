/*
 * Real_Calculator.c
 *
 *  Created on: Jun 12, 2020
 *      Author: Raafat
 */
#include "Real_Calculator.h"

/*******************************************************************************
 *							Global Variables				                    *
 *******************************************************************************/
double 	num_content[NUM_STACK_SIZE];
char 	oper_content[OPER_STACK_SIZE];
int 	num_top = 0;
int 	oper_top = 0;

/*******************************************************************************
 *                      Functions Definitions for Calculator app                *
 *******************************************************************************/

Bool is_digit_or_decimal_point(char c){
	return ((c >= '0' && c <= '9') || (c == '.'));
}
Bool is_digit(char c){
	return (c >= '0' && c <= '9');
}
Bool is_decimal_point(char c){
	return (c == '.');
}
Bool is_operation(char c){
	return (c == '+' || c == '-' || c == '*' ||
			c == '/' || c == '(' || c == ')');
}
int oper_precedence(char c){
	int precedence = -2;
	switch(c)
	{
	case '(': case ')':
		precedence = 2;
		break;
	case '*': case '/':
		precedence = 1;
		break;
	case '+': case '-':
		precedence = 0;
		break;
	default:
		break;
	}
	return precedence;
}
double result_of_operation(double num1, double num2, char oper){
	double result = 0;
	switch(oper)
	{
	case '+':
		result = num1 + num2;
		break;
	case '-':
		result = num1 - num2;
		break;
	case '*':
		result = num1 * num2;
		break;
	case '/':
		result = num1 / num2;
		if(num2 == 0)
			printf("MATH ERROR!\n");
		break;
	default:
		printf("Invalid operator!\n");
		break;
	}
	return result;
}
/*******************************************************************************
 *                      Functions Definitions for stacks                        *
 *******************************************************************************/
/* Operations Stack*/
Bool oper_empty_stack(void){
	return 0==oper_top;
}
void oper_push(char c){
	oper_content[oper_top++]=c;
}
char oper_pop(void){
	return oper_content[--oper_top];
}
char oper_peek(void){
	return oper_content[oper_top - 1];
}
void oper_make_empty(void){
	oper_top=0;
}
/* Numbers Stack*/
Bool num_empty_stack(void){
	return 0==num_top;
}
void num_push(double d){
	num_content[num_top++]=d;
}
double num_pop(void){
	return num_content[--num_top];
}
double num_peek(void){
	return num_content[num_top - 1];
}
void num_make_empty(void){
	num_top=0;
}

/*******************************************************************************
 *                     Functions Definitions for handling strings (Public)       *
 *******************************************************************************/
void read_line(char *str, int n){
	int ch, i = 0;
	while ((ch = getchar()) != '\n')
		if (i < n)
			str[i++] = ch;
	str[i] = '\0';
}
