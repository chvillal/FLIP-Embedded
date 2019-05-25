//
//  main.cpp
//  Unit Testing for eFLIP
//
//  Created by Christopher Villalpando on 5/5/19.
//  Copyright © 2019 Christopher Villalpando. All rights reserved.
//

#include <iostream>
#include <string.h>
#include <bitset>
#include "eflip.h"

void test_metaheader(void);
void test_metafields(void);
void test_buildandparse(void);
void test_gtpsockets(void);
void test_full_packetbuilder(void);
void test_str(void);
    
int main(int argc, const char * argv[]) {
    
    //test_metaheader();
    //test_metafields();
    //test_buildandparse();
    //test_gtpsockets();
    //test_full_packetbuilder();
    test_str();
    
    return 0;
}

void test_metaheader(void)
{
    FlipSocket mysocket;
    SocketHandler handler;
    
    //print_metaheader(mysocket);
    std::cout << "\n\n";
    mysocket.set_metabit(FLIP_ESP, true);
    mysocket.set_metabit(FLIP_VERSION, true);
    mysocket.set_metabit(FLIP_DEST_1, true);
    mysocket.set_metabit(FLIP_TYPE, true);
    mysocket.set_metabit(FLIP_TTL, true);
    mysocket.set_metabit(FLIP_FLOW, true );
    mysocket.set_metabit(FLIP_SOURCE_1, true );
    mysocket.set_metabit(FLIP_LENGTH, true );
    mysocket.set_metabit(FLIP_CHECKSUM, true );
    mysocket.set_metabit(FLIP_NOFRAG, true );
    mysocket.set_metabit(FLIP_LASTFRAG, true );

    uint8_t *a;
    handler.build_flip_metaheader(mysocket);
    a = handler.get_flip_bitmap();
    
    int max = handler.get_flip_bitmapsize(); 
    
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
    
//    mysocket.set_metabit(FLIP_ESP, false);
    mysocket.set_metabit(FLIP_VERSION, true);
    mysocket.set_metabit(FLIP_DEST_1, true);
    mysocket.set_metabit(FLIP_TYPE, true);
    mysocket.set_metabit(FLIP_TTL, true);
    mysocket.set_metabit(FLIP_FLOW, true );
    mysocket.set_metabit(FLIP_SOURCE_1, true );
    mysocket.set_metabit(FLIP_LENGTH, true );
    mysocket.set_metabit(FLIP_CHECKSUM, true );
//    mysocket.set_metabit(FLIP_NOFRAG, true );
    mysocket.set_metabit(FLIP_LASTFRAG, true );
    
    mysocket.set_version(1);
    mysocket.set_dest(128);
    mysocket.set_type(4);
    mysocket.set_ttl(3);
    mysocket.set_flow(1024);
    mysocket.set_src(48);
    mysocket.set_len(16);
    mysocket.set_checksum(234);
    mysocket.set_offset(45);

    uint8_t *m;
    handler.build_flip_metafields(mysocket);
    m = handler.get_flip_metafields();
    int max = handler.get_flip_fieldssize();
    
    std::cout << "max= " << max << std::endl;
    
    for (int i=0; i<=max; i++ ){
        std::cout << std::hex << (int) *(m+i) << " ";
    }
    std::cout << "\n";
    
    for (int i=0; i<=max; i++ ){
        std::cout << std::bitset<8> (*(m+i)) << " " ;
    }
    
    std::cout << "\n";
}

void test_buildandparse(){
    FlipSocket s_socket;
    SocketHandler s_handler;
    uint8_t *bitmap;
    uint8_t *fields;
    int b_size;
    int f_size;
    
    //cnfigure flip socket
    //s_socket.set_metabit(FLIP_ESP, true);
    s_socket.set_metabit(FLIP_VERSION, true);
    s_socket.set_metabit(FLIP_DEST_4, true);
    s_socket.set_metabit(FLIP_TYPE, true);
    s_socket.set_metabit(FLIP_TTL, true);
    s_socket.set_metabit(FLIP_FLOW, true );
    s_socket.set_metabit(FLIP_SOURCE_4, true );
    s_socket.set_metabit(FLIP_LENGTH, true );
    s_socket.set_metabit(FLIP_CHECKSUM, true );
    s_socket.set_metabit(FLIP_NOFRAG, true );
    s_socket.set_metabit(FLIP_LASTFRAG, true );
    s_socket.set_metabit(FLIP_FRAGOFFSET, true);
    
    s_socket.set_version(255);
    s_socket.set_dest(65535);
    s_socket.set_type(255);
    s_socket.set_ttl(255);
    s_socket.set_flow(65535);
    s_socket.set_src(65535);
    s_socket.set_len(65535);
    s_socket.set_checksum(65535);
    s_socket.set_offset(65535);
    
    //build flip bitmap
    s_handler.build_flip_metaheader(s_socket);
    bitmap = s_handler.get_flip_bitmap();
    b_size = s_handler.get_flip_bitmapsize();
    s_socket.set_cont_bits();
    
    std::cout << "bitmap-size= " << b_size << std::endl;
    for (int i=0; i<b_size; i++ ){
        std::cout << std::hex << (int) *(bitmap+i) << " ";
    }
    std::cout << "\n";
    for (int i=0; i<b_size; i++ ){
        std::cout << std::bitset<8> (*(bitmap+i)) << " " ;
    }
    std::cout << "\n";
    std::cout << "\n";
    
    //build metafields
    s_handler.build_flip_metafields(s_socket);
    fields = s_handler.get_flip_metafields();
    f_size = s_handler.get_flip_fieldssize();
    
    std::cout << "fields-size= " << f_size << std::endl;
    for (int i=0; i<=f_size; i++ ){
        std::cout << std::hex << (int) *(fields+i) << " ";
    }
    std::cout << "\n";
    for (int i=0; i<=f_size; i++ ){
        std::cout << std::bitset<8> (*(fields+i)) << " " ;
    }
    std::cout << "\n";
    std::cout << "\n";
    
    // FLIP Packet bitmap+fields fully created. Parsed them below.
    FlipSocket r_socket;
    SocketHandler r_handler;
    
    //read/extract bitmap and store in struct
    r_handler.parse_flip_metaheader(&r_socket, bitmap, b_size);
    print_metaheader(r_socket);
    std::cout << "\n";
    std::cout << "\n";
    
    //extract metafields based on bitmap
    r_handler.parse_flip_metafields(&r_socket, fields, f_size, 0);
    print_metafields(r_socket);
    std::cout << "\n";
    std::cout << "\n";
}

