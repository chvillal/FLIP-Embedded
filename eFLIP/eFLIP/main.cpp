//
//  main.cpp
//  Unit Testing for eFLIP
//
//  Created by Christopher Villalpando on 5/5/19.
//  Copyright © 2019 Christopher Villalpando. All rights reserved.
//

#include <iostream>
#include "eflip.h"

int main(int argc, const char * argv[]) {
    
//    //determine size of dataypes in my machine
//    std::cout << "bool:\t\t" << sizeof(bool) << "byes\n";
//    std::cout << "char:\t\t" << sizeof(char) << "byes\n";
//    std::cout << "int:\t\t" << sizeof(int) << "byes\n";
//    std::cout << "long:\t\t" << sizeof(long) << "byes\n";
//    std::cout << "float:\t\t" << sizeof(float) << "byes\n";
//    std::cout << "double:\t\t" << sizeof(double) << "byes\n";
    
//    meta_header metaHdr;
//    flip_header flipHdr;
//
//    metaHdr.continuation1 = true;
//    metaHdr.version = true;
//    metaHdr.destination1 = true;
//    metaHdr.source2 = true;
//    metaHdr.flow = true;
//    metaHdr.protocol = true;
//    metaHdr.checksum = true;
//
//    flipHdr.version = 10;
//    flipHdr.destination_addr = 65535;
//    flipHdr.source_addr = 255;
//    flipHdr.protocol = 4;
//    flipHdr.checksum = 8;
//    flipHdr.flow = 1234568;
//
//    char *bitmaps = FLIP_construct_bitmap();
//    printf("returned string is: %s\n\n", bitmaps);
//
//    FLIP_construct_header();
    
//    char *packet = "THIS IS A PACKET WOOOOO";
//    char *bitmap = "10001100";
//
//    uint32_t length = 255;
//
//    uint8_t array[5] = {0, 0, 0, 0, 0};
//
//    char str[10];
//
//    array[0] = *((uint8_t *)&length + 3);
//    array[1] = *((uint8_t *)&length + 2);
//    array[2] = *((uint8_t *)&length + 1);
//    array[3] = *((uint8_t *)&length);
//
//    printf("array elems are: %u %u %u %u\n", array[0], array[1], array[2], array[3]);
//
//    memcpy(str, array, 5);
//    printf("string is: %s}\n", str);
//
//    uint8_t byte1 = (uint8_t) str[0];
//    uint8_t byte2 = (uint8_t) str[1];
//    uint8_t byte3 = (uint8_t) str[2];
//    uint8_t byte4 = (uint8_t) str[3];
//
//    printf("%u %u %u %u\n", str[0], str[1], str[2], str[3]);
//    //printf("%u %u %u %u\n", byte1, byte2, byte3, byte4);
//
//    uint32_t b1 = str[0] <<  24 | str[1] << 16 | str[2] << 8 | (uint8_t) str[3];
//    printf("OG unsigned value: %u\n", b1);
    
    FlipSocket mysocket;
    
    mysocket.set_version(0);
    mysocket.set_dest(128);
    mysocket.set_type(4);
    mysocket.set_ttl(3);
    mysocket.set_flow(65535);
    mysocket.set_src(48);
    mysocket.set_len(16);
    mysocket.set_checksum(234);
    mysocket.set_offset(45);
    
    std::cout << "Ver: " <<  mysocket.get_version();
    std::cout << "\nDest:" << mysocket.get_dest();
    std::cout << "\nType:" <<  mysocket.get_type();
    std::cout << "\nTTL:" << mysocket.get_ttl();
    std::cout << "\nFlow:" << mysocket.get_flow();
    std::cout << "\nSrc:" << mysocket.get_src();
    std::cout << "\nLen:" << mysocket.get_len();
    std::cout << "\nCRC:" << mysocket.get_checksum();
    std::cout << "\nOffset:" << mysocket.get_offset();
    std::cout << "\n";
    
    return 0;
}
