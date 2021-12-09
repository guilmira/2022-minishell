
#include <stdio.h>

#include <string.h>

int main(void)
{

	char	*line;
	size_t	bufsize;

	FILE *fp;

	fp = fopen("whatever", "r");
	if (!fp)
	{
		printf("%i\n", errno);
		printf("%s\n", strerror(errno));
		perror("error");
		
	}
	line = NULL;
	bufsize = 0;
	/* if (getline(&line, &bufsize, fp) == -1)
	{
		printf("%i\n", errno);
		return(0);
	} */
printf("%i\n", errno);
	printf("%s\n", line);


	return (0);
}