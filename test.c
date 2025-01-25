
#include "pipex.h"


int main()
{
	char *l = "hid\n";
	char *d = "hid";

	printf("%d \n", ft_strncmp(l, d, ft_strlen(d)));
}