void test_gtpsockets(){
    GTPsocket g_socket;
    SocketHandler handler;
    uint8_t *bitmap;
    uint8_t *fields;
    int size;
    
    g_socket.set_metabit(GTP_FLAGS, true);
    g_socket.set_metabit(GTP_SOURCE, true);
    g_socket.set_metabit(GTP_DEST, true);
    g_socket.set_metabit(GTP_SEQ, true);
    g_socket.set_metabit(GTP_ACK, true);
    g_socket.set_metabit(GTP_TIMESTAMP, true);
    g_socket.set_metabit(GTP_CHECKSUM, true);
    g_socket.set_metabit(GTP_W_SIZE, true);
    g_socket.set_metabit(GTP_URGENT, true);
    g_socket.set_metabit(GTP_LENGTH, true);
    g_socket.set_metabit(GTP_NEXTPROTO, true);
    
    g_socket.set_flags(12);
    g_socket.set_src(250);
    g_socket.set_dest(234);
    g_socket.set_seq(1234);
    g_socket.set_ack(53);
    g_socket.set_tstamp(92983);
    g_socket.set_checksum(54089);
    g_socket.set_wsize(1024);
    g_socket.set_urgent(2048);
    g_socket.set_len(234);
    g_socket.set_nextp(4);
    
    g_socket.set_cont_bits();
    
    print_gtp_metaheader(g_socket);
    std::cout << std::endl;
    std::cout << std::endl;
    
    handler.build_gtp_metaheader(g_socket);
    bitmap = handler.get_gtp_bitmap();
    size = handler.get_gtp_bitmapsize();
    
    std::cout << "bitmapSize= " << size << std::endl;
    for (int i=0; i < size; i++ ){
        std::cout << std::hex << (int) *(bitmap+i) << " ";
    }
    std::cout << "\n";
    for (int i=0; i < size; i++ ){
        std::cout << std::bitset<8> (*(bitmap+i)) << " " ;
    }
    std::cout << std::endl;
    std::cout << std::endl;
    
    //GTPsocket rcv_s;
    SocketHandler rcv_h;
    
    rcv_h.parse_gtp_metaheader(&rcv_h.gtp_s, bitmap, size);
    print_gtp_metaheader(rcv_h.gtp_s);
    std::cout << std::endl;
    std::cout << std::endl;
    
    //build metafields
    handler.build_gtp_metafields(g_socket);
    fields = handler.get_gtp_metafields();
    size = handler.get_gtp_fieldsize();
    
    print_gtp_metafields(g_socket);
    std::cout << std::endl;
    std::cout << std::endl;
    
    std::cout << "fields-size= " << size << std::endl;
    for (int i=0; i<=size; i++ ){
        std::cout << std::hex << (int) *(fields+i) << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;
    for (int i=0; i<=size; i++ ){
        std::cout << std::bitset<8> (*(fields+i)) << " " ;
    }
    std::cout << std::endl;
    std::cout << std::endl;
    
    rcv_h.parse_gtp_metafields(&rcv_h.gtp_s, fields, size, 0);
    print_gtp_metafields(rcv_h.gtp_s);
    std::cout << std::endl;
    std::cout << std::endl;
    
    //test sizes
    std::cout << "GTPsize =" << sizeof(rcv_h.gtp_s) << "\n";
    std::cout << "FLIPsize =" << sizeof(rcv_h.flip_s) << "\n";
    std::cout << "Handersize =" << sizeof(rcv_h) << "\n";
    std::cout << std::endl;
    std::cout << std::endl;
}

void test_full_packetbuilder(void){
    
    FlipKernel network;
    char buf[] = "Hello World!";
    int s;
    
    s = network.socket();
    network.setsocketopt(s, SOCK_TYPE_FLIP, FLIP_VERSION, 1);
    network.setsocketopt(s, SOCK_TYPE_FLIP, FLIP_DEST_1, 224);
    network.setsocketopt(s, SOCK_TYPE_FLIP, FLIP_TTL, 4);
    network.setsocketopt(s, SOCK_TYPE_FLIP, FLIP_SOURCE_1, 64);
    
    network.write(s, buf, (int) strlen(buf));
    
    network.kernel();
}

void test_str(void){
    char *buf = "EVENT-ENDED";
    int i = (int) strlen(buf);
    
    std::cout << "size:" << i << std::endl;
}
