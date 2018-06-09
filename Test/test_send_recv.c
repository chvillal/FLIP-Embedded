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
	metaHdr.ttl = true;
	metaHdr.length = true;
	metaHdr.protocol = true;
	
	flipHdr.version = 8;
	flipHdr.ttl = 6;
	flipHdr.length = 12;
	flipHdr.protocol = 3;
	flipHdr.destination_addr = 2949567296;
	flipHdr.flow = 38;

	char *payload = "HELLO";
	
	char *bitmap = FLIP_construct_bitmap();
	char *header = FLIP_construct_header();
	char *packet = FLIP_construct_packet(bitmap, header, payload);
	
	int i = 0, j, k;
	int t = read_bitmap(bitmap, &i, &j, &k); 
	
	char read_string[20];
	
	printf("constructed packet is: %s\n", packet);
	for (int i = 0; i < 20; i ++) {
		printf(" %02x", packet[i]);
	}
	printf("\n");
	

	
	flip_parse_packet(packet, 10, payload);

	
	read_rcv_values();
	
	
	
	
	get_bitmap_str(bitmap, read_string, 20);
	printf("bitmap is: %s\n", read_string);

}