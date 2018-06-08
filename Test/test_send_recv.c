#include "flip.h"
#include <stdio.h>
#include <stdlib.h>

meta_header metaHdr;
flip_header flipHdr;

int main(int argc, char *argv[])
{	
	metaHdr.continuation1 = false;
	metaHdr.version = true;
	metaHdr.destination1 = true;
	metaHdr.flow = true;
	
	flipHdr.version = 10;
	flipHdr.destination_addr = 1234;
	flipHdr.flow = 38;

	char *bitmap = FLIP_construct_bitmap();
	char *header = FLIP_construct_header();
	char *packet = FLIP_construct_packet();
	
	int i = 0, j, k;
	int t = read_bitmap(bitmap, &i, &j, &k); 
	
	char read_string[20];
	
	flip_parse_packet();
	//get_bitmap_str(bitmap, read_string, 20);
	//printf("bitmap is: %s\n", read_string);
	
	
	char *header = FLIP_construct_header();
	
	int s = read_header_values(header, &i, );
}