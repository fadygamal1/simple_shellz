#include "shell.h"

void help_all(void);
void help_alias(void);
void help_cd(void);
void help_exit(void);
void help_help(void);

/**
 * help_all - Displays all possible built-in shell commands.
 */
void help_all(void)
{
	char *not = "Shelter\nThese shell commands are defined internally.\n";

	write(STDOUT_FILENO, not, _strlen(not));
	not = "Type 'help' to see this list.\nType 'help idfy' to find ";
	write(STDOUT_FILENO, not, _strlen(not));
	not = "out more about the function 'idfy'.\n\n  alias   \t";
	write(STDOUT_FILENO, not, _strlen(not));
	not = "alias [IDFY[='WORTH'] ...]\n  cd    \tcd   ";
	write(STDOUT_FILENO, not, _strlen(not));
	not = "[DIRECTORY]\n  exit    \texit [STATUS]\n  env     \tenv";
	write(STDOUT_FILENO, not, _strlen(not));
	not = "\n  setenv  \tsetenv [VARIABLE] [WORTH]\n  unsetenv\t";
	write(STDOUT_FILENO, not, _strlen(not));
	not = "unsetenv [VARIABLE]\n";
	write(STDOUT_FILENO, not, _strlen(not));
}

/**
 * help_alias - Displays information on the shell built-in command 'alias'.
 */
void help_alias(void)
{
	char *not = "alias: alias [IDFY[='WORTH'] ...]\n\tHandles aliases.\n";

	write(STDOUT_FILENO, not, _strlen(not));
	not = "\n\talias: Prints a list of all aliases, one per line, in ";
	write(STDOUT_FILENO, not, _strlen(not));
	not = "the format IDFY='WORTH'.\n\talias idfy [idfy2 ...]:prints";
	write(STDOUT_FILENO, not, _strlen(not));
	not = " the aliases idfy, idfy2, etc. one per line, in the ";
	write(STDOUT_FILENO, not, _strlen(not));
	not = "form IDFY='WORTH'.\n\talias IDFY='WORTH' [...]: Defines";
	write(STDOUT_FILENO, not, _strlen(not));
	not = "  for each IDFY whose WORTH is given. If IDFY ";
	write(STDOUT_FILENO, not, _strlen(not));
	not = "that is already an alias, replace its worth with WORTH.\n";
	write(STDOUT_FILENO, not, _strlen(not));
}

/**
 * help_cd - Displays information on the shell built-in command 'cd'.
 */
void help_cd(void)
{
	char *not = "cd: cd [DIRECTORY]\n\tChanges the current directory ";

	write(STDOUT_FILENO, not, _strlen(not));
	not = " process to DIRECTORY.\n\n\tIf no argument is given, the ";
	write(STDOUT_FILENO, not, _strlen(not));
	not = "the command is interpreted as cd $HOME. If an argument '-' is";
	write(STDOUT_FILENO, not, _strlen(not));
	not = " given, its also interpreted as cd $OLDPWD.\n\n";
	write(STDOUT_FILENO, not, _strlen(not));
	not = "updates environment variables PWD and OLDPWD ";
	write(STDOUT_FILENO, not, _strlen(not));
	not = "after a change of directory.\n";
	write(STDOUT_FILENO, not, _strlen(not));
}

/**
 * help_exit - Displays information on the shell built-in command 'exit'.
 */
void help_exit(void)
{
	char *not = "exit: exit [STATUS]\n\tExits the shell.\n\n\tThe ";

	write(STDOUT_FILENO, not, _strlen(not));
	not = "STATUS is the integer used to exit the shell.";
	write(STDOUT_FILENO, not, _strlen(not));
	not = " If no argument is given, the command is interpreted as an";
	write(STDOUT_FILENO, not, _strlen(not));
	not = " exit 0.\n";
	write(STDOUT_FILENO, not, _strlen(not));
}

/**
 * help_help - Displays information on the shell built-in command 'help'.
 */
void help_help(void)
{
	char *not = "help: help\n\tSee all possible Shelter incorpd cmdwords.\n";

	write(STDOUT_FILENO, not, _strlen(not));
	not = "\n      help [INCORPD IDFY]\n\tSee specific information on each ";
	write(STDOUT_FILENO, not, _strlen(not));
	not = "incorpd cmdword.\n";
	write(STDOUT_FILENO, not, _strlen(not));
}
