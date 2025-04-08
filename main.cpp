#include <iostream>
#include <vector>
#include "include/proc_maps/ProcessMap.hpp"
#include "include/proc_maps/MapRange.hpp"

int main() {
    
    try {
        ProcessMap processMap;
        
        std::vector<MapRange> mappings = processMap.get_process_maps();
        
        std::cout << "Found " << mappings.size() << " memory mappings:" << std::endl;
        std::cout << "-------------------------------------------------" << std::endl;
        
        for (auto& mapping : mappings) {
            std::cout << "Address Range: byte " << mapping.start() << " - byte " << (mapping.start() + mapping.size()) << " (Size: " << std::dec << mapping.size() << " bytes)" << std::endl;
            
            std::cout << "Permissions: " 
                      << (mapping.is_read() ? "r" : "-")
                      << (mapping.is_write() ? "w" : "-")
                      << (mapping.is_exec() ? "x" : "-")
                      << std::endl;
            
            std::cout << "Offset: 0x" << std::hex << mapping.offset << std::endl;
            std::cout << "Device: " << mapping.dev << std::endl;
            std::cout << "Inode: " << std::dec << mapping.inode << std::endl;
            
            auto filename = mapping.filename();
            if (filename && !filename->empty()) {
                std::cout << "Path: " << filename->string() << std::endl;
            } else {
                std::cout << "Path: [anonymous]" << std::endl;
            }
            
            std::cout << "-------------------------------------------------" << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cerr << "An error occured: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}