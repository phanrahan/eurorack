#include <stdio.h>
 
void euclidean(int dx, int dy)
{
	int p=2*dy-dx;
 
	for( int x = 0; x < dx; x++ )
	{
		if(p>=0)
		{
			putchar('1');
			p=p+2*dy-2*dx;
		}
		else
		{
			putchar('0');
			p=p+2*dy;
		}
	}
}
 
int main()
{
    euclidean(16,5);
    putchar('\n');
}
