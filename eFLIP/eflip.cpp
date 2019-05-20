//
//  eflip.cpp
//  eFLIP
//
//  Created by Christopher Villalpando on 5/5/19.
//  Copyright © 2019 Christopher Villalpando. All rights reserved.
//

/* LIBRARIES */
#include "eflip.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>


/* DEFINES */
#define FLIP_CONT1      0x800000
#define FLIP_CONT2      0x008000
#define FLIP_CONT3      0x000080
#define GTP_CONT1       0x8000
#define GTP_CONT2       0x0080

//#define BITMAP_MAXLEN   2
//#define MAX_STR_SIZE    128 //temporary, not sure what max lora string len is...


/* CLASS FUNCTIONS */
void FlipSocket::set_version(uint8_t ver)
{
    m_metafields.version = ver;
}

void FlipSocket::set_dest(uint64_t dest)
{
    m_metafields.dest_hst = dest;
}

void FlipSocket::set_type(uint8_t type)
{
    m_metafields.type = type;
}

void FlipSocket::set_ttl(uint8_t ttl)
{
    m_metafields.ttl = ttl;
}

void FlipSocket::set_flow(uint32_t flow)
{
    m_metafields.flow = flow;
}

void FlipSocket::set_src(uint64_t src)
{
    m_metafields.src_hst = src;
}

void FlipSocket::set_len(uint16_t len) // dynamic - needs rework
{
    m_metafields.length = len;
}

void FlipSocket::set_checksum(uint16_t checksum) //dynamic - needs rework
{
    m_metafields.checksum = checksum;
}

void FlipSocket::set_offset(uint16_t offset)
{
    m_metafields.offset = offset;
}

void FlipSocket::clear_metafields()
{
    m_metafields.version = 0;
    m_metafields.dest_hst = 0;
    m_metafields.dest_net = 0;
    m_metafields.type = 0;
    m_metafields.ttl = 0;
    m_metafields.flow = 0;
    m_metafields.src_hst = 0;
    m_metafields.src_net = 0;
    m_metafields.length = 0;    //dynamic
    m_metafields.checksum = 0;  //dynamic
    m_metafields.offset = 0;
}

void FlipSocket::set_metaheader(int32_t bitmask, bool state)
{
    switch(bitmask)
    {
        case FLIP_CONT1:
            m_metaheader.cont1 = state;
            break;
        case FLIP_CONT2:
            m_metaheader.cont2 = state;
            break;
        case FLIP_CONT3:
            m_metaheader.cont3 = state;
            break;
        case FLIP_ESP:
            m_metaheader.esp = state;
            break;
        case FLIP_VERSION:
            m_metaheader.ver = state;
            break;
        case FLIP_DEST_1:
            m_metaheader.dest2 = state;
            //m_metaheader.dest1 = false;
            break;
        case FLIP_DEST_4:
            m_metaheader.dest1 = state;
            //m_metaheader.dest2 = false;
            break;
        case FLIP_DEST_16:
            m_metaheader.dest1 = state;
            m_metaheader.dest2 = state;
            break;
        case FLIP_TYPE:
            m_metaheader.type = state;
            break;
        case FLIP_TTL:
            m_metaheader.ttl = state;
            break;
        case FLIP_FLOW:
            m_metaheader.flow = state;
            break;
        case FLIP_SOURCE_1:
            m_metaheader.source2 = state;
            //m_metaheader.source1 = false;
            break;
        case FLIP_SOURCE_4:
            m_metaheader.source1 = state;
            //m_metaheader.source2 = false;
            break;
        case FLIP_SOURCE_16:
            m_metaheader.source1 = state;
            m_metaheader.source2 = state;
            break;
        case FLIP_LENGTH:
            m_metaheader.length = state;
            break;
        case FLIP_CHECKSUM:
            m_metaheader.checksum = state;
            break;
        case FLIP_NOFRAG:
            m_metaheader.no_frag = state;
            break;
        case FLIP_OPT1:
            m_metaheader.opt1 = state;
            break;
        case FLIP_OPT2:
            m_metaheader.opt2 = state;
            break;
        case FLIP_FRAGOFFSET:
            m_metaheader.frag_offset = state;
            break;
        case FLIP_LASTFRAG:
            m_metaheader.last_frag = state;
            break;
        case FLIP_OPT3:
            m_metaheader.opt3 = state;
            break;
        case FLIP_OPT4:
            m_metaheader.opt4 = state;
            break;
        case FLIP_OPT5:
            m_metaheader.opt5 = state;
            break;
        case FLIP_OPT6:
            m_metaheader.opt6 = state;
            break;
        case FLIP_OPT7:
            m_metaheader.opt7 = state;
            break;
        default:
            break;
    }
}

