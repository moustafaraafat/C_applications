/*
 * Real_Calculator.h
 *
 *  Created on: Jun 12, 2020
 *      Author: Raafat
 */

#ifndef REAL_CALCULATOR_H_
#define REAL_CALCULATOR_H_

#include <stdio.h>

/*******************************************************************************
*                      Preprocessor Macros And typedefs                  		*
*******************************************************************************/
#define NUM_STACK_SIZE 	100
#define OPER_STACK_SIZE	100

typedef	enum{
	FALSE, TRUE
}Bool;


/*******************************************************************************
*                     Functions Prototypes for Calculator app (Public)         *
*******************************************************************************/
Bool is_digit_or_decimal_point(char c);
Bool is_digit(char c);
Bool is_decimal_point(char c);
Bool is_operation(char c);
int oper_precedence(char c);
double result_of_operation(double num1, double num2, char oper);

/*******************************************************************************
*                     Functions Prototypes for stacks (Public)                 *
*******************************************************************************/
/* Operations Stack*/
void oper_make_empty(void);
Bool oper_empty_stack(void);
void oper_push(char c);
char oper_pop(void);
char oper_peek(void);
/* Numbers Stack*/
void num_make_empty(void);
Bool num_empty_stack(void);
void num_push(double d);
double num_pop(void);
double num_peek(void);

/*******************************************************************************
*                     Functions Prototypes for handling strings (Public)       *
*******************************************************************************/
void read_line(char *str, int n);

#endif /* REAL_CALCULATOR_H_ */
