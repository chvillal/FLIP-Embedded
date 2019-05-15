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
#include <stdint.h>


/* DEFINES */
#define FLIP_CONT_1         -1
#define FLIP_CONT_2         -2
#define FLIP_CONT_3         -3

#define BITMASK_DST_SIZE_2      0x08
#define BITMASK_DST_SIZE_4      0x10
#define BITMASK_DST_SIZE_16     0x18
#define BITMASK_VER             0x20
#define BITMASK_SRC_SIZE_2      0x20
#define BITMASK_SRC_SIZE_4      0x40
#define BITMASK_SRC_SIZE_16     0x60
#define BITMASK_LEN             0x04
#define BITMASK_TTL             0x02
#define BITMASK_FLOW            0x01
#define BITMASK_PROTOCOL        0x10
#define BITMASK_CRC             0x08
#define BITMASK_ESP             0x40
#define BITMASK_CONT            0x80
#define BITMAP_MAXLEN          2
#define MAX_STR_SIZE            128 //temporary, not sure what max lora string len is...

//uint8_t  version;
//uint32_t dest;
//uint8_t  type;
//uint8_t  ttl;
//uint32_t flow;
//uint32_t source;
//uint16_t length;    //dynamic
//uint16_t checksum;  //dynamic
//uint16_t offset;

/* CLASS FUNCTIONS */
void FlipSocket::set_version(uint8_t ver)
{
    m_metafields.version = ver;
}

void FlipSocket::set_dest(uint32_t dest)
{
    m_metafields.dest = dest;
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

void FlipSocket::set_src(uint32_t src)
{
    m_metafields.source = src;
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


void set_field()
{
    
}
int  get_field()
{
    return 0;
}


void set_bitmap()
{
    
}
void set_bitfield()
{
    
}
int get_bitmap()
{
    return 0;
}
int get_bitfield()
{
    return 0;
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

/* HELPER FUNCTIONS */


/* TEST FUNCTIONS */