bool FlipSocket::get_metaheader(uint32_t bitmask)
{
    switch(bitmask)
    {
        case FLIP_ESP:
            return m_metaheader.esp;
        case FLIP_VERSION:
            return m_metaheader.ver;
        case FLIP_DEST_1:
            return m_metaheader.dest2;
        case FLIP_DEST_4:
            return m_metaheader.dest1;
        case FLIP_DEST_16:
            return (m_metaheader.dest1 && m_metaheader.dest2);
        case FLIP_TYPE:
            return m_metaheader.type;
        case FLIP_TTL:
            return m_metaheader.ttl;
        case FLIP_FLOW:
            return m_metaheader.flow;
        case FLIP_SOURCE_1:
            return m_metaheader.source2;
        case FLIP_SOURCE_4:
            return m_metaheader.source1;
        case FLIP_SOURCE_16:
            return (m_metaheader.source1 && m_metaheader.source2);
        case FLIP_LENGTH:
            return m_metaheader.length;
        case FLIP_CHECKSUM:
            return m_metaheader.checksum;
        case FLIP_NOFRAG:
            return m_metaheader.no_frag;
        case FLIP_OPT1:
            return m_metaheader.opt1;
        case FLIP_OPT2:
            return m_metaheader.opt2;
        case FLIP_FRAGOFFSET:
            return m_metaheader.frag_offset;
        case FLIP_LASTFRAG:
            return m_metaheader.last_frag;
        case FLIP_OPT3:
            return m_metaheader.opt3;
        case FLIP_OPT4:
            return m_metaheader.opt4;
        case FLIP_OPT5:
            return m_metaheader.opt5;
        case FLIP_OPT6:
            return m_metaheader.opt6;
        case FLIP_OPT7:
            return m_metaheader.opt7;
        case FLIP_CONT1:
            //std::cout << "\nLOG: get_metaheader(): return bool: " << m_metaheader.cont1 << std::endl;
            return m_metaheader.cont1;
        case FLIP_CONT2:
            return m_metaheader.cont2;
        case FLIP_CONT3:
            return m_metaheader.cont3;
        default:
            break;
    }
    //if it gets here, error
    return false;
}

void FlipSocket::clear_metaheader()
{
    m_metaheader.esp = false;
    m_metaheader.ver = false;
    m_metaheader.dest1 = false;
    m_metaheader.dest2 = false;
    m_metaheader.type = false;
    m_metaheader.ttl = false;
    m_metaheader.flow = false;
    m_metaheader.source1 = false;
    m_metaheader.source2 = false;
    m_metaheader.length = false;
    m_metaheader.checksum = false;
    m_metaheader.no_frag = false;
    m_metaheader.opt1 = false;
    m_metaheader.opt2 = false;
    m_metaheader.frag_offset = false;
    m_metaheader.last_frag = false;
    m_metaheader.opt3 = false;
    m_metaheader.opt4 = false;
    m_metaheader.opt5 = false;
    m_metaheader.opt6 = false;
    m_metaheader.opt7 = false;
}


/* WRAPPER FUNCTIONS */
int setsocketopt()
{
    return 0;
}

int getsocketopt()
{
    return 0;
}

int read()
{
    return 0;
}

int write()
{
    return 0;
}

void FlipSocket::set_cont_bits()
{
    
    // if any bitfields set on 3rd byte, enable continuation bits 1 and 2
    if ( m_metaheader.frag_offset || m_metaheader.last_frag || m_metaheader.opt3 || m_metaheader.opt4 ||
         m_metaheader.opt5 || m_metaheader.opt6 || m_metaheader.opt7 )
    {
        m_metaheader.cont1 = true;
        m_metaheader.cont2 = true;
        
    } else if ( m_metaheader.source1 || m_metaheader.source2 || m_metaheader.length || m_metaheader.checksum ||
        m_metaheader.no_frag || m_metaheader.opt1 || m_metaheader.opt2 )
    {
        m_metaheader.cont1 = true;
        m_metaheader.cont2 = false;
        //std::cout << "\nLOG: set_cont_bits: cont1=true : " << m_metaheader.cont1 << std::endl;
    } else {
        m_metaheader.cont1 = false;
        m_metaheader.cont2 = false;
        //std::cout << "LOG: set_cont_bits: cont1=false\n" ;
    }
    
    //redundant under current version, but set for sanity.
    m_metaheader.cont3 = false;
}

