#include <stdio.h>

void func(int &i) 
{
	i = 256;
}

int main (int argc, char **argv)
{
	int i = 128;
	func(i);
	printf("%d", i);
	return 0;
}
