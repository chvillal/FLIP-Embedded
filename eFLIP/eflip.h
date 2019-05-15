//
//  eflip.h
//  eFLIP
//
//  Created by Christopher Villalpando on 5/6/19.
//  Copyright © 2019 Christopher Villalpando. All rights reserved.
//

#ifndef eflip_h
#define eflip_h

/* LIBRARIES */
#include <stdint.h>
//#include <string.h>

/* DEFINES */
#define FLIP_ESP            1
#define FLIP_VERSION        2
#define FLIP_DESTINATION    3
#define FLIP_TYPE           4
#define FLIP_TTL            5
#define FLIP_FLOW           6
#define FLIP_SOURCE         7
#define FLIP_LENGTH         8
#define FLIP_CHECKSUM       9
#define FLIP_NOFRAG         10
#define FLIP_OPT1           11
#define FLIP_OPT2           12
#define FLIP_FRAGOFFSET     13
#define FLIP_LASTFRAG       14
#define FLIPO_OPT3          15
#define FLIPO_OPT4          16
#define FLIPO_OPT5          17
#define FLIPO_OPT6          18
#define FLIPO_OPT7          19



/* STRUCTURES */
struct metaheader
{
    bool cont1;
    bool esp;
    bool ver;
    bool dest1;
    bool dest2;
    bool type;
    bool ttl;
    bool flow;
    bool cont2;
    bool source1;
    bool source2;
    bool length;
    bool checksum;
    bool no_frag;
    bool opt1;
    bool opt2;
    bool cont3;
    bool frag_offset;
    bool last_frag;
    bool opt3;
    bool opt4;
    bool opt5;
    bool opt6;
    bool opt7;
};

struct metafields
{
    uint8_t  version;
    uint32_t dest;
    uint8_t  type;
    uint8_t  ttl;
    uint32_t flow;
    uint32_t source;
    uint16_t length;    //dynamic
    uint16_t checksum;  //dynamic
    uint16_t offset;
};

/* CLASSES */
class FlipSocket {
private:
    metaheader m_metaheader;
    metafields m_metafields;
    
public:
    //Constructors
    FlipSocket(){}
    
    //header field values
    void set_version(uint8_t ver);
    void set_dest(uint32_t dest);
    void set_type(uint8_t type);
    void set_ttl(uint8_t ttl);
    void set_flow(uint32_t flow);
    void set_src(uint32_t src);
    void set_len(uint16_t len);
    void set_checksum(uint16_t checksum);
    void set_offset(uint16_t offset);

    int get_version()   { return m_metafields.version; };
    int get_dest()      { return m_metafields.dest; };
    int get_type()      { return m_metafields.type; };
    int get_ttl()       { return m_metafields.ttl; };
    int get_flow()      { return m_metafields.flow; };
    int get_src()       { return m_metafields.source; };
    int get_len()       { return m_metafields.length; };
    int get_checksum()  { return m_metafields.checksum; };
    int get_offset()    { return m_metafields.offset; };
    
    //header field values
    void set_field();
    int  get_field();
    
    //metaheader bitmap bits
    void set_bitmap();
    void set_bitfield();
    int get_bitmap();
    int get_bitfield();
    
    
};

int setsocketopt();
int getsocketopt();

int read();
int write();

//typedef struct
//{
//    //flip_header headerField;
//    uint8_t payload[256];
//
//} flipPacket;

/* FUNCTION DECLARATIONS */
//uint32_t test_function(uint32_t num);
//
//int setsockopt (int optname, uint32_t optval, int optlen);
//int getsockopt(int optname, uint32_t *optval);
//int add_version (uint32_t optva);
//int add_destination (uint32_t optval, int optlen);
//int add_length (uint32_t optva);
//int add_ttl (uint32_t optval);
//int add_flow (uint32_t optval);
//int add_source (uint32_t optval, int optlen);
//int add_protocol (uint32_t optval);
//int add_checksum (uint32_t optval);
//
//char* FLIP_construct_bitmap (void);
//char* FLIP_construct_header (void);
//char* FLIP_construct_packet (char *bitmap, char *header, char *payload);
//
//int flip_read_packet(char *buff, int buff_len, int *index);
//int read_bitmap(char *buff, int *i, int *dst_size, int *src_size);
//int read_header_values(char *buff, int *i, int dst_size, int src_size);
//
//void read_rcv_values(void);
//int get_bitmap_str(char *packet, char *str, int str_len);
//int get_headervals_str(char *str, int str_len);
//
//char* mod_strncat(char *dest, const char *src, size_t n, int *index);
//void reset_values (uint32_t optval);
//
//int get_packet_length();
//
//void reset_bitmap(meta_header *bitmap);
//void reset_header(flip_header *header_values);
//void read_rcv_flags(void);


#endif /* eflip_h */
