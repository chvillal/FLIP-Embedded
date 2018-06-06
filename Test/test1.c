#include "flip.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{	
	char *bitmap_string = flip_construct_bitmap();
	printf("Bitmap is: %s\n", bitmap_string);
}