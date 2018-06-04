#include "flip.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* int flip_construct_header(flipHdr *flipPacket, uint16_t packet_len)
{
	
	flipPacket->flipHdr.version = 0;
	flipPacket->flipHdr.lenght = htons(packet_len);
	flipPacket->flipHdr.ttl;
	
	
} */

int setsockopt(int optname, int optval, int optlen)
{
	int ret;
	
	switch(optname) {

		case FLIPO_ESP:
			printf("Not implemented yet\n");
			break; 
		
		case FLIPO_VERSION:
			printf("Not implemented yet\n");
			break; 
		
		case FLIPO_DESTINATION:
			ret = add_destination (optval, optlen);
			break;
		
		case FLIPO_LENGTH:
			ret = add_length (optlen);
			break;
		
		case FLIPO_TTL:
			ret = add_ttl (optval, optlen);
			break; 
		
		case FLIPO_SOURCE:
			ret = add_source (optval, optlen);
			break;
		
		case FLIPO_PROTOCOL:
			ret = add_protocol (optval, optlen);
			break; 
		
		case FLIPO_CHECKSUM:
			printf("Not implemented yet\n");
			break; 
			
	  
		default:
			printf("Not a valid option\n");
			return -1;
	}
	return ret;
}

char* FLIP_construct_bitmap (void)
{
	if (metaHdr.continuation1) {
		// bitmap array of size 16
		char *bitmap = (char *)malloc(16 + 1);
		
		printf("Initialized charater array:\n");
		for (int i = 0; i < 16; i++){
			bitmap[i] = '0';
			printf("%s, ", bitmap[i]);
		}
		
		bitmap[0] = '1'; 
		
		if (metaHdr.esp) {
			bitmap[1] = '1';
		}
		if (metaHdr.version) {
			bitmap[2] = '1';
		}
		if (metaHdr.destination1) {
			bitmap[3] = '1';
		}
		if (metaHdr.destination2) {
			bitmap[4] = '1';
		}
		if (metaHdr.length) {
			bitmap[5] = '1';
		}
		if (metaHdr.ttl) {
			bitmap[6] = '1';
		}
		if (metaHdr.flow) {
			bitmap[7] = '1';
		}
		if (metaHdr.continuation2){
			bitmap[8] = '1';
		}
		if (metaHdr.source1) {
			bitmap[9] = '1';
		}
		if (metaHdr.source2) {
			bitmap[10] = '1';
		}
		if (metaHdr.protocol) {
			bitmap[11] = '1';
		}
		if (metaHdr.checksum) {
			bitmap[12] = '1';
		}
		
		return bitmap;
		
	}else{
		char *bitmap = (char *)malloc(8 + 1);
		
		if (metaHdr.esp) {
			bitmap[1] = '1';
		}
		if (metaHdr.version) {
			bitmap[2] = '1';
		}
		if (metaHdr.destination1) {
			bitmap[3] = '1';
		}
		if (metaHdr.destination2) {
			bitmap[4] = '1';
		}
		if (metaHdr.length) {
			bitmap[5] = '1';
		}
		if (metaHdr.ttl) {
			bitmap[6] = '1';
		}
		if (metaHdr.flow) {
			bitmap[7] = '1';
		}
		
		return bitmap;
	}
	
}

int add_destination(int optval, int optlen)
{
	if (optlen == 16){
		printf("Destination field should be two bytes, it is %d bits", optlen);
		metaHdr.destination1 = 0;
		metaHdr.destination2 = 1;
	}else if (optlen == 32){
		printf("Destination field should be four bytes, it is %d bits", optlen);
		metaHdr.destination1 = 1;
		metaHdr.destination2 = 0;
	}else if (optlen == 64){
		printf("Destination field should be sixteen bytes, it is %d bits", optlen);
		metaHdr.destination1 = 1;
		metaHdr.destination2 = 1;
	}else{
		printf("Not a valid destination address lenght\n");
		return -1;
	}
	
	char string[optlen + 1];
	itoa(optval, string, 10);
	
	flipHdr.destination_addr = optval;
	printf("Destination address is %s\n", flipHdr.destination_addr);
	
	return 0;
}

int add_length (optlen)
{
	if (optlen == 0 || optlen > 16){
		printf("Invalid length\n");
		return -1;
	}
	
	flipHdr.length = (uint16_t) optlen;
	printf("Lenght is %d\n", flipHdr.length);
	return 0;
}

int add_ttl (optval, optlen)
{
	if (optlen == 0 || optlen > 16){
		printf("Invalid length\n");
		return -1;
	}
	
	flipHdr.ttl =  (uint8_t) optval;
	printf("Time to live is %d\n", flipHdr.ttl);
	return 0;
}