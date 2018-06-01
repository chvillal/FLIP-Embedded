

int flip_construct_header(flipHdr *flipPacket, uint16_t packet_len);
int flip_construct_packet(flipHdr *flipPacket, uint16_t packet_len);

/*
 * FLIP Packet
 */
typedef struct
{
	bool esp;
	bool version;
	bool destination;
	bool lenght;
	bool ttl;
	bool flow;
	bool source;
	bool protocol;
	bool checksum;
	
} meta_header;



/*
 * FLIP Header
 */
 
typedef struct
{
	char version;				/* FLIP header version. */
	uint16_t lenght;		    /* Length of FLIP packet (in bytes). */
	uint8_t ttl;				/* Packet time to live. */
	uint32_t flow;				/* Flow identification. */
	uint32_t source_addr;		/* FLIP source address. */
	uint32_t destination_addr;  /* FLIP destination address. */
	uint8_t protocol; 			/* Higher layer protocols. */
	uint16_t checksum; 			/* FLIP header checksum. */
	 
} flipHdr;


/*
 * FLIP Packet
 */
typedef struct
{
	flipHdr flipHeader;
	uint8_t payload[packet_len];
	
} flipPkt;