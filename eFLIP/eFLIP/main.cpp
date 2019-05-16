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
    
    print_metaheader(mysocket);
    std::cout << "\n\n";
    print_metafields(mysocket);
    std::cout << "\n\n";
    //mysocket.clear_metafields();
    //print_metafields(mysocket);
    
    
    return 0;
}
