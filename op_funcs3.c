#include "monty.h"

/**
 * op_mod - computes the rest of the division of the second top
 * element of the stack by the top element of the stack
 * @stack: stack
 * @lnum: line number
 *
 * Return: void
 */
void op_mod(stack_t **stack, unsigned int lnum)
{
	stack_t *temp = *stack;
	char *num;

	if (!(*stack) || !(*stack)->next)
	{
		free_global();
		fprintf(stderr, "L%d: can't mod, stack too short\n", lnum);
		exit(EXIT_FAILURE);
	}

	for (; temp->next->next; temp = temp->next)
		;
	if (temp->next->n == 0)
	{
		free_global();
		fprintf(stderr, "L%d: division by zero\n", lnum);
		exit(EXIT_FAILURE);
	}

	num = _itoa(temp->n % temp->next->n);

	op_pop(stack, lnum);
	op_pop(stack, lnum);

	s.number = num;
	op_push(stack, lnum);

	free(num);
}

/**
 * op_pchar - prints the char at the top of the stack
 * @stack: stack
 * @lnum: line number
 *
 * Return: void
 */
void op_pchar(stack_t **stack, unsigned int lnum)
{
	stack_t *temp = *stack;
	int num;

	if (!(*stack))
	{
		fprintf(stderr, "L%d: can't pchar, stack empty\n", lnum);
		free_global();
		exit(EXIT_FAILURE);
	}

	for (; temp->next; temp = temp->next)
		;
	num = temp->n;
	if (num < 0 || num > 127)
	{
		fprintf(stderr, "L%d: can't pchar, value out of range\n", lnum);
		free_global();
		exit(EXIT_FAILURE);
	}

	putchar(num);
	putchar('\n');
}

/**
 * op_pstr - prints the string starting from the top
 * @stack: stack
 * @lnum: line number
 *
 * Return:void
 */
void op_pstr(stack_t **stack, unsigned int lnum)
{
	stack_t *temp = *stack;
	int num;

	if (!(*stack))
		putchar('\n');
	else
	{
		for (; temp->next; temp = temp->next)
			;

		for (; temp; temp = temp->prev)
		{
			num = temp->n;
			if (num == 0 || num < 0 || num > 127)
				break;

			putchar(num);
		}
		putchar('\n');
	}

	(void)lnum;
}
