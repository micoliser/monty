#include "monty.h"

/**
 * op_push - pushes an element to the stack
 * @stack: the stack
 * @lnum: line number
 *
 * Return: void
 */
void op_push(stack_t **stack, unsigned int lnum)
{
	stack_t *new, *temp = *stack;
	int num;

	if (!s.number)
	{
		free_global();
		fprintf(stderr, "L%d: usage: push integer\n", lnum);
		exit(EXIT_FAILURE);
	}
	if (strcmp(s.number, "0") == 0)
		num = 0;
	else
	{
		num = atoi(s.number);
		if (num == 0)
		{
			free_global();
			fprintf(stderr, "L%d: usage: push integer\n", lnum);
			exit(EXIT_FAILURE);
		}
	}
	new = malloc(sizeof(stack_t));
	if (!new)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	new->n = num;
	new->prev = NULL;
	new->next = NULL;

	if (!(*stack))
		*stack = new;
	else
	{
		for (; temp->next; temp = temp->next)
			;
		new->prev = temp;
		temp->next = new;
	}
}

/**
 * op_pall - prints the stack from the top
 * @stack: the stack;
 * @lnum: line number
 *
 * Return: void
 */
void op_pall(stack_t **stack, unsigned int lnum)
{
	stack_t *temp = *stack;

	if (temp)
	{
		for (; temp->next; temp = temp->next)
			;
		for (; temp; temp = temp->prev)
			printf("%d\n", temp->n);
	}

	(void)lnum;
}

/**
 * op_pint - prints the value at the top of the stack
 * @stack: stack
 * @lnum: line number
 *
 * Return: void
 */
void op_pint(stack_t **stack, unsigned int lnum)
{
	stack_t *temp = *stack;

	if (!temp)
	{
		free_global();
		fprintf(stderr, "L%d: can't pint, stack empty\n", lnum);
		exit(EXIT_FAILURE);
	}

	for (; temp->next; temp = temp->next)
		;
	printf("%d\n", temp->n);
}

/**
 * op_pop - removes the top element from the stack
 * @stack: stack
 * @lnum: line number
 *
 * Return: void
 */
void op_pop(stack_t **stack, unsigned int lnum)
{
	stack_t *temp = *stack, *prev;

	if (!temp)
	{
		fprintf(stderr, "L%d: can't pop an empty stack\n", lnum);
		free_global();
		exit(EXIT_FAILURE);
	}

	if (!temp->next)
	{
		*stack = NULL;
		return;
	}

	for (; temp->next->next; temp = temp->next)
		;
	prev = temp->next;
	temp->next = NULL;

	free(prev);
}

/**
 * op_swap - swaps the top two elements of the stack
 * @stack: stack
 * @lnum: line number
 *
 * Return: void
 */
void op_swap(stack_t **stack, unsigned int lnum)
{
	stack_t *temp = *stack, *temp2;

	if (!(*stack) || !(*stack)->next)
	{
		fprintf(stderr, "L%d: can't swap, stack too short\n", lnum);
		exit(EXIT_FAILURE);
	}

	for (; temp->next->next; temp = temp->next)
		;
	temp2 = temp->next;
	temp2->prev = temp->prev;
	temp2->next = temp;
	temp->next = NULL;
	temp->prev = temp2;
}
