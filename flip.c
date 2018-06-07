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
#define BITMASK_DST_SIZE_2	0x08
#define BITMASK_DST_SIZE_4	0x10
#define BITMASK_DST_SIZE_16	0x18
#define BITMASK_VER			0x20
#define BITMASK_SRC_SIZE_2	0x20
#define BITMASK_SRC_SIZE_4	0x40
#define BITMASK_SRC_SIZE_16 0x60
#define BITMASK_LEN			0x04
#define BITMASK_TTL			0x02
#define BITMASK_FLOW		0x01
#define BITMASK_PROTOCOL	0x10
#define BITMASK_CRC			0x08
#define BITMASK_ESP			0x40
#define BITMASK_CONT		0x80

#define BITMAP_MAX_LEN		2


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



/** GET SOCKET OPTIONS - RECEIVING END FUNCTIONS **/

/*
 * Receives raw string BUFF from radio. reads FLIP bitmap and then parses 
 * corresponding values. Saves ptr where payload starts in string.
 *
 * returns 0 if parsed successfully, 1 if esp packet,
 * or -1 if error.
 *
 */
int flip_parse_packet(char *buff, int buff_len, char *payload ){
	int i = 0;
	int dst_size = 0;
	int src_size = 0;	
	
	//reset bitmap and header values in buffer struct
	reset_bitmap(&rcv_bitmap);
	reset_header(&rcv_header_values);
	
	//start reading bitmap
	if (read_bitmap(buff, &i, &dst_size, &src_size) > 0)
		return 1; // ESP packet, done parsing.
	
	//start reading header values
	read_header_values(buff, &i, dst_size, src_size);
	
	//store start address of they payload (ptr)
	payload = buff + i;
	
	return 0; // no errors.
}


/*
 * reads very first bytes of a passed string. translates bitmap into
 * corresponding boolean flags. 
 * returns 1 if esp packet, 0 if no errors, -1 on error
 */
int read_bitmap(char *buff, int *i, int *dst_size, int *src_size) {
		
	uint8_t bitmap = (uint8_t) buff[*i];
	
	if (bitmap & BITMASK_ESP){
		rcv_bitmap.esp = true;
		// ESP detected, notify caller
		return 1; 
	}
	
	if (bitmap & BITMASK_VER){
		rcv_bitmap.version = true;
	}
	
	if (bitmap & BITMASK_DST_SIZE_16){
		rcv_bitmap.destination = true;	
			
		if ((bitmap & BITMASK_DST_SIZE_2) == BITMASK_DST_SIZE_2)
			*dst_size = 2;
		if ((bitmap & BITMASK_DST_SIZE_4) == BITMASK_DST_SIZE_4)
			*dst_size = 4;
		if ((bitmap & BITMASK_DST_SIZE_16) == BITMASK_DST_SIZE_16)
			*dst_size = 16;
	}
	
	if (bitmap & BITMASK_LEN){
		rcv_bitmap.lenght = true;
	}
	
	if (bitmap & BITMASK_TTL){
		rcv_bitmap.ttl = true;
	}
	
	if (bitmap & BITMASK_FLOW){
		rcv_bitmap.flow = true;
	}
	
	if (bitmap & BITMASK_CONT){
		*i += *i + 1;
		bitmap = (uint8_t) buff[i];
		
		if (bitmap & BITMASK_SRC_SIZE_16){
			rcv_bitmap.source = true;
			
			if ((bitmap & BITMASK_SRC_SIZE_2) == BITMASK_SRC_SIZE_2)
				*src_size = 2;
			if ((bitmap & BITMASK_SRC_SIZE_4) == BITMASK_SRC_SIZE_4)
				*src_size = 4;
			if ((bitmap & BITMASK_SRC_SIZE_16) == BITMASK_SRC_SIZE_16)
				*src_size = 16;
		}
		
		if (bitmap & BITMASK_PROTOCOL){
			rcv_bitmap.protocol = true;
		}
		
		if (bitmap & BITMASK_CRC){
			rcv_bitmap.checksum = true;
		}
	}
	
	// move index to point to next byte
	*i += *i +1;
	
	return 0;
}


/*
 * reads header values flagged by rcv_bitmap struct in sequential oder,
 * stores values in rcv_header_values struct. 
 *
 * index i should point to the first byte of header values.
 *
 * returns 0 if successful, or -1 if error
 */
