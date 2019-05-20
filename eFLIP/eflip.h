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
#define GTP_FLAGS           0X4000
#define GTP_SOURCE          0X2000
#define GTP_DEST            0X1000
#define GTP_SEQ             0X0800
#define GTP_ACK             0X0400
#define GTP_TIMESTAMP       0X0200
#define GTP_CHECKSUM        0X0100
#define GTP_W_SIZE          0X0040
#define GTP_URGENT          0X0020
#define GTP_LENGTH          0X0010
#define GTP_NEXTPROTO       0X0008
#define GTP_OPT1            0X0004
#define GTP_OPT2            0X0002
#define GTP_OPT3            0X0001
#define FLIP_MAX_BITMAP_SIZE    3
#define FLIP_MAX_FIELDS_SIZE    47
#define GTP_MAX_BITMAP_SIZE     2
#define GTP_MAX_FIELDS_SIZE     28

/* STRUCTURES */
struct flipbitmap
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

struct flipfields
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

struct gtpbitmap
{
    bool cont1;
    bool flags;
    bool src;
    bool dest;
    bool seq;
    bool ack;
    bool tstamp;
    bool checksum;
    bool cont2;
    bool wsize;
    bool urgent;
    bool len;
    bool nextp;
    bool opt1;
    bool opt2;
    bool opt3;
};

struct gtpfields
{
    uint8_t flags;
    uint16_t src;
    uint16_t dest;
    uint32_t seq;
    uint32_t ack;
    uint32_t tstamp;
    uint16_t checksum;
    uint32_t wsize;
    uint16_t urgent;
    uint16_t len;
    uint8_t nextp;
};
/* CLASSES */

// FLIPSOCKET CLASS stores all information relevant to a single Flip socket
// provides cuntionality to set, get, and clear bits and corresponding fields
class FlipSocket {
private:
    flipbitmap m_metaheader;
    flipfields m_metafields;
    
public:
    //Constructors
    FlipSocket()
    {
        FlipSocket::clear_metaheader();
        FlipSocket::clear_metafields();
    }
    
    void set_metaheader(int32_t bitmask, bool state);
    bool get_metaheader(uint32_t bitmask);
    void clear_metaheader();
    void clear_metafields();
    void set_cont_bits();
    
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

    uint8_t get_version()   { return m_metafields.version; };
    uint64_t get_dest()     { return m_metafields.dest_hst; };
    uint8_t get_type()      { return m_metafields.type; };
    uint8_t get_ttl()       { return m_metafields.ttl; };
    uint32_t get_flow()     { return m_metafields.flow; };
    uint64_t get_src()      { return m_metafields.src_hst; };
    uint16_t get_len()      { return m_metafields.length; };
    uint16_t get_checksum() { return m_metafields.checksum; };
    uint16_t get_offset()   { return m_metafields.offset; };
    
};

class GTPsocket {
private:
    gtpbitmap m_metaheader;
    gtpfields m_metafields;
    
public:
    //Constructor
    GTPsocket()
    {
        clear_metafields();
        clear_metaheader();
    }
    
    void set_metabit(uint16_t bitmask, bool state);
    bool get_metabit(uint16_t bitmask);
    void clear_metaheader();
    void clear_metafields();
    void set_cont_bits();
    
    void set_flags(uint8_t flags) {m_metafields.flags = flags ;};
    void set_src(uint16_t src) {m_metafields.src = src ;};
    void set_dest(uint16_t dest) {m_metafields.dest = dest ;};
    void set_seq(uint32_t seq) {m_metafields.seq = seq ;};
    void set_ack(uint32_t ack) {m_metafields.ack = ack ;};
    void set_tstamp(uint32_t tstamp) {m_metafields.tstamp = tstamp ;};
    void set_checksum(uint16_t checksum) {m_metafields.checksum = checksum ;};
    void set_wsize(uint32_t wsize) {m_metafields.wsize = wsize ;};
    void set_urgent(uint16_t urgent) {m_metafields.urgent = urgent ;};
    void set_len(uint16_t len) {m_metafields.len = len ;};
    void set_nextp(uint8_t nextp) {m_metafields.nextp = nextp ;};
    
    uint8_t get_flags() {return m_metafields.flags ;};
    uint16_t get_src() {return m_metafields.src ;};
    uint16_t get_dest() {return m_metafields.dest ;};
    uint32_t get_seq() {return m_metafields.seq ;};
    uint32_t get_ack() {return m_metafields.ack ;};
    uint32_t get_tstamp() {return m_metafields.tstamp ;};
    uint16_t get_checksum() {return m_metafields.checksum ;};
    uint32_t get_wsize() {return m_metafields.wsize ;};
    uint16_t get_urgent() {return m_metafields.urgent ;};
    uint16_t get_len() {return m_metafields.len ;};
    uint8_t get_nextp() {return m_metafields.nextp ;};
    
};

// PACKET CLASS provides functionality to construct, and read FLIPSOCKET packets.
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
    
    //build FLIP bitmap and fields
    void build_metaheader(FlipSocket s);
    void build_metafields(FlipSocket s);
    
    uint8_t* get_metafields() {return m_fields;};
    int get_fields_size() {return fields_size;};
    
    uint8_t* get_bitmap() {return m_bitmap;};
    int get_bitmap_size() {return bitmap_size;};
    
    int parse_flip_metaheader(FlipSocket *s, uint8_t *message, int m_size);
    int parse_flip_metafields(FlipSocket *s, uint8_t *message, int m_size, int index);
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
void print_gtp_metaheader(GTPsocket g);
void print_gtp_metafields(GTPsocket g);


#endif /* eflip_h */
