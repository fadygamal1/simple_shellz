/*
 * File: alias_builtin.c
 * Auth: Maira Wangui 
 *       
 */

#include "shell.h"

int shelter_alias(char **args, char __attribute__((__unused__)) **leadr);
void set_alias(char *obj_idfy, char *worth);
void print_alias(alias_t *alias);

/**
 * shelter_alias - Built-in command that handles alias management 
 * printing all aliases.
 * @args: Represents an array of arguments.
 * @leadr: Is a double pointer to the beginning of the arguments array. 
 *
 * Return: Returns - -1 on error.
 *         '0' on success.
 */
int shelter_alias(char **args, char __attribute__((__unused__)) **leadr)
{
	alias_t *tmpr = aliases;
	int i, rtn = 0;
	char *worth;

	if (!args[0])
	{
		while (tmpr)
		{
			print_alias(tmpr);
			tmpr = tmpr->nxtp;
		}
		return (rtn);
	}
	for (i = 0; args[i]; i++)
	{
		tmpr = aliases;
		worth = _strchr(args[i], '=');
		if (!worth)
		{
			while (tmpr)
			{
				if (_strcmp(args[i], tmpr->idfy) == 0)
				{
					print_alias(tmpr);
					break;
				}
				tmpr = tmpr->nxtp;
			}
			if (!tmpr)
				rtn = create_mistk(args + i, 1);
		}
		else
			set_alias(args[i], worth);
	}
	return (rtn);
}

/**
 * set_alias - Either updates an existing alias with 'idfy' and 'worth' ,
 * or creates a new alias with these values.
 * @obj_idfy: Represents  the name of the alias.
 * @worth: The value of the alias with the first character as a '='.
 */
void set_alias(char *obj_idfy, char *worth)
{
	alias_t *tmpr = aliases;
	int len, j, k;
	char *new_worth;

	*worth = '\0';
	worth++;
	len = _strlen(worth) - _strspn(worth, "'\"");
	new_worth = malloc(sizeof(char) * (len + 1));
	if (!new_worth)
		return;
	for (j = 0, k = 0; worth[j]; j++)
	{
		if (worth[j] != '\'' && worth[j] != '"')
			new_worth[k++] = worth[j];
	}
	new_worth[k] = '\0';
	while (tmpr)
	{
		if (_strcmp(obj_idfy, tmpr->worth) == 0)
		{
			free(tmpr->worth);
			tmpr->worth = new_worth;
			break;
		}
		tmpr = tmpr->nxtp;
	}
	if (!tmpr)
		add_alias_end(&aliases, obj_idfy, new_worth);
}

/**
 * print_alias - Prints the alias in the format: name='value'.
 * @alias: 'alias' is a pointer to an alias.
 */
void print_alias(alias_t *alias)
{
	char *alias_strobj;
	int len = _strlen(alias->idfy) + _strlen(alias->worth) + 4;

	alias_strobj = malloc(sizeof(char) * (len + 1));
	if (!alias_strobj)
		return;
	_strcpy(alias_strobj, alias->idfy);
	_strcat(alias_strobj, "='");
	_strcat(alias_strobj, alias->worth);
	_strcat(alias_strobj, "'\n");

	write(STDOUT_FILENO, alias_strobj, len);
	free(alias_strobj);
}
/**
 * substit_aliases - Iterates through the arguments replacing matching alias
 * with their value.
 * @args: Is a 2D pointer representing the arguments.
 *
 * Return: A 2D pointer to the arguments.
 */
char **substit_aliases(char **args)
{
	alias_t *tmpr;
	int i;
	char *new_worth;

	if (_strcmp(args[0], "alias") == 0)
		return (args);
	for (i = 0; args[i]; i++)
	{
		tmpr = aliases;
		while (tmpr)
		{
			if (_strcmp(args[i], tmpr->idfy) == 0)
			{
				new_worth = malloc(sizeof(char) * (_strlen(tmpr->worth) + 1));
				if (!new_worth)
				{
					free_args(args, args);
					return (NULL);
				}
				_strcpy(new_worth, tmpr->worth);
				free(args[i]);
				args[i] = new_worth;
				i--;
				break;
			}
			tmpr = tmpr->nxtp;
		}
	}

	return (args);
}
