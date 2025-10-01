#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>


#ifndef BUFFER_SIZE
# define BUFFER_SIZE 4
#endif

char *get_next_line(int fd)
{
	static char buff[BUFFER_SIZE];
	static int i = 0;
	static int bytes = 0;
	char *line;
	int len;
	char *tmp;
	int j;

	len = 0;
	line = malloc(1);
	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
	{
		free(line);
		return(NULL);
	}
	while (1)
	{
		if (i >= bytes)
		{
			bytes = read(fd, buff, BUFFER_SIZE);
			if (bytes <= 0)
			{
				if (len > 0)
					return (line);
				free(line);
				return (NULL);
			}
			i = 0;
		}
		tmp = malloc(len + 2);
		if (!tmp)
		{
			free(line);
			return (NULL);
		}
		j = 0;
		while (j < len)
		{
			tmp[j] = line[j];
			j++;
		}
		tmp[j] = buff[i];
		len++;
		tmp[len] = '\0';
		i++;
		free(line);
		line = tmp;
		if (line[j] == '\n')
			return (line);
	}
}

int main(int argc, char **argv)
{
	int fd;
	char *line;
	
	if (argc != 2)
	{
		printf("Usage: %s <filename>\n", argv[0]);
		return (1);
	}
	
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	
	close(fd);
	return (0);
}

