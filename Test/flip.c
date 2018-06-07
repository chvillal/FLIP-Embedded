#include "flip.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

meta_header metaHdr;
flip_header flipHdr;


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
		
		char *bitmap_string = (char *) malloc(sizeof(char) * (8+1));
		
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
		
		char *bitmap_string = (char *) malloc(sizeof(char) * (16+1));
		
		unsigned char byte1 = *((unsigned char *)&bitmap + 1);
		unsigned char byte2 = *((unsigned char *)&bitmap);

		sprintf(bitmap_string, "%c%c", byte1, byte2);
		printf("Unsigned: %u %u\n", byte1, byte2);
		printf("Bytes: %c %c\n", byte1, byte2);
	
		printf("The string is: {%s}\n", bitmap_string);
		
		uint16_t b1 = (uint8_t)bitmap_string[0] << 8 | (uint8_t)bitmap_string[1];
		printf("Unsigned int: %u\n", b1);
		
		return bitmap_string;
	}
}

char* FLIP_construct_header (void)
{
	char *header_string = (char *) malloc(sizeof(char) * 249);
	
	if (metaHdr.version){
		char version_string[10];
		
		unsigned char byte1 = *((unsigned char *)&flipHdr.version);

		sprintf(version_string, "%c", byte1);
		printf("Unsigned: %u\n", byte1);
		printf("Bytes: %c\n", byte1);
	
		printf("The version string is: %s\n", version_string);
		
		uint8_t b1 = (uint8_t)version_string[0];
		printf("Unsigned int: %u\n\n", b1);
		
		
		
		strcat(header_string, version_string);
	}
	
	if (metaHdr.destination1){
		char destination_string[100];
		
		unsigned char byte1 = *((unsigned char *)&flipHdr.destination_addr + 3);
		unsigned char byte2 = *((unsigned char *)&flipHdr.destination_addr + 2);
		unsigned char byte3 = *((unsigned char *)&flipHdr.destination_addr + 1);
		unsigned char byte4 = *((unsigned char *)&flipHdr.destination_addr);

		sprintf(destination_string, "%c%c%c%c", byte1, byte2, byte3, byte4);
		printf("Unsigned: %u %u %u %u\n", byte1, byte2, byte3, byte4);
		printf("Bytes: %c %c %c %c\n", byte1, byte2, byte3, byte4);
	
		printf("The destination string is: %s\n", destination_string);
		
		uint32_t b1 = (uint8_t)destination_string[0] <<  24 | (uint8_t)destination_string[1] << 16 | (uint8_t)destination_string[2] << 8 | (uint8_t)destination_string[3];
		printf("Unsigned int: %u\n\n", b1);
		
		strcat(header_string, destination_string);
	}
	
	if (metaHdr.destination2){
		
		uint16_t dest_addr = (uint16_t) flipHdr.destination_addr;
		char destination_string[16];
		
		unsigned char byte1 = *((unsigned char *)&dest_addr + 1);
		unsigned char byte2 = *((unsigned char *)&dest_addr);

		sprintf(destination_string, "%c%c", byte1, byte2);
		printf("Unsigned: %u %u\n", byte1, byte2);
		printf("Bytes: %c %c\n", byte1, byte2);
	
		printf("The destination string is: %s\n", destination_string);
		
		uint16_t b1 = (uint8_t)destination_string[0] << 8 | (uint8_t)destination_string[1];
		printf("Unsigned int: %u\n\n", b1);
		
		strcat(header_string, destination_string);
	}
	
	if (metaHdr.length){
		char length_string[18];
		
		unsigned char byte1 = *((unsigned char *)&flipHdr.length + 1);
		unsigned char byte2 = *((unsigned char *)&flipHdr.length);

		sprintf(length_string, "%c%c", byte1, byte2);
		printf("Unsigned: %u %u\n", byte1, byte2);
		printf("Bytes: %c %c\n", byte1, byte2);
	
		printf("The length string is: %s\n\n", length_string);
		
		uint16_t b1 = (uint8_t)length_string[0] << 8 | (uint8_t)length_string[1];
		printf("Unsigned int: %u\n", b1);
		
		strcat(header_string, length_string);
	}
	
	if (metaHdr.ttl){
		char ttl_string[10];
		
		unsigned char byte1 = *((unsigned char *)&flipHdr.ttl);

		sprintf(ttl_string, "%c", byte1);
		printf("Unsigned: %u\n", byte1);
		printf("Bytes: %c\n", byte1);
	
		printf("The ttl string is: %s\n", ttl_string);
		
		uint8_t b1 = (uint8_t)ttl_string[0];
		printf("Unsigned int: %u\n\n", b1);
		
		strcat(header_string, ttl_string);
	}
	
	if (metaHdr.flow){
		char flow_string[33] = {0};
		
		unsigned char byte1 = *((unsigned char *)&flipHdr.flow + 3);
		unsigned char byte2 = *((unsigned char *)&flipHdr.flow + 2);
		unsigned char byte3 = *((unsigned char *)&flipHdr.flow + 1);
		unsigned char byte4 = *((unsigned char *)&flipHdr.flow);

		
		sprintf(flow_string, "%c%c%c%c", byte1, byte2, byte3, byte4);
		printf("Unsigned: %u %u %u %u\n", byte1, byte2, byte3, byte4);
		printf("Bytes: %c %c %c %c\n", byte1, byte2, byte3, byte4);
		
		printf("The flow string is: %s\n", flow_string);
		
		uint32_t b1 = (uint8_t)flow_string[0] <<  24 | (uint8_t)flow_string[1] << 16 | (uint8_t)flow_string[2] << 8 | (uint8_t)flow_string[3];
		printf("Unsigned int: %u\n\n", b1);
		
		strcat(header_string, flow_string);
	}
	
	if (metaHdr.source1){
		char source_string[33];
		
		unsigned char byte1 = *((unsigned char *)&flipHdr.source_addr + 3);
		unsigned char byte2 = *((unsigned char *)&flipHdr.source_addr + 2);
		unsigned char byte3 = *((unsigned char *)&flipHdr.source_addr + 1);
		unsigned char byte4 = *((unsigned char *)&flipHdr.source_addr);

		sprintf(source_string, "%c%c%c%c", byte1, byte2, byte3, byte4);
		printf("Unsigned: %u %u %u %u\n", byte1, byte2, byte3, byte4);
		printf("Bytes: %c %c %c %c\n", byte1, byte2, byte3, byte4);
	
		printf("The source string is: %s\n", source_string);
		
		uint32_t b1 = (uint8_t)source_string[0] <<  24 | (uint8_t)source_string[1] << 16 | (uint8_t)source_string[2] << 8 | (uint8_t)source_string[3];
		printf("Unsigned int: %u\n\n", b1);
		
		strcat(header_string, source_string);
	}
	
	if (metaHdr.source2){
		char source_string[18];
		
		unsigned char byte1 = *((unsigned char *)&flipHdr.source_addr + 1);
		unsigned char byte2 = *((unsigned char *)&flipHdr.source_addr);

		sprintf(source_string, "%c%c", byte1, byte2);
		printf("Unsigned: %u %u\n", byte1, byte2);
		printf("Bytes: %c %c\n", byte1, byte2);
	
		printf("The source string is: %s\n", source_string);
		
		uint16_t b1 = (uint8_t)source_string[0] << 8 | (uint8_t)source_string[1];
		printf("Unsigned int: %u\n\n", b1);
		
		strcat(header_string, source_string);
	}
	
	if (metaHdr.protocol){
		char protocol_string[10];
		
		unsigned char byte1 = *((unsigned char *)&flipHdr.protocol);

		sprintf(protocol_string, "%c", byte1);
		printf("Unsigned: %u\n", byte1);
		printf("Bytes: %c\n", byte1);
	
		printf("The protocol string is: %s\n", protocol_string);
		
		uint8_t b1 = (uint8_t)protocol_string[0];
		printf("Unsigned int: %u\n\n", b1);
		
		strcat(header_string, protocol_string);
	}
	
	if (metaHdr.checksum){
		char checksum_string[18];
		
		unsigned char byte1 = *((unsigned char *)&flipHdr.checksum + 1);
		unsigned char byte2 = *((unsigned char *)&flipHdr.checksum);

		sprintf(checksum_string, "%c%c", byte1, byte2);
		printf("Unsigned: %u %u\n", byte1, byte2);
		printf("Bytes: %c %c\n", byte1, byte2);
	
		printf("The checksum string is: %s\n", checksum_string);
		
		uint16_t b1 = (uint8_t)checksum_string[0] << 8 | (uint8_t)checksum_string[1];
		printf("Unsigned int: %u\n\n", b1);
		
		strcat(header_string, checksum_string);
	}
	printf("Header: %s\n", header_string);
	
	return header_string;
}


int setsockopt(int optname, uint32_t optval, int optlen)
{
	int ret;
	
	switch (optname) {

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