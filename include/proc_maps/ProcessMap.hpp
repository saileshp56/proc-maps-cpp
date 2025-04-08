#ifndef PROCESSMAP_H
#define PROCESSMAP_H

#include <vector>
#include <string>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "MapRange.hpp"

using namespace std;

class ProcessMap {
    public:
        ProcessMap(pid_t = getpid());
    
        vector<MapRange> get_process_maps();
    

    private:
        vector<MapRange> get_process_maps_linux();
        pid_t pid;
};


#endif