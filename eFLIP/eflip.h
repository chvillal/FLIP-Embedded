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

/* DEFINES */
#define FLIP_ESP            0x400000
#define FLIP_VERSION        0x200000
#define FLIP_DEST_1         0x080000    // destination address is size 1 byte (sensors)
#define FLIP_DEST_4         0x100000    // destination address is size 4 bytess (ipv4)
#define FLIP_DEST_16        0x180000    // destination address is size 16 bytes (ipv6)
#define FLIP_TYPE           0x040000
#define FLIP_TTL            0x020000
#define FLIP_FLOW           0x010000
#define FLIP_SOURCE_1       0x002000    // source address is size 1 byte (sensors)
#define FLIP_SOURCE_4       0x004000    // source address is size 4 bytes (ipv4)
#define FLIP_SOURCE_16      0x006000    // source address is size 16 bytes (ipv6)
#define FLIP_LENGTH         0x001000
#define FLIP_CHECKSUM       0x000800
#define FLIP_NOFRAG         0x000400
#define FLIP_OPT1           0x000200
#define FLIP_OPT2           0x000100
#define FLIP_FRAGOFFSET     0x000040
#define FLIP_LASTFRAG       0x000020
#define FLIP_OPT3           0x000010
#define FLIP_OPT4           0x000008
#define FLIP_OPT5           0x000004
#define FLIP_OPT6           0x000002
#define FLIP_OPT7           0x000001

#define FLIP_MAX_BITMAP_SIZE    3
#define FLIP_MAX_FIELDS_SIZE    47


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
    uint64_t dest_hst;
    uint64_t dest_net;
    uint8_t  type;
    uint8_t  ttl;
    uint32_t flow;
    uint64_t src_hst;
    uint64_t src_net;
    uint16_t length;    //dynamic
    uint16_t checksum;  //dynamic
    uint16_t offset;
};

/* CLASSES */

// FLIPSOCKET CLASS stores all information relevant to a single Flip socket
// provides cuntionality to set, get, and clear bits and corresponding fields
class FlipSocket {
private:
    metaheader m_metaheader;
    metafields m_metafields;
    //char *bitmap[4]{};
    
public:
    //Constructors
    FlipSocket()
    {
        FlipSocket::clear_metaheader();
        FlipSocket::clear_metafields();
    }
    
    //metaheader bitmap bits
    void set_metaheader(int32_t bitmask, bool state);
    bool get_metaheader(uint32_t bitmask);
    void clear_metaheader();
    
    //header field values
    void set_version(uint8_t ver);
    void set_dest(uint64_t dest);
    void set_type(uint8_t type);
    void set_ttl(uint8_t ttl);
    void set_flow(uint32_t flow);
    void set_src(uint64_t src);
    void set_len(uint16_t len);
    void set_checksum(uint16_t checksum);
    void set_offset(uint16_t offset);

    int get_version()   { return m_metafields.version; };
    long get_dest()     { return m_metafields.dest_hst; };
    int get_type()      { return m_metafields.type; };
    int get_ttl()       { return m_metafields.ttl; };
    int get_flow()      { return m_metafields.flow; };
    long get_src()      { return m_metafields.src_hst; };
    int get_len()       { return m_metafields.length; };
    int get_checksum()  { return m_metafields.checksum; };
    int get_offset()    { return m_metafields.offset; };
    
    void clear_metafields();
    
    //other, maybe private?
    void set_cont_bits();
    
};

// PACKET CLASS provides functionality to construct, and read
// FLIPSOCKET packets.
class SocketHandler {
private:
    int bitmap_size;
    int fields_size;
    uint8_t m_bitmap[FLIP_MAX_BITMAP_SIZE+1]{};
    uint8_t m_fields[FLIP_MAX_FIELDS_SIZE+1]{};
    //FlipSocket socket;
    //bool modified;
    
public:
    //constructor
    SocketHandler(){}
    
    //build bitmap and fields
    void get_flip_metaheader(FlipSocket s);
    void get_flip_metafields(FlipSocket s);
    
    uint8_t* get_metafields() {return m_fields;};
    int get_fields_size() {return fields_size;};
    
    uint8_t* get_bitmap() {return m_bitmap;};
    int get_bitmap_size() {return bitmap_size;};
    
    int parse_flip_metaheader(FlipSocket *s, uint8_t *message, int m_size);
    int parse_flip_metafields(FlipSocket s, uint8_t *message, int m_size);
};

/* PUBLIC FUNCTIONS */
int setsocketopt();
int getsocketopt();
int read();
int write();


/* HELPER/PRIVATE FUNCTIONS */
//uint8_t* get_flip_metaheader(FlipSocket s);

/* TEST FUNCTIONS */
void print_metaheader(FlipSocket s);
void print_metafields(FlipSocket s);



#endif /* eflip_h */
