/*
 * File: beautiful_code.c
 * Author: Your Name
 * Description: A beautiful C program that passes Betty checks.
 */

#include <stdio.h>

/*
 * greet_user - Greets the user
 *
 * This function prints a greeting message to the user.
 */
void greet_user(void)
{
	printf("Hello, welcome to the beautiful code example!\n");
}

/*
 * main - The main function
 *
 * This is the entry point of the program.
 */
int main(void)
{
	greet_user();

	/* Some beautiful code here */
	for (int i = 0; i < 5; i++) {
		printf("This is iteration %d\n", i + 1);
	}

	return 0;
}