int read_header_values(char *buff, int *i, int dst_size, int src_size){
	int j = *i;
	
	if ( rcv_bitmap.version){
		//1 byte long
		rcv_header_values.version = (uint8_t) buff[j];
		j++;
	}
	
	if ( rcv_bitmap.destination){		
		//2-16 bytes long
		if ( dst_size == 2) {
			rcv_header_values.destination_addr = (uint8_t)buff[j] << 8 | (uint8_t)buff[j+1] ;
			j +=2;
		} 
		if ( dst_size == 4) {
			rcv_header_values.destination_addr = (uint8_t)buff[j] << 24 | (uint8_t)buff[j+1] << 16 | (uint8_t)buff[j+2] << 8 | (uint8_t)buff[j+3] ;
			j +=4;
		}
		if ( dst_size == 16) {
		//	rcv_header_values.destination_addr = buff[j] << 24 | buff[j+1] << 16 | buff[j+2] << 8 | buff[j+3]
		//										 buff[j+4] << 24 | buff[j+5] << 16 | buff[j+6] << 8 | buff[j+7]
		//										 buff[j+8] << 24 | buff[j+9] << 16 | buff[j+10] << 8 | buff[j+11]
		//										 buff[j+12] << 24 | buff[j+13] << 16 | buff[j+14] << 8 | buff[j+15];
			j +=16;
		}
	}
	
	if ( rcv_bitmap.lenght){
		// 2 bytes long
		rcv_header_values.lenght = (uint8_t)buff[j] << 8 | (uint8_t)buff[j+1];
		j +=2;
	}
	
	if ( rcv_bitmap.ttl){
		//1 byte long
		rcv_header_values.ttl = (uint8_t)buff[j];
		j++;
	}
	
	if ( rcv_bitmap.flow){ 
		// 4 bytes long
		rcv_header_values.flow = (uint8_t)buff[j] << 24 | (uint8_t)buff[j+1] <<16 | (uint8_t)buff[j+2] << 8 | (uint8_t)buff[j+3] ;
		j +=4;
	}
	
	if ( rcv_bitmap.source){ 
		// 2-16 bytes long
		if ( src_size == 2) {
			rcv_header_values.source_addr = (uint8_t)buff[j] << 8 | (uint8_t)buff[j+1] ;
			j +=2;
		}
		if ( src_size == 4) {
			rcv_header_values.source_addr = (uint8_t)buff[j] << 24 | (uint8_t)buff[j+1] << 16 | (uint8_t)buff[j+2] << 8 | (uint8_t)buff[j+3] ;
			j +=4;
		}
		if ( src_size == 16) {
			//	rcv_header_values.source_addr = buff[j] << 24 | buff[j+1] << 16 | buff[j+2] << 8 | buff[j+3]
			//										 buff[j+4] << 24 | buff[j+5] << 16 | buff[j+6] << 8 | buff[j+7]
			//										 buff[j+8] << 24 | buff[j+9] << 16 | buff[j+10] << 8 | buff[j+11]
			//										 buff[j+12] << 24 | buff[j+13] << 16 | buff[j+14] << 8 | buff[j+15];
			j +=16;
		}
	}
	
	if ( rcv_bitmap.protocol){
		// 1 byte long
		rcv_header_values.protocol = (uint8_t)buff[j];
		j++;
	}
	
	if ( rcv_bitmap.checksum){
		// 2 bytes long
		rcv_header_values.checksum =  (uint8_t)buff[j] << 8 | (uint8_t)buff[j+1];
		j +=2;
	}
	
	i* = j;
	return 0;
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

int get_bitmap_str(char *packet, char *str, int str_len){
	uint8_t bitmap;
	int i,j;
	
	//needs at least 16 bytes + 1 (null)
	if (str_len < 17)
		return -1;
	
	//iterated for number of bytes in bitmap (1-2)	
	for (i=0; i< BITMAP_MAX_LEN; i++){
		bitmap = (uint8_t)packet[i];
		
		//iterate 8 times, store bit value in string
		for (j=0; j< 8; j++){
			strcat(str, " ");
			
			if (( bitmap & (1<< 8-j)) > 0)
				strcat(str, "1");				
			else
				strcat(str, "0");
		}
		
		//if no more continuation bytes, done, exit
		if (( bitmap & (1<<8)) == 0)
			break;
	}
	
	return 0;
}

//int get_headervals_str(char *str, int str_len){
	//char vals[64];
	//
	//// 109 in max val characters + 5*8 definitions + 1 null
	//if (str_len < 200 )
	//return -1;
	//
	//if (rcv_header_values.version > 0 ){
		//sprintf(vals, "VER: %u ", rcv_header_values.version)
		//strcat(str, vals);
	//}
	//
//}