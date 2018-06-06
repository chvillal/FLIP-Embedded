#ifndef _FLIP_H  
#define _FLIP_H

/* LIBRARIES */
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

/* DEFINES */
#define FLIPO_CONTINUATION 1
#define FLIPO_ESP 2
#define FLIPO_VERSION 3
#define FLIPO_DESTINATION 4
#define FLIPO_LENGTH 5
#define FLIPO_TTL 6
#define FLIPO_FLOW 7
#define FLIPO_SOURCE 8
#define FLIPO_PROTOCOL 9 
#define FLIPO_CHECKSUM 10

/* FUNCTION DECLARATIONS */
uint32_t test_function(uint32_t num);

int setsockopt(int optname, uint32_t optval, int optlen);
int add_version(uint32_t optva);
int add_destination(uint32_t optval, int optlen);
int add_length(uint32_t optva);
int add_ttl(uint32_t optval);
int add_flow(uint32_t optval);
int add_source(uint32_t optval, int optlen);
int add_protocol(uint32_t optval);
int add_checksum(uint32_t optval);

char* FLIP_construct_packet(char *bitmap, char *packet);
char* FLIP_construct_bitmap (void);

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


/*
 * FLIP Packet
 */
typedef struct
{
	flipHeader headerField;
	uint8_t payload[256];
	
} flipPacket;



#endif // FLIP_H_