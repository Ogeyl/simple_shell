#include "shell.h"

/**
 * interactive - returns true if shell is interactive mode
 * @info: struct address
 *
 * Return: if interactive returns (1), otherwise (0)
 */
int interactive(info_t *info)
{
	if (isatty(STDIN_FILENO) && info != NULL)
	{
		/* Check if the shell was not started with a file redirection */
		struct stat st;

		if (fstat(STDIN_FILENO, &st) == -1 || !S_ISCHR(st.st_mode))
		{
			return (0);
		}

		/* Check if the read and write file descriptors are valid */
		if (info->readfd >= 0 && info->writefd >= 0)
		{
			struct stat st_r, st_w;

			if (fstat(info->readfd, &st_r) != -1 && S_ISCHR(st_r.st_mode)
				&& fstat(info->writefd, &st_w) != -1 && S_ISCHR(st_w.st_mode))
			{
				return (1);
			}
		}
	}
	return (0);
}

/**
 * is_delim - checks if character is a delimiter
 * @c: the char to check
 * @delim: the delimiter string
 *
 * Return: if true return (1), if false (0)
 */
int is_delim(char c, char *delim)
{
	while (*delim)
	{
		/*Iterate through the delimiter string */
		if (*delim == c)
		{
			/* Check if current character is a delimiter */
			return (1);
			}
			delim++; /* Move to the next character in the delimiter string */
			}
			return (0);

			/* If the character is not a delimiter, return false */
}



/**
 * _isalpha - checks if a character is alphabetic
 * @c: input character
 * Return: if c is alphabetic, return 1, otherwise return 0
 */
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/**
 * _atoi - converts a string to an integer
 * @h: the string to be converted
 * Return: if no numbers in string (0), otherwise converted number
 */
int _atoi(char *h)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; h[i] != '\0' && flag != 2; i++)
	{
		if (h[i] == '-')
			sign *= -1;

		if (h[i] >= '0' && h[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (h[i] - '0');
			}
			else if (flag == 1)
			{
				flag = 2;
			}
		}

		if (sign == -1)
		{
			output = -result;
			}
		else
		{
			output = result;
			}

		return (output);
}
