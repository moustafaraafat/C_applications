/*
 * main.c
 *
 *  Created on: Jun 12, 2020
 *      Author: Raafat
 *
 *  Description: This is an advanced calculator, which supports operations
 *  on Float numbers such as ‘+’, ‘-’, ‘*’, ‘/’, and ().
 *  It accepts expressions like 15*(4+3) - (11/(2*3) + 7)
 *  This release doesn't support expressions like 5(3+4)
 *  it should be written as 5*(3+4)
 *  Spaces are allowed
 */
#include <stdio.h>
#include "Real_Calculator.h"

#define EXPRESSION_LEN	100

int main(void)
{
	setbuf(stdout, NULL);		/*To solve printing problem in Eclipse*/

	char 	expression[EXPRESSION_LEN] = {0};
	double 	currentNum = 0, result = 0, tens = 10;
	char	currentChar = 0;
	int 	ind = 0;
	Bool	decimal_flag = FALSE;

	while(1)
	{
		/*Read the entire mathematical expression*/
		printf("Enter an expression\n");
		read_line(expression, EXPRESSION_LEN);
		/*Work on that expression until it reaches '\0'*/
		while(expression[ind])
		{
			currentChar = expression[ind];
			/*Store the number in currentNum*/
			if(is_digit_or_decimal_point(currentChar))
			{
				if(is_digit(currentChar))
				{
					/*Save the whole part*/
					if(!decimal_flag){
						currentNum = currentNum*10 + (currentChar - '0');
					}
					/*Save the decimal part (if there's any)*/
					else{
						currentNum = currentNum + (currentChar - '0')/(tens);
						tens *= 10;
					}

				}
				else if(is_decimal_point(currentChar))
				{
					decimal_flag = TRUE;
				}
			}
			else if(is_operation(currentChar))
			{
				/*Here we check if it's an open '('  it's the first if,
				 *  such that if the whole expression started with (
				 *  like (5+3)+9 */
				if(currentChar == '(')
				{
					/*Here we don't push number, as it's already pushed
					 * i.e. we don't support expr. like: 5(2+4) it should be 5*(2+4)*/
					oper_push(currentChar);
					currentNum = 0;
				}
				/*Here we check if stack is empty, we fill with the first num and oper*/
				else if(num_empty_stack())
				{
					num_push(currentNum);
					currentNum = 0;
					oper_push(currentChar);
				}
				/*If it's ')' keep doing operations until we reach '('*/
				else if(currentChar == ')')
				{
					while( oper_peek() != '(' ){
						currentNum = result_of_operation(num_pop(), currentNum, oper_pop());
					}
					oper_pop(); /*pop the '('*/
				}
				/*Here the operation is ‘+’, ‘-’, ‘*’, ‘/’*/
				else
				{
					/*if current oper has higher precedence then the last one in stack
					 * we will push both num and operation into stack.
					 * i.e. don’t evaluate last operation in stack, cause we got a higher one.
					 * */
					if( oper_precedence(currentChar) > oper_precedence(oper_peek()) )
					{
						num_push(currentNum);
						currentNum = 0;
						oper_push(currentChar);
					}
					/*else, lower precedence, do the last operation in the stack*/
					else
					{
						/*And keep digging down on the stacks until it’s empty or the
						 * precedence of current operator became higher than the one in the stack
						 * that is to handle situation like  5-2*1+10 => 5-2+10 now instead of
						 * doing 2+10 first it will be 5-12 = - 7 which is wrong, so we keep
						 * digging down on the stack like: 5-2*1+10 => 5-2+10 => 3+10*/
						/*But digging down without checking precedence will cause problems like
						 * 2+3*3*3 => 2+9*3 if we dig with no check it will be 11*3 which is wrong
						 * so we check precedence again. It will be 2+3*3*3 => 2+9*3 =>2+27=31*/
						while(!oper_empty_stack() &&
								oper_precedence(currentChar) <= oper_precedence(oper_peek()) &&
								oper_peek() != '('){
							currentNum = result_of_operation(num_pop(), currentNum, oper_pop());
						}
						num_push(currentNum);
						currentNum = 0;
						oper_push(currentChar);
					}
				}
				/*Re-init tens and clear dec flag, as we already stored the num*/
				tens = 10;
				decimal_flag = FALSE;
			}
			/*Herein, we allow spaces*/
			else if(currentChar != ' '){
				printf("Illegal Characters\n");
				break;
			}

			ind++;
		}
		/*This if finishes the last operation in stack
		 * we do a check, as if only one number entered,
		 * we just print it without calling result_of_operation*/
		while(!oper_empty_stack()){
			currentNum = result_of_operation(num_pop(), currentNum, oper_pop());
		}
		result = currentNum;
		printf("Result = %.2f\n", result);
		/*Here, I empty the two stacks,
		 * make currentNum = 0 as it'll get multiplied by 10
		 * make index = 0, to start looping from 0 in the next string*/
		num_make_empty();
		oper_make_empty();
		currentNum = 0;
		ind = 0;
		tens = 10;
		decimal_flag = FALSE;
		/*Now the operation is ended, and we start a brand new expression*/
	}
	return 0;
}
