/* name:
 * authors:
 * email:
 *
 * description:
 *
 */

/* INCLUDES */
#include "flip.h"

/* DEFINES */
#define SO_DST_SIZE_2 0x18
#define SO_VER 
#define SO_SRC
#define SO_LEN
#define SO_TTL
#define SO_FLOW
#define SO_PROTOCOL
#define SO_CRC
#define SO_ESP
#define CONT_BIT 0x80


#define MAX_STR_SIZE 128 //temporary, not sure what max lora string len is...

/* GLOBAL VARIABLES */
struct meta_header rcv_bitmap;
struct flipHdr rcv_header_values;


int flip_construct_header(flipHdr *flipPacket, uint16_t packet_len)
{
	
	flipPacket->flipHdr.version = 0;
	flipPacket->flipHdr.lenght = htons(packet_len);
	flipPacket->flipHdr.ttl;
	
	
	
	char version;				/* FLIP header version. */
	uint16_t packet_len;		/* Length of FLIP packet (in bytes). */
	uint8_t ttl;				/* Packet time to live. */
	uint32_t flow;				/* Flow identification. */
	char* source_addr[];		/* FLIP source address. */
	uint32_t destination_addr;  /* FLIP destination address. */
	uint8_t protocol; 			/* Higher layer protocols. */
	uint16_t checksum; 		
	
}

int flip_construct_packet(flipHdr *flipPacket, uint16_t packet_len);



/** GET SOCKET OPTIONS - RECEIVING END **/

//temp name, receives entire message string from radio. then reads header
// fields, saves options, and returns payload string.

int flip_parse_packet(char *buff, int buff_len, char *payload ){
	int i = 0;
	int j = 0;
	int dst_size;
	uint8_t bitmap = buff[i];
	
	//reset bitmap and header values in buffer structs
	reset_bitmap(&rcv_bitmap);
	reset_header(&rcv_header_values);
	
	//start reading bit map
	if (bitmap & SO_ESP){
		rcv_bitmap.esp = true;
		//do something
		payload = buff + i;
		return 1; // no errors.
	}
	
	if (bitmap & SO_VER){
		rcv_bitmap.version = true;
	}
	
	if (bitmap & SO_DST){
		rcv_bitmap.destination = true;
		
		//compute and save size
		dst_size = 2;
	}
	
	if (bitmap & SO_LEN){
		rcv_bitmap.lenght = true;
	}
	
	if (bitmap & SO_TTL){
		rcv_bitmap.ttl = true;
	}
	
	if (bitmap & SO_FLOW){
		rcv_bitmap.flow = true;
	}
	
	if (bitmap & CONT_BIT){
		i++;
		bitmap = buff[i];
		
		if (bitmap & SO_SRC){
			rcv_bitmap.source = true;
			//compute and save size
		}
		
		if (bitmap & SO_PROTOCOL){
			rcv_bitmap.protocol = true;
		}
		
		if (bitmap & SO_CRC){
			rcv_bitmap.checksum = true;
		}
	}
	
	//start reading header values
	i++; //point to next byte, values start
	if ( rcv_bitmap.version){

		//1 byte long
		rcv_header_values.version = buff[i];
		i++;
	}
	
	if ( rcv_bitmap.destination){ // ***** NEEDS LOGIC TO DETERMINE PROPER VALUE SIZE
		
		//2 bytes long

		rcv_header_values.destination_addr = buff[i] << 8 | buff[i+1] ;
		i += 2;
	}
	
	if ( rcv_bitmap.lenght){

		// 2 bytes long
		rcv_header_values.lenght = buff[i] << 8 | buff[i+1];
		i += 2;
	}
	
	if ( rcv_bitmap.ttl){
		
		rcv_header_values.ttl = buff[i];
		i++;
	}
	
	if ( rcv_bitmap.flow){ // ***** NEEDS LOGIC TO DETERMINE PROPER VALUE SIZE
		
		rcv_header_values.flow = buff[i] << 24 | buff[i+1] <<16 | buff[i+2] << 8 | buff[i+3] ;
		i += 4;
	}
	
	if ( rcv_bitmap.source){
		
		rcv_header_values.source_addr = buff[i] << 8 | buff[i+1] ;
		i += 2;
	}
	
	if ( rcv_bitmap.protocol){
		rcv_header_values.protocol = buff[i];
		i++;
	}
	
	if ( rcv_bitmap.checksum){
		
		rcv_header_values.checksum =  buff[i] << 8 | buff[i+1];
		i += 2;
	}
	
	//return payload?
	payload = buff + i;
	
	return 1; // no errors.
}

/*
 * Resets all flags of BITMAP to false.
 */
void reset_bitmap(struct meta_header *bitmap){
	
	bitmap->checksum = false;
	bitmap->destination = false;
	bitmap->esp = false;
	bitmap->flow = false;
	bitmap->lenght = false;
	bitmap->protocol = false;
	bitmap->source = false;
	bitmap->ttl = false;
	bitmap->version = false;
}

/*
 * Resets all values of the header HEADER_VALUES to 0.
 */
void reset_header(struct flipHdr *header_values){
	
	header_values->checksum = 0;
	header_values->destination_addr = 0;
	header_values->flow = 0;
	header_values->lenght = 0;
	header_values->protocol = 0;
	header_values->source_addr = 0;
	header_values->ttl = 0;
	header_values->version = 0;
}