void GTPsocket::set_metabit(uint16_t bitmask, bool state)
{
    switch (bitmask)
    {
        case GTP_CONT1:
            m_metaheader.cont1 = state;
            break;
        case GTP_FLAGS:
            m_metaheader.flags = state;
            break;
        case GTP_SOURCE:
            m_metaheader.src = state;
            break;
        case GTP_DEST:
            m_metaheader.dest = state;
            break;
        case GTP_SEQ:
            m_metaheader.seq = state;
            break;
        case GTP_ACK:
            m_metaheader.ack = state;
            break;
        case GTP_TIMESTAMP:
            m_metaheader.tstamp = state;
            break;
        case GTP_CHECKSUM:
            m_metaheader.checksum = state;
            break;
        case GTP_CONT2:
            m_metaheader.cont2 = state;
            break;
        case GTP_W_SIZE:
            m_metaheader.wsize = state;
            break;
        case GTP_URGENT:
            m_metaheader.urgent = state;
            break;
        case GTP_LENGTH:
            m_metaheader.len = state;
            break;
        case GTP_NEXTPROTO:
            m_metaheader.nextp = state;
            break;
        case GTP_OPT1:
            m_metaheader.opt1 = state;
            break;
        case GTP_OPT2:
            m_metaheader.opt2 = state;
            break;
        case GTP_OPT3:
            m_metaheader.opt3 = state;
            break;
        default:
            break;
    }
}

bool GTPsocket::get_metabit(uint16_t bitmask)
{
    switch (bitmask)
    {
        case GTP_CONT1:
            return m_metaheader.cont1;
        case GTP_FLAGS:
            return m_metaheader.flags;
        case GTP_SOURCE:
            return m_metaheader.src;
        case GTP_DEST:
            return m_metaheader.dest;
        case GTP_SEQ:
            return m_metaheader.seq;
        case GTP_ACK:
            return m_metaheader.ack;
        case GTP_TIMESTAMP:
            return m_metaheader.tstamp;
        case GTP_CHECKSUM:
            return m_metaheader.checksum;
        case GTP_CONT2:
            return m_metaheader.cont2;
        case GTP_W_SIZE:
            return m_metaheader.wsize;
        case GTP_URGENT:
            return m_metaheader.urgent;
        case GTP_LENGTH:
            return m_metaheader.len;
        case GTP_NEXTPROTO:
            return m_metaheader.nextp;
        case GTP_OPT1:
            return m_metaheader.opt1;
        case GTP_OPT2:
            return m_metaheader.opt2;
        case GTP_OPT3:
            return m_metaheader.opt3;
        default:
            break;
    }
    
    //if it gets here, error
    return false;
}

void GTPsocket::clear_metaheader()
{
    m_metaheader.flags = false;
    m_metaheader.src = false;
    m_metaheader.dest = false;
    m_metaheader.seq = false;
    m_metaheader.ack = false;
    m_metaheader.tstamp = false;
    m_metaheader.checksum = false;
    m_metaheader.wsize = false;
    m_metaheader.urgent = false;
    m_metaheader.len = false;
    m_metaheader.nextp = false;
    m_metaheader.opt1 = false;
    m_metaheader.opt2 = false;
    m_metaheader.opt3 = false;
}

void GTPsocket::clear_metafields()
{
    m_metafields.flags = 0;
    m_metafields.src = 0;
    m_metafields.dest = 0;
    m_metafields.seq = 0;
    m_metafields.ack = 0;
    m_metafields.tstamp = 0;
    m_metafields.checksum = 0;
    m_metafields.wsize = 0;
    m_metafields.urgent = 0;
    m_metafields.len = 0;
    m_metafields.nextp = 0;
}

void GTPsocket::set_cont_bits()
{
    if ( m_metaheader.wsize || m_metaheader.urgent || m_metaheader.len || m_metaheader.nextp ||
         m_metaheader.opt1 || m_metaheader.opt2 || m_metaheader.opt3 )
    {
        m_metaheader.cont1 = true;
    } else {
        m_metaheader.cont1 = false;
    }
    
    // additional metaheader bystes pending, limited to 2 bytes for now.
    m_metaheader.cont2 = false;
}

/* HELPER FUNCTIONS */

