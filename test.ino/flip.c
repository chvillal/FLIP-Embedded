#include "flip.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

meta_header metaHdr;
flipPacket flipPkt;
flipHeader flipHdr;

char* FLIP_construct_packet(char *bitmap, char *packet)
{
	char *send_string = malloc(500);
	
	char *version = malloc(sizeof(uint8_t) + 1);
	char *destination = malloc(sizeof(uint32_t) + 1);
	char *length = malloc(sizeof(uint16_t) + 1);
	char *ttl = malloc(sizeof(uint8_t) + 1);
	char *flow = malloc(sizeof(uint32_t) + 1);
	char *source = malloc(sizeof(uint32_t) + 1);
	char *protocol = malloc(sizeof(uint8_t) + 1);
	char *checksum = malloc(sizeof(uint16_t) + 1);
	
	version = itoa(flipHdr.version, 10);
	destination = itoa(flipHdr.destination_addr, 10);
	length = itoa(flipHdr.length, 10);
	ttl = itoa(flipHdr.ttl, 10);
	flow = itoa(flipHdr.flow, 10);
	source = itoa(flipHdr.source_addr, 10);
	protocol = itoa(flipHdr.protocol, 10);
	checksum = itoa(flipHdr.checksum, 10);
	
	strcpy(send_string, bitmap);
	strcat(send_string, version);
	strcat(send_string, destination);
	strcat(send_string, length);
	strcat(send_string, ttl);
	strcat(send_string, flow);
	strcat(send_string, source);
	strcat(send_string, protocol);
	strcat(send_string, checksum);
	strcat(send_string, packet);

	printf("String to send is: %s\n", send_string);
}

int setsockopt(int optname, uint32_t optval, int optlen)
{
	int ret;
	
	switch(optname) {

		case FLIPO_ESP:
			printf("Not implemented yet\n");
			break; 
		
		case FLIPO_VERSION:
			ret = add_version (optval);
			break; 
		
		case FLIPO_DESTINATION:
			ret = add_destination (optval, optlen);
			break;
		
		case FLIPO_LENGTH:
			ret = add_length (optval);
			break;
		
		case FLIPO_TTL:
			ret = add_ttl (optval);
			break; 
		
		case FLIPO_FLOW:
			ret = add_flow (optval);
			break; 
		
		case FLIPO_SOURCE:
			ret = add_source (optval, optlen);
			break;
		
		case FLIPO_PROTOCOL:
			ret = add_protocol (optval);
			break; 
		
		case FLIPO_CHECKSUM:
			ret = add_checksum (optval);
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
			printf("%s\n\n", bitmap[i]);
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

int add_destination(uint32_t optval, int optlen)
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
		printf("Not a valid destination address length\n");
		return -1;
	}
		
	flipHdr.destination_addr = optval;
	printf("Destination address is: %u\n", flipHdr.destination_addr);
	
	return 0;
}

int add_length (uint32_t optval)
{
	flipHdr.length = (uint16_t) optval;
	printf("Lenght is %u\n", flipHdr.length);
	
	return 0;
}

int add_ttl (uint32_t optval)
{
	flipHdr.ttl =  (uint8_t) optval;
	printf("Time to live is %u\n", flipHdr.ttl);
	
	return 0;
}

int add_protocol (uint32_t optval)
{
	flipHdr.protocol = (uint8_t) optval;
	printf("Protocol is %u\n", flipHdr.protocol);
	
	return 0;
}

int add_checksum (uint32_t optval)
{
	flipHdr.checksum = (uint16_t) optval;
	printf("Checksum is %u\n", flipHdr.checksum);
	
	return 0;
}

int add_version (uint32_t optval)
{
	flipHdr.version = (uint8_t) optval;
	printf("Version is %u\n", flipHdr.version);
	
	return 0;
}

int add_flow (uint32_t optval)
{
	flipHdr.flow = optval;
	printf("Flow is %u\n", flipHdr.flow);
	
	return 0;
}

int add_source(uint32_t optval, int optlen)
{
	if (optlen == 16){
		printf("Source field should be two bytes, it is %d bits", optlen);
		metaHdr.source1 = 0;
		metaHdr.source2 = 1;
	}else if (optlen == 32){
		printf("Source field should be four bytes, it is %d bits", optlen);
		metaHdr.source1 = 1;
		metaHdr.source2 = 0;
	}else if (optlen == 64){
		printf("Source field should be sixteen bytes, it is %d bits", optlen);
		metaHdr.source1 = 1;
		metaHdr.source2 = 1;
	}else{
		printf("Not a valid source address length\n");
		return -1;
	}
		
	flipHdr.source_addr = optval;
	printf("Source address is: %u\n", flipHdr.source_addr);
	
	return 0;
}

uint32_t test_function(uint32_t num)
{
	char str[10];
	
	unsigned char byte1 = *((unsigned char *)&num + 3);
	unsigned char byte2 = *((unsigned char *)&num + 2);
	unsigned char byte3 = *((unsigned char *)&num + 1);
	unsigned char byte4 = *((unsigned char *)&num);

	
	sprintf(str, "%c%c%c%c", byte1, byte2, byte3, byte4);
	
	uint32_t b1 = str[0] <<  24 | str[1] << 16 | str[2] << 8 | str[3];
	
	return b1;
}