#ifndef _FLIP_H  
#define _FLIP_H

#include <stdbool.h>
#include <stdint.h>


#define FLIPO_ESP 1
#define FLIPO_VERSION 2
#define FLIPO_DESTINATION 3
#define FLIPO_LENGTH 4
#define FLIPO_TTL 5
#define FLIPO_FLOW 6
#define FLIPO_SOURCE 7
#define FLIPO_PROTOCOL 8 
#define FLIPO_CHECKSUM 9

int setsockopt(int optname, uint32_t optval, int optlen);
int add_destination(int optval, int optlen);
int add_length(int optlen);
int add_ttl(int optlen);


//int flip_construct_header(flipHdr *flipPacket, uint16_t packet_len);
//int flip_construct_packet(flipHdr *flipPacket, uint16_t packet_len);

//char* FLIP_construct_bitmap (void);

/*
 * FLIP Meta-header
 */
typedef struct
{
	bool continuation1;
	bool continuation2;
	bool esp;
	bool version;
	bool destination1;
	bool destination2;
	bool length;
	bool ttl;
	bool flow;
	bool source1;
	bool source2;
	bool protocol;
	bool checksum;
	
} meta_header;

meta_header metaHdr;

/*
 * FLIP Header
 */
 
typedef struct
{
	uint8_t version;		    /* FLIP header version. */
	uint16_t length;		    /* Length of FLIP packet (in bytes). */
	uint8_t ttl;				/* Packet time to live. */
	uint32_t flow;				/* Flow identification. */
	uint32_t source_addr;		/* FLIP source address. */
	uint32_t destination_addr;  /* FLIP destination address. */
	uint8_t protocol; 			/* Higher layer protocols. */
	uint16_t checksum; 			/* FLIP header checksum. */
	 
} flipHeader;

flipHeader flipHdr;

/*
 * FLIP Packet
 */
typedef struct
{
	flipHeader headerField;
	uint8_t payload[256];
	
} flipPacket;

flipPacket flipPkt;

#endif // FLIP_H_