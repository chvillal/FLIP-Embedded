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

int main(int argc, const char * argv[]) {
    
    FlipSocket mysocket;

    //print_metaheader(mysocket);
    std::cout << "\n\n";
    mysocket.set_metaheader(FLIP_ESP, true);
    mysocket.set_metaheader(FLIP_VERSION, true);
    mysocket.set_metaheader(FLIP_DEST_1, true);
    mysocket.set_metaheader(FLIP_TYPE, true);
    mysocket.set_metaheader(FLIP_TTL, true);
    mysocket.set_metaheader(FLIP_FLOW, true );
//    mysocket.set_metaheader(FLIP_SOURCE_1, true );
//    mysocket.set_metaheader(FLIP_LENGTH, true );
//    mysocket.set_metaheader(FLIP_CHECKSUM, true );
//    mysocket.set_metaheader(FLIP_NOFRAG, true );
//    mysocket.set_metaheader(FLIP_LASTFRAG, true );
    
    mysocket.set_version(0);
    mysocket.set_dest(128);
    mysocket.set_type(4);
    mysocket.set_ttl(3);
    mysocket.set_flow(65535);
    mysocket.set_src(48);
    mysocket.set_len(16);
    mysocket.set_checksum(234);
    mysocket.set_offset(45);

    //print_metafields(mysocket);
    //print_metaheader(mysocket);
    std::cout << "\n";
    
    mysocket.set_cont_bits();
    
    print_metaheader(mysocket);
    std::cout << "\n";

    uint8_t *a;
    a = get_flip_metaheader(mysocket);
    std::cout << std::hex << (int) *a << " " << (int) *(a+1) << " " <<  (int) *(a+2) << std::endl;
    std::cout << std::string((char*) a) << std::string((char*) a+1) << std::string((char*) a+2) << std::endl;
    std::cout << std::bitset<8> (*a) << " " << std::bitset<8> (*(a+1)) << " " << std::bitset<8> (*(a+2))<<  std::endl;

    std::cout << "\n";
    //print_metaheader(mysocket);
    std::cout << "\n";
    
    
    
//    //TEST bitwise operations and bitmap builder
//    int x = 0x400000;
//    uint8_t y[4]{};
//    std::cout << std::dec << x << std::endl;
//    std::cout << std::hex << x << std::endl;
//
//    y[0] = y[0] | (x >> 16);
//
//    std::cout << std::dec << (int) y[0] << std::endl;
//    std::cout << std::hex << (int) y[0] << std::endl;
//
//    char *a;
//
//    a = (char *) y;
//
//    std::cout << std::dec << (int) *a << std::endl;
//    std::cout << std::hex << (int) *a << std::endl;
    
    
    return 0;
}
