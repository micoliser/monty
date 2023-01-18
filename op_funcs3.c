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
