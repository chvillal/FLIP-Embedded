#include flip.h


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