#include "flip.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *packet = "THIS IS A PACKET WOOOOO";
char *bitmap = "10001234";

char* itoa(int val, int base){
	
	static char buf[32] = {0};
	
	int i = 30;
	
	for(; val && i ; --i, val /= base)
	
		buf[i] = "0123456789abcdef"[val % base];
	
	return &buf[i+1];	
}

int main(int argc, char* argv[])
{
	flipHdr.version = 9;
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
	
	printf("Version is: %s\n", version);
	printf("String to send is: %s\n", send_string);
}