void SocketHandler::build_metaheader(FlipSocket s)
{
    //int bitmap_size;
    //uint8_t m_bitmap[FLIP_MAX_BITMAP_SIZE+1]{};
    
    // update continuation bits now
    s.set_cont_bits();
    s.get_metaheader(FLIP_CONT1)   ? m_bitmap[0] = m_bitmap[0] | (FLIP_CONT1 >> 16)  : m_bitmap[0] = m_bitmap[0] & (~FLIP_CONT1 >> 16);
    s.get_metaheader(FLIP_CONT2)   ? m_bitmap[1] = m_bitmap[1] | (FLIP_CONT2 >> 8)   : m_bitmap[1] = m_bitmap[1] & (~FLIP_CONT2 >> 8);
    s.get_metaheader(FLIP_CONT3)   ? m_bitmap[2] = m_bitmap[2] | (FLIP_CONT3)        : m_bitmap[2] = m_bitmap[2] & (~FLIP_CONT3);
    
    //parse flipsocket enabled fields to bitmap
    s.get_metaheader(FLIP_ESP)     ? m_bitmap[0] = m_bitmap[0] | (FLIP_ESP >> 16)    : m_bitmap[0] = m_bitmap[0] & (~FLIP_ESP >> 16);
    s.get_metaheader(FLIP_VERSION) ? m_bitmap[0] = m_bitmap[0] | (FLIP_VERSION>> 16) : m_bitmap[0] = m_bitmap[0] & (~FLIP_VERSION >> 16);
    s.get_metaheader(FLIP_DEST_4)  ? m_bitmap[0] = m_bitmap[0] | (FLIP_DEST_4 >> 16) : m_bitmap[0] = m_bitmap[0] & (~FLIP_DEST_4 >> 16);
    s.get_metaheader(FLIP_DEST_1)  ? m_bitmap[0] = m_bitmap[0] | (FLIP_DEST_1 >> 16) : m_bitmap[0] = m_bitmap[0] & (~FLIP_DEST_1 >> 16);
    s.get_metaheader(FLIP_TYPE)    ? m_bitmap[0] = m_bitmap[0] | (FLIP_TYPE >> 16)   : m_bitmap[0] = m_bitmap[0] & (~FLIP_TYPE >> 16);
    s.get_metaheader(FLIP_TTL)     ? m_bitmap[0] = m_bitmap[0] | (FLIP_TTL >> 16)    : m_bitmap[0] = m_bitmap[0] & (~FLIP_TTL >> 16);
    s.get_metaheader(FLIP_FLOW)    ? m_bitmap[0] = m_bitmap[0] | (FLIP_FLOW >> 16)   : m_bitmap[0] = m_bitmap[0] & (~FLIP_FLOW >> 16);
    
    s.get_metaheader(FLIP_SOURCE_4) ? m_bitmap[1] = m_bitmap[1] | (FLIP_SOURCE_4 >> 8) : m_bitmap[1] = m_bitmap[1] & (~FLIP_SOURCE_4 >> 8);
    s.get_metaheader(FLIP_SOURCE_1) ? m_bitmap[1] = m_bitmap[1] | (FLIP_SOURCE_1 >> 8) : m_bitmap[1] = m_bitmap[1] & (~FLIP_SOURCE_1 >> 8);
    s.get_metaheader(FLIP_LENGTH)   ? m_bitmap[1] = m_bitmap[1] | (FLIP_LENGTH >> 8)   : m_bitmap[1] = m_bitmap[1] & (~FLIP_LENGTH >> 8);
    s.get_metaheader(FLIP_CHECKSUM) ? m_bitmap[1] = m_bitmap[1] | (FLIP_CHECKSUM >> 8) : m_bitmap[1] = m_bitmap[1] & (~FLIP_CHECKSUM >> 8);
    s.get_metaheader(FLIP_NOFRAG)   ? m_bitmap[1] = m_bitmap[1] | (FLIP_NOFRAG >> 8)   : m_bitmap[1] = m_bitmap[1] & (~FLIP_NOFRAG >> 8);
    s.get_metaheader(FLIP_OPT1)     ? m_bitmap[1] = m_bitmap[1] | (FLIP_OPT1 >> 8)     : m_bitmap[1] = m_bitmap[1] & (~FLIP_OPT1 >> 8);
    s.get_metaheader(FLIP_OPT2)     ? m_bitmap[1] = m_bitmap[1] | (FLIP_OPT2 >> 8)     : m_bitmap[1] = m_bitmap[1] & (~FLIP_OPT2 >> 8);
    
    s.get_metaheader(FLIP_FRAGOFFSET) ? m_bitmap[2] = m_bitmap[2] | FLIP_FRAGOFFSET : m_bitmap[2] = m_bitmap[2] & ~FLIP_FRAGOFFSET;
    s.get_metaheader(FLIP_LASTFRAG)   ? m_bitmap[2] = m_bitmap[2] | FLIP_LASTFRAG   : m_bitmap[2] = m_bitmap[2] & ~FLIP_LASTFRAG;
    s.get_metaheader(FLIP_OPT3)       ? m_bitmap[2] = m_bitmap[2] | FLIP_OPT3       : m_bitmap[2] = m_bitmap[2] & ~FLIP_OPT3;
    s.get_metaheader(FLIP_OPT4)       ? m_bitmap[2] = m_bitmap[2] | FLIP_OPT4       : m_bitmap[2] = m_bitmap[2] & ~FLIP_OPT4;
    s.get_metaheader(FLIP_OPT5)       ? m_bitmap[2] = m_bitmap[2] | FLIP_OPT5       : m_bitmap[2] = m_bitmap[2] & ~FLIP_OPT5;
    s.get_metaheader(FLIP_OPT6)       ? m_bitmap[2] = m_bitmap[2] | FLIP_OPT6       : m_bitmap[2] = m_bitmap[2] & ~FLIP_OPT6;
    s.get_metaheader(FLIP_OPT7)       ? m_bitmap[2] = m_bitmap[2] | FLIP_OPT7       : m_bitmap[2] = m_bitmap[2] & ~FLIP_OPT7;

    if (s.get_metaheader(FLIP_CONT3)){
        bitmap_size = 4;
    } else if (s.get_metaheader(FLIP_CONT2)) {
        bitmap_size = 3;
    } else if (s.get_metaheader(FLIP_CONT1)){
        bitmap_size = 2;
    } else {
        bitmap_size = 1;
    }
    
}

void SocketHandler::build_metafields(FlipSocket s)
{
    //int fields_size;
    //uint8_t m_fields[FLIP_MAX_FIELDS_SIZE+1]{};
    int index = 0;
    
    if (s.get_metaheader(FLIP_VERSION)){
        m_fields[index] = s.get_version();
        index++;
    }
    
    if (s.get_metaheader(FLIP_DEST_16))
    {
        //first byte tells size, 1-16 for now
        //implementation pending
        
    } else if (s.get_metaheader(FLIP_DEST_4)) {
        m_fields[index] = (s.get_dest() & 0xFF000000) >> 24;
        index++;
        m_fields[index] = (s.get_dest() & 0xFF0000) >> 16;
        index++;
        m_fields[index] = (s.get_dest() & 0xFF00) >> 8;
        index++;
        m_fields[index] = (s.get_dest() & 0xFF);
        index++;
        
    } else if (s.get_metaheader(FLIP_DEST_1)) {
        m_fields[index] = (s.get_dest() & 0xFF);
        index++;
    }
    
    if (s.get_metaheader(FLIP_TYPE)) {
        m_fields[index] = s.get_type();
        index++;
    }
    
    if (s.get_metaheader(FLIP_TTL)) {
        m_fields[index] = s.get_ttl();
        index++;
    }
    
    if (s.get_metaheader(FLIP_FLOW)) {
        m_fields[index] = (s.get_flow() & 0xFF000000) >> 24;
        index++;
        m_fields[index] = (s.get_flow() & 0xFF0000) >> 16;
        index++;
        m_fields[index] = (s.get_flow() & 0xFF00) >> 8;
        index++;
        m_fields[index] = (s.get_flow() & 0xFF);
        index++;
    }
    
    if (s.get_metaheader(FLIP_SOURCE_16))
    {
        //first byte tells size, 1-16 for now
        //implementation pending
        
    } else if (s.get_metaheader(FLIP_SOURCE_4)) {
        m_fields[index] = (s.get_src() & 0xFF000000) >> 24;
        index++;
        m_fields[index] = (s.get_src() & 0xFF0000) >> 16;
        index++;
        m_fields[index] = (s.get_src() & 0xFF00) >> 8;
        index++;
        m_fields[index] = (s.get_src() & 0xFF);
        index++;
        
    } else if (s.get_metaheader(FLIP_SOURCE_1)) {
        m_fields[index] = (s.get_src() & 0xFF);
        index++;
    }
    
    if (s.get_metaheader(FLIP_LENGTH)) {
        m_fields[index] = (s.get_len() & 0xFF00) >> 8;
        index++;
        m_fields[index] = (s.get_len() & 0xFF);
        index++;
    }
    
    if (s.get_metaheader(FLIP_CHECKSUM)) {
        m_fields[index] = (s.get_checksum() & 0xFF00) >> 8;
        index++;
        m_fields[index] = (s.get_checksum() & 0xFF);
        index++;
    }
    
    if (s.get_metaheader(FLIP_FRAGOFFSET)) {
        m_fields[index] = (s.get_offset() & 0xFF00) >> 8;
        index++;
        m_fields[index] = (s.get_offset() & 0xFF);
        index++;
    }
    
    //at this point, index is pointing to a null bit alfter the last field
    //in m_fields.
    if (index != 0){
        fields_size = index - 1;
    }
}

int SocketHandler::parse_flip_metaheader(FlipSocket *s, uint8_t *message, int m_size)
{
    
    int i = 0;
    if (m_size < 1) {return 0;};
    
    // check if larger than 1 byte bitmap
    (message[i] & (FLIP_CONT1 >> 16))   ? s->set_metaheader(FLIP_CONT1, true)  : s->set_metaheader(FLIP_CONT1, false);
    (message[i] & (FLIP_ESP >> 16))     ? s->set_metaheader(FLIP_ESP, true)    : s->set_metaheader(FLIP_ESP, false);
    (message[i] & (FLIP_VERSION >> 16)) ? s->set_metaheader(FLIP_VERSION, true): s->set_metaheader(FLIP_VERSION, false);
    (message[i] & (FLIP_DEST_4 >> 16))  ? s->set_metaheader(FLIP_DEST_4, true) : s->set_metaheader(FLIP_DEST_4 , false);
    (message[i] & (FLIP_DEST_1 >> 16))  ? s->set_metaheader(FLIP_DEST_1, true) : s->set_metaheader(FLIP_DEST_1 , false);
    (message[i] & (FLIP_TYPE >> 16))    ? s->set_metaheader(FLIP_TYPE, true)   : s->set_metaheader(FLIP_TYPE , false);
    (message[i] & (FLIP_TTL >> 16))     ? s->set_metaheader(FLIP_TTL, true)    : s->set_metaheader(FLIP_TTL , false);
    (message[i] & (FLIP_FLOW >> 16))    ? s->set_metaheader(FLIP_FLOW, true)   : s->set_metaheader(FLIP_FLOW , false);
    i++;
    
//    std::cout << std::hex << std::bitset<8> (*(message+0)) << " " ;
//    std::cout << std::hex << std::bitset<8> (*(message+1)) << " \n" ;
//    std::cout << "cont1: " << (message[0] & (FLIP_CONT1 >> 16)) << " \n";
//
//    if(message[0] & (FLIP_CONT1 >> 16)){
//        std::cout << "true cout1\n";
//    } else {
//        std::cout << "false cout1\n";
//    }
    
    if (s->get_metaheader(FLIP_CONT1) == false){
        //std::cout << "byte1 exit ";
        return i;
    }
    
    (message[i] & (FLIP_CONT2 >> 8))    ? s->set_metaheader(FLIP_CONT2, true)   : s->set_metaheader(FLIP_CONT2 , false);
    (message[i] & (FLIP_SOURCE_4 >> 8)) ? s->set_metaheader(FLIP_SOURCE_4, true): s->set_metaheader(FLIP_SOURCE_4 , false);
    (message[i] & (FLIP_SOURCE_1 >> 8)) ? s->set_metaheader(FLIP_SOURCE_1, true): s->set_metaheader(FLIP_SOURCE_1 , false);
    (message[i] & (FLIP_LENGTH >> 8))   ? s->set_metaheader(FLIP_LENGTH, true)  : s->set_metaheader(FLIP_LENGTH , false);
    (message[i] & (FLIP_CHECKSUM >> 8)) ? s->set_metaheader(FLIP_CHECKSUM, true): s->set_metaheader(FLIP_CHECKSUM , false);
    (message[i] & (FLIP_NOFRAG >> 8))   ? s->set_metaheader(FLIP_NOFRAG, true)  : s->set_metaheader(FLIP_NOFRAG , false);
    (message[i] & (FLIP_OPT1 >> 8))     ? s->set_metaheader(FLIP_OPT1, true)    : s->set_metaheader(FLIP_OPT1 , false);
    (message[i] & (FLIP_OPT2 >> 8))     ? s->set_metaheader(FLIP_OPT2, true)    : s->set_metaheader(FLIP_OPT2 , false);
    i++;
    
    if (s->get_metaheader(FLIP_CONT2) == false){
        //std::cout << "byte2 exit ";
        return i;
    }
    
    (message[i] & FLIP_CONT3 )      ? s->set_metaheader(FLIP_CONT3, true)     : s->set_metaheader(FLIP_CONT3 , false);
    (message[i] & FLIP_FRAGOFFSET ) ? s->set_metaheader(FLIP_FRAGOFFSET, true): s->set_metaheader(FLIP_FRAGOFFSET , false);
    (message[i] & FLIP_LASTFRAG )   ? s->set_metaheader(FLIP_LASTFRAG, true)  : s->set_metaheader(FLIP_LASTFRAG , false);
    (message[i] & FLIP_OPT3 )       ? s->set_metaheader(FLIP_OPT3, true)      : s->set_metaheader(FLIP_OPT3 , false);
    (message[i] & FLIP_OPT4 )       ? s->set_metaheader(FLIP_OPT4, true)      : s->set_metaheader(FLIP_OPT4 , false);
    (message[i] & FLIP_OPT5 )       ? s->set_metaheader(FLIP_OPT5, true)      : s->set_metaheader(FLIP_OPT5 , false);
    (message[i] & FLIP_OPT6 )       ? s->set_metaheader(FLIP_OPT6, true)      : s->set_metaheader(FLIP_OPT6 , false);
    (message[i] & FLIP_OPT7 )       ? s->set_metaheader(FLIP_OPT7, true)      : s->set_metaheader(FLIP_OPT7 , false);
    i++;
    
    if (s->get_metaheader(FLIP_CONT3) == false){
        //std::cout << "byte3 exit ";
        return i;
    }
    //if gets here -> error : not implemented yet
    return -1;
}

int SocketHandler::parse_flip_metafields(FlipSocket *s, uint8_t *message, int m_size, int index)
{
    int i = index;
    uint32_t byte4_t;
    
    s->clear_metafields();
    
    if (s->get_metaheader(FLIP_VERSION)) {
        s->set_version(message[i]);
        i++;
    }
    
    if (s->get_metaheader(FLIP_DEST_16)) {
        //implementation pending
        
    } else if (s->get_metaheader(FLIP_DEST_4)) {
        byte4_t = 0;
        byte4_t = message[i] << 24;
        i++;
        byte4_t = byte4_t | (message[i] << 16);
        i++;
        byte4_t = byte4_t | (message[i] << 8);
        i++;
        byte4_t = byte4_t | message[i];
        i++;
        
        s->set_dest(byte4_t);

    } else if (s->get_metaheader(FLIP_DEST_1)) {
        s->set_dest(message[i]);
        i++;
    }
    
    if (s->get_metaheader(FLIP_TYPE)) {
        s->set_type(message[i]);
        i++;
    }
    
    if (s->get_metaheader(FLIP_TTL)) {
        s->set_ttl(message[i]);
        i++;
    }
    
    if (s->get_metaheader(FLIP_FLOW)) {
        byte4_t = 0;
        byte4_t = message[i] << 24;
        i++;
        byte4_t = byte4_t | (message[i] << 16);
        i++;
        byte4_t = byte4_t | (message[i] << 8);
        i++;
        byte4_t = byte4_t | message[i];
        i++;
        
        s->set_flow(byte4_t);
    }
    
    if (s->get_metaheader(FLIP_SOURCE_16)) {
        //implementation pending
        
    } else if (s->get_metaheader(FLIP_SOURCE_4)) {
        byte4_t = 0;
        byte4_t = message[i] << 24;
        i++;
        byte4_t = byte4_t | (message[i] << 16);
        i++;
        byte4_t = byte4_t | (message[i] << 8);
        i++;
        byte4_t = byte4_t | message[i];
        i++;
        
        s->set_src(byte4_t);
        
    } else if (s->get_metaheader(FLIP_SOURCE_1)) {
        s->set_src(message[i]);
        i++;
    }
    
    if (s->get_metaheader(FLIP_LENGTH)) {
        byte4_t = 0;
        byte4_t = (message[i] << 8);
        i++;
        byte4_t = byte4_t | message[i];
        i++;
        
        s->set_len(byte4_t);
    }
    
    if (s->get_metaheader(FLIP_CHECKSUM)) {
        byte4_t = 0;
        byte4_t = (message[i] << 8);
        i++;
        byte4_t = byte4_t | message[i];
        i++;
        
        s->set_checksum(byte4_t);
    }
    
    if (s->get_metaheader(FLIP_FRAGOFFSET)) {
        byte4_t = 0;
        byte4_t = (message[i] << 8);
        i++;
        byte4_t = byte4_t | message[i];
        i++;
        
        s->set_offset(byte4_t);
    }
    
    //return index pointing to buffer next byte (start of upper layer msg)
    if (index == i)
        return index;
    else
        return i - 1;
}

