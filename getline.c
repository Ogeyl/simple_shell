#include "shell.h"

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t y;
	char *new_buf;
	size_t len_p = 0;

	/* fill the buffer */
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		y = getline(buf, &len_p, stdin);
#else
		y = _getline(info, buf, &len_p);
#endif
		if (y > 0)
		{
			if ((*buf)[y - 1] == '\n')
			{
				(*buf)[y - 1] = '\0'; /* remove trailing newline */
				y--;
			}

			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = y;
				info->cmd_buf = buf;
			}
		}
		else
		{
			free(*buf);
			*buf = NULL;
	return (y);
		}
}

/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t y = 0;
	char **buf_p = &(info->arg);

	_putchar(BUF_FLUSH);
	y = input_buf(info, &buf, &len);
	if (y == -1) /* EOF */
	{
		return (-1);
	}
	if (len) /* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */

		check_chain(info, buf, &j, i, len);

		while (j < len) /* iterate to semicolon or end */
		{
			char *p = buf + j; /* get pointer for return */

			if (is_chain(info, buf, &j))
			{
				break;
			}
			j++;

			i = j + 1; /* increment past nulled ';' */
		}

		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = buf + (i - j); /* pass back pointer to current command position */
		return (_strlen(*buf_p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (y); /* return length of buffer from _getline() */
}



/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: y
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t y = 0;

	if (*i)
		return (0);
	y = read(info->readfd, buf, READ_BUF_SIZE);
	if (y >= 0)
		*i = y;
	return (y);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: length of line read, or -1 on failure or EOF
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t y = 0;
	char *p = NULL, *new_p = NULL, *ch;

	p = *ptr;
	if (p && length)
		len = *length;
	if (i == len)
		i = len = 0;

	y = read_buf(info, buf, &len);
	if (y == -1 || (y == 0 && len == 0))
		return (-1);

	ch = _strchr(buf + i, '\n');
	k = ch ? 1 + (size_t)(ch - buf) : len;

	new_p = _realloc(p, *length, k + 1);
	if (!new_p)
	{ /* MALLOC FAILURE! */
		free(p);
		return (-1);
	}

	if (*length == 0)
		new_p[0] = '\0';

	_strncat(new_p, buf + i, k - i);
	new_p[k - i] = '\0';

	i = ch ? k + 1 : len;
	*length = k + 1;
	*ptr = new_p;

	return (1);
}
