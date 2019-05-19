//
//  main.cpp
//  Unit Testing for eFLIP
//
//  Created by Christopher Villalpando on 5/5/19.
//  Copyright © 2019 Christopher Villalpando. All rights reserved.
//

#include <iostream>
#include <bitset>
#include "eflip.h"

void test_metaheader(void);
void test_metafields(void);

int main(int argc, const char * argv[]) {
    
    test_metaheader();
    //test_metafields();
    
    return 0;
}

void test_metaheader(void)
{
    FlipSocket mysocket;
    SocketHandler handler;
    
    //print_metaheader(mysocket);
    std::cout << "\n\n";
    mysocket.set_metaheader(FLIP_ESP, true);
    mysocket.set_metaheader(FLIP_VERSION, true);
    mysocket.set_metaheader(FLIP_DEST_1, true);
    mysocket.set_metaheader(FLIP_TYPE, true);
    mysocket.set_metaheader(FLIP_TTL, true);
    mysocket.set_metaheader(FLIP_FLOW, true );
    mysocket.set_metaheader(FLIP_SOURCE_1, true );
    mysocket.set_metaheader(FLIP_LENGTH, true );
    mysocket.set_metaheader(FLIP_CHECKSUM, true );
    mysocket.set_metaheader(FLIP_NOFRAG, true );
    mysocket.set_metaheader(FLIP_LASTFRAG, true );

    uint8_t *a;
    handler.get_flip_metaheader(mysocket);
    a = handler.get_bitmap();
    
    int max = handler.get_bitmap_size();
    
    mysocket.set_cont_bits();
    std::cout << "max= " << max << std::endl;
    
    for (int i=0; i<max; i++ ){
        std::cout << std::hex << (int) *(a+i) << " ";
    }
    std::cout << "\n";
    
    for (int i=0; i<max; i++ ){
        std::cout << std::bitset<8> (*(a+i)) << " " ;
    }
    
    std::cout << "\n";
    std::cout << "\n";
    
    SocketHandler h_rcv;
    FlipSocket f_rcv;
    h_rcv.parse_flip_metaheader(&f_rcv, a, max);
    std::cout << "\n";
    print_metaheader(f_rcv);
}

void test_metafields(void)
{
    FlipSocket mysocket;
    SocketHandler handler;
    
//    mysocket.set_metaheader(FLIP_ESP, false);
    mysocket.set_metaheader(FLIP_VERSION, true);
    mysocket.set_metaheader(FLIP_DEST_1, true);
    mysocket.set_metaheader(FLIP_TYPE, true);
    mysocket.set_metaheader(FLIP_TTL, true);
    mysocket.set_metaheader(FLIP_FLOW, true );
    mysocket.set_metaheader(FLIP_SOURCE_1, true );
    mysocket.set_metaheader(FLIP_LENGTH, true );
    mysocket.set_metaheader(FLIP_CHECKSUM, true );
//    mysocket.set_metaheader(FLIP_NOFRAG, true );
//    mysocket.set_metaheader(FLIP_LASTFRAG, true );
    
        mysocket.set_version(1);
        mysocket.set_dest(128);
        mysocket.set_type(4);
        mysocket.set_ttl(3);
        mysocket.set_flow(1024);
        mysocket.set_src(48);
        mysocket.set_len(16);
        mysocket.set_checksum(234);
//        mysocket.set_offset(45);
    
//    uint8_t *a;
//    mysocket.set_cont_bits();
//    a = get_flip_metaheader(mysocket);

    uint8_t *m;
    handler.get_flip_metafields(mysocket);
    m = handler.get_metafields();
    int max = handler.get_fields_size();
    
    std::cout << "max= " << max << std::endl;
    
    for (int i=0; i<=max; i++ ){
        std::cout << std::hex << (int) *(m+i) << " ";
    }
    std::cout << "\n";
    
    for (int i=0; i<=max; i++ ){
        std::cout << std::bitset<8> (*(m+i)) << " " ;
    }
    
}