/* TEST/PRINT FUNCTIONS */
void print_metaheader(FlipSocket s)
{
    std::cout << "cont1: " << s.get_metaheader(FLIP_CONT1) ;
    std::cout << "\nesp: " << s.get_metaheader(FLIP_ESP);
    std::cout << "\nver: " << s.get_metaheader(FLIP_VERSION);
    std::cout << "\ndest1: " << s.get_metaheader(FLIP_DEST_4);
    std::cout << "\ndest2: " << s.get_metaheader(FLIP_DEST_1);
    std::cout << "\ntype: " << s.get_metaheader(FLIP_TYPE);
    std::cout << "\nttl: " << s.get_metaheader(FLIP_TTL);
    std::cout << "\nflow: " << s.get_metaheader(FLIP_FLOW);
    std::cout << "\ncont2: " << s.get_metaheader(FLIP_CONT2);
    std::cout << "\nsource1: " << s.get_metaheader(FLIP_SOURCE_4);
    std::cout << "\nsource2: " << s.get_metaheader(FLIP_SOURCE_1);
    std::cout << "\nlength: " << s.get_metaheader(FLIP_LENGTH);
    std::cout << "\nchecksum: " << s.get_metaheader(FLIP_CHECKSUM);
    std::cout << "\nno_frag: " << s.get_metaheader(FLIP_NOFRAG);
    std::cout << "\nopt1: " << s.get_metaheader(FLIP_OPT1);
    std::cout << "\nopt2: " << s.get_metaheader(FLIP_OPT2);
    std::cout << "\ncont3: " << s.get_metaheader(FLIP_CONT3);
    std::cout << "\nfrag_offset: " << s.get_metaheader(FLIP_FRAGOFFSET);
    std::cout << "\nlast-frag: " << s.get_metaheader(FLIP_LASTFRAG);
    std::cout << "\nopt3: " << s.get_metaheader(FLIP_OPT3);
    std::cout << "\nopt4: " << s.get_metaheader(FLIP_OPT4);
    std::cout << "\nopt5: " << s.get_metaheader(FLIP_OPT5);
    std::cout << "\nopt6: " << s.get_metaheader(FLIP_OPT6);
    std::cout << "\nopt7: " << s.get_metaheader(FLIP_OPT7);
    std::cout << "\n";
}

void print_metafields(FlipSocket s)
{
    std::cout << std::dec << "Ver: " <<   (int) s.get_version();
    std::cout << std::dec << "\nDest:" << (int) s.get_dest();
    std::cout << std::dec << "\nType:" << (int) s.get_type();
    std::cout << std::dec << "\nTTL:" <<  (int) s.get_ttl();
    std::cout << std::dec << "\nFlow:" << (int) s.get_flow();
    std::cout << std::dec << "\nSrc:" <<  (int) s.get_src();
    std::cout << std::dec << "\nLen:" <<  (int) s.get_len();
    std::cout << std::dec << "\nCRC:" <<  (int) s.get_checksum();
    std::cout << std::dec << "\nOffset:" << (int) s.get_offset();
    std::cout << "\n";
}

void print_gtp_metaheader(GTPsocket g)
{
    std::cout << "\ncont1: " << g.get_metabit(GTP_CONT1);
    std::cout << "\nflags: " << g.get_metabit(GTP_FLAGS);
    std::cout << "\nsrc: " << g.get_metabit(GTP_SOURCE);
    std::cout << "\ndest: " << g.get_metabit(GTP_DEST);
    std::cout << "\nseq#: " << g.get_metabit(GTP_SEQ);
    std::cout << "\nack: " << g.get_metabit(GTP_ACK);
    std::cout << "\ntstmp: " << g.get_metabit(GTP_TIMESTAMP);
    std::cout << "\nchksum: " << g.get_metabit(GTP_CHECKSUM);
    std::cout << "\ncont2: " << g.get_metabit(GTP_CONT2);
    std::cout << "\nwsize: " << g.get_metabit(GTP_W_SIZE);
    std::cout << "\nurgent: " << g.get_metabit(GTP_URGENT);
    std::cout << "\nlen: " << g.get_metabit(GTP_LENGTH);
    std::cout << "\nnextp: " << g.get_metabit(GTP_NEXTPROTO);
}

void print_gtp_metafields(GTPsocket g)
{
    std::cout << std::dec << "\nflags: " <<   (int) g.get_flags() ;
    std::cout << std::dec << "\nsrc: " <<   (int) g.get_src() ;
    std::cout << std::dec << "\ndest: " <<   (int) g.get_dest() ;
    std::cout << std::dec << "\nseq: " <<   (int) g.get_seq() ;
    std::cout << std::dec << "\nack: " <<   (int) g.get_ack() ;
    std::cout << std::dec << "\ntstamp: " <<   (int) g.get_tstamp() ;
    std::cout << std::dec << "\nchecksum: " <<   (int) g.get_checksum() ;
    std::cout << std::dec << "\nwsize: " <<   (int) g.get_wsize() ;
    std::cout << std::dec << "\nurgent: " <<   (int) g.get_urgent() ;
    std::cout << std::dec << "\nlen: " <<   (int) g.get_len() ;
    std::cout << std::dec << "\nnextp: " <<   (int) g.get_nextp() ;
}
