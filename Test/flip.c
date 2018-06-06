#include "flip.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

meta_header metaHdr;
flipPacket flipPkt;
flipHeader flipHdr;


char* FLIP_construct_bitmap (void)
{
	/* We want to send a one byte bitmap */
	if (metaHdr.continuation1 == 0){
		
		// The first continuationo bit is off, initialize a bitmap of one byte
		uint8_t bitmap = 0;
		//printf("Bitmap is: %u\n", bitmap);
		
		// Construct the bitmap based on the meta header fields
		if (metaHdr.esp){
			bitmap = bitmap | 1 << 6;
			//printf("Bitmap is: %u\n", bitmap);
		}
		if (metaHdr.version){
			bitmap = bitmap | 1 << 5;
			//printf("Bitmap is: %u\n", bitmap);
		}
		if (metaHdr.destination1){
			bitmap = bitmap | 1 << 4;
			//printf("Bitmap is: %u\n", bitmap);
		}
		if (metaHdr.destination2){
			bitmap = bitmap | 1 << 3;
			//printf("Bitmap is: %u\n", bitmap);
		}
		if (metaHdr.length){
			bitmap = bitmap | 1 << 2;
			//printf("Bitmap is: %u\n", bitmap);
		}
		if (metaHdr.ttl){
			bitmap = bitmap | 1 << 1;
			//printf("Bitmap is: %u\n", bitmap);
		}
		if (metaHdr.flow){
			bitmap = bitmap | 1;
			//printf("Bitmap is: %u\n", bitmap);
		}
		
		printf("Bitmap is: %u\n", bitmap);
		
		char *bitmap_string = (char*) malloc(sizeof(char) * (8+1));
		
		unsigned char byte1 = *((unsigned char *)&bitmap);

		sprintf(bitmap_string, "%c", byte1);
		printf("Unsigned: %u\n", byte1);
		printf("Bytes: %c\n", byte1);
	
		printf("The string is: %s\n", bitmap_string);
		
		uint8_t b1 = bitmap_string[0];
		printf("Unsigned int: %u\n", b1);
		
		return bitmap_string;
		
	/* We want to send a two byte bitmap */	
	}else if (metaHdr.continuation1){
		// The first continuationo bit is on, initialize a bitmap of two bytes
		uint16_t bitmap = 32768;
		//printf("Bitmap is: %u\n", bitmap);
		
		// Construct the bitmap based on the meta header fields
		if (metaHdr.esp){
			bitmap = bitmap | 1 << 14;
			//printf("Bitmap is: %u\n", bitmap);
		}
		if (metaHdr.version){
			bitmap = bitmap | 1 << 13;
			//printf("Bitmap is: %u\n", bitmap);
		}
		if (metaHdr.destination1){
			bitmap = bitmap | 1 << 12;
			//printf("Bitmap is: %u\n", bitmap);
		}
		if (metaHdr.destination2){
			bitmap = bitmap | 1 << 11;
			//printf("Bitmap is: %u\n", bitmap);
		}
		if (metaHdr.length){
			bitmap = bitmap | 1 << 10;
			//printf("Bitmap is: %u\n", bitmap);
		}
		if (metaHdr.ttl){
			bitmap = bitmap | 1 << 9;
			//printf("Bitmap is: %u\n", bitmap);
		}
		if (metaHdr.flow){
			bitmap = bitmap | 1 << 8;
			//printf("Bitmap is: %u\n", bitmap);
		}
		if (metaHdr.continuation2){
			bitmap = bitmap | 1 << 7;
			//printf("Bitmap is: %u\n", bitmap);
		}
		if (metaHdr.source1){
			bitmap = bitmap | 1 << 6;
			//printf("Bitmap is: %u\n", bitmap);
		}
		if (metaHdr.source2){
			bitmap = bitmap | 1 << 5;
			//printf("Bitmap is: %u\n", bitmap);
		}
		if (metaHdr.protocol){
			bitmap = bitmap | 1 << 4;
			//printf("Bitmap is: %u\n", bitmap);
		}
		if (metaHdr.checksum){
			bitmap = bitmap | 1 << 3;
			//printf("Bitmap is: %u\n", bitmap);
		}
		
		printf("Bitmap is: %u\n", bitmap);
		
		char *bitmap_string = (char*) malloc(sizeof(char) * (16+1));
		
		unsigned char byte1 = *((unsigned char *)&bitmap + 1);
		unsigned char byte2 = *((unsigned char *)&bitmap);

		sprintf(bitmap_string, "%c%c", byte1, byte2);
		printf("Unsigned: %u %u\n", byte1, byte2);
		printf("Bytes: %c %c\n", byte1, byte2);
	
		printf("The string is: %s\n", bitmap_string);
		
		uint8_t b1 = bitmap_string[0] << 8 | bitmap_string[1];
		printf("Unsigned int: %u\n", b1);
		
		return bitmap_string;
	}
}

char* FLIP_construct_header (void)
{
	
	
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