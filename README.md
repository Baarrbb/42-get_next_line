<h1 align="center">
42-get_next_line 125/100
</h1>
<div align="center">
  <img src="./badge/get_next_linem.png" alt="badge-gnl">
</div>

##
## Purpose

Introduction to a new concept : `static` variables.

The function has to return a `char *` containing a line from the file descriptor given. A loop on the function let us read the file pointed by the file descriptor.

Functions authorized : `malloc`, `read`and `free`.

## `main.c`

	#include <stdio.h>
	#include <fcntl.h>
	#include "get_next_line.h"

	int main(int ac, char **av)
	{
		if (ac != 2)
		{
			printf("Usage:\n./a.out <filename>\n");
			return (1);
		}
		int fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			fprintf(stderr, "Problem opening file\n");
			return (1);
		}
		char *line;
		while((line = get_next_line(fd)))
		{
			printf("%s", line);
			free(line);
		}
		close(fd);
		return (0);
	}

## Usage

```sh
cc -Wall -Wextra -Werror main.c get_next_line_utils.c get_next_line.c
```

```sh
./a.out main.c
```
