#include "flip.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *packet = "THIS IS A PACKET WOOOOO";
char *bitmap = "10001100";


int main(int argc, char* argv[])
{
/* 	flipHdr.version = 9;
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
	printf("String to send is: %s\n", send_string); */
	
/* 	uint32_t x = 65;
	uint32_t y = 66;
	uint32_t z = 67;
	
	char str[10];
	char a = x;
	char b = y;
	char c = z;
	
	sprintf(str, "%c%c%c", a, b, c);
	printf("The string is: %s\n", str);
	
	uint8_t m = str[0];
	uint32_t n = str[1];
	uint32_t e = str[2];
	
	printf("Uints: %u %u %u\n", m,n,e); */
	
/* 	char e[3];
	e[0] = 64;
	e[1] = 66;
	e[2] = 0;
	
	printf("The string is: %s\n", e);
	
	uint16_t test = e[0] << 8 | e[1];
	
	printf("Uint: %u\n", test); */
	
	uint32_t x = 1094861636;
	char str[10];
	
	unsigned char byte1 = *((unsigned char *)&x + 3);
	unsigned char byte2 = *((unsigned char *)&x + 2);
	unsigned char byte3 = *((unsigned char *)&x + 1);
	unsigned char byte4 = *((unsigned char *)&x);

	
	sprintf(str, "%c%c%c%c", byte1, byte2, byte3, byte4);
	printf("Unsigned: %u %u %u %u\n", byte1, byte2, byte3, byte4);
	printf("Bytes: %c %c %c %c\n", byte1, byte2, byte3, byte4);
	
	printf("The string is: %s\n", str);
	
	uint32_t b1 = str[0] <<  24 | str[1] << 16 | str[2] << 8 | str[3];
	printf("Unsigned int: %u\n", b1);
	
}