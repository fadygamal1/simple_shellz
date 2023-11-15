#include <stdio.h>

/**
 * struct ALXStudent - Represents an ALX student with a full name and age.
 * @full_name: The full name of the ALX student.
 * @years_old: The age of the ALX student.
 */
typedef struct ALXStudent {
    char *full_name;
    int years_old;
} ALXStudent;

/**
 * print_alxstudent_info - Prints information about an ALX student.
 * @student: The ALX student whose information will be printed.
 */
void print_alxstudent_info(const ALXStudent *student)
{
    if (student != NULL) {
        printf("Full Name: %s\n", student->full_name);
        printf("Age: %d\n", student->years_old);
    } else {
        fprintf(stderr, "Error: Invalid ALX student\n");
    }
}

/**
 * main - Entry point of the program.
 * Return: 0 on success, non-zero on failure.
 */
int main(void)
{
    ALXStudent first_alxstudent = {"Alice", 25};
    ALXStudent second_alxstudent = {"Bob", 30};

    printf("ALX Student Information:\n");
    printf("=======================\n");

    printf("First ALX Student's Information:\n");
    print_alxstudent_info(&first_alxstudent);

    printf("\nSecond ALX Student's Information:\n");
    print_alxstudent_info(&second_alxstudent);

    return 0;
}
