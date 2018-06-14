#include "flip.h"
#include <stdio.h>
#include <stdlib.h>

meta_header metaHdr;
flip_header flipHdr;

int main(int argc, char *argv[])
{	
	int ret;
	
	ret = setsockopt(FLIPO_VERSION, 3, 0);
	ret = setsockopt(FLIPO_LENGTH, 55, 0);
	ret = setsockopt(FLIPO_DESTINATION, 32, 2);
	ret = setsockopt(FLIPO_TTL, 2, 0);
	ret = setsockopt(FLIPO_FLOW, 1, 0);
	ret = setsockopt(FLIPO_SOURCE, 321, 4);
	ret = setsockopt(FLIPO_CHECKSUM, 1, 0);
	ret = setsockopt(FLIPO_PROTOCOL, 4, 0);


/* 	metaHdr.continuation1 = true;
	metaHdr.version = true;
	metaHdr.destination1 = true;
	metaHdr.flow = true;
	metaHdr.ttl = true;
	metaHdr.length = true;
	metaHdr.protocol = true;
	metaHdr.source1 = true;
	
	flipHdr.version = 8;
	flipHdr.ttl = 6;
	flipHdr.length = 5;
	flipHdr.protocol = 3;
	flipHdr.destination_addr = 29;
	flipHdr.flow = 38;
	flipHdr.source_addr = 43; */

	char *payload = "HELLO";
	
	char *bitmap = FLIP_construct_bitmap();
	char *header = FLIP_construct_header();
	char *packet = FLIP_construct_packet(bitmap, header, payload);
	
	int i = 0, j, k;
	int t = read_bitmap(bitmap, &i, &j, &k); 
	
	char read_string[20];
	
	printf("constructed packet is: %s\n", packet);
	for (int i = 0; i < 24; i ++) {
		printf(" %02x", packet[i]);
	}
	printf("\n");
	

	int var;
	flip_read_packet(packet, 10, &var);
	printf("\n\nFLIP_read_packet payload: %s\n\n", packet+var);

	
	read_rcv_values();
	
	
	get_bitmap_str(bitmap, read_string, 20);
	printf("bitmap is: %s\n", read_string);
	
	read_rcv_flags();
	
	
	int packet_len = get_packet_length();
	printf("Length of the packet is: %d\n", packet_len);
	
	char printH[256];
	get_headervals_str(printH, 256);
	printf("PRINTING HEADER VALS FROM STRUCT\n%s", printH);
}