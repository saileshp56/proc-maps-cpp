#include "../include/proc_maps/ProcessMap.hpp"


ProcessMap::ProcessMap(pid_t pid) : pid(pid) {
}

std::vector<MapRange> ProcessMap::get_process_maps() {
    #ifdef __linux__
        return get_process_maps_linux();
    #else
        throw std::runtime_error("Unsupported operating system.");
    #endif
}

vector<MapRange> ProcessMap::get_process_maps_linux() {
    vector<MapRange> mappings;
    ifstream maps_file("/proc/" + std::to_string(pid) + "/maps");


    if (!maps_file.is_open()) {
        std::cerr << "Failed to open /proc/" << pid << "/maps" << std::endl;
        return mappings;
    }

    string line;
    while (std::getline(maps_file, line)) {
        std::istringstream iss(line);
        string range_str;
        iss >> range_str;
        
        // Step 1: Parse address range
        size_t hyphen_pos = range_str.find('-');
        
        string start_str = range_str.substr(0, hyphen_pos);
        string end_str = range_str.substr(hyphen_pos + 1);
        
        size_t range_start, range_end;
        try {
            range_start = static_cast<size_t>(std::stoull(start_str, nullptr, 16));
            range_end = static_cast<size_t>(std::stoull(end_str, nullptr, 16));
            // M

        } catch (const std::exception&) {
            continue; // Skip invalid entries
        }
        
        // Step 2: Parse permissions
        string flags;
        iss >> flags;
        
        
        // Step 3: Parse offset, dev, inode
        string offset_str, dev, inode_str;
        iss >> offset_str >> dev >> inode_str;
        
        size_t offset, inode;
        try {
            offset = std::stoull(offset_str, nullptr, 16);
            inode = std::stoull(inode_str, nullptr, 10);
        } catch (const std::exception&) {
            continue; // Skip invalid entries
        }

        // Step 4: Create filesystem::path object

        // Parse pathname (rest of the line)
        string pathname_str;
        getline(iss, pathname_str);
        
        // Trim leading whitespace
        size_t first_non_space = pathname_str.find_first_not_of(" \t");


        std::experimental::filesystem::path pathname;
        if (first_non_space != std::string::npos) {
            pathname_str = pathname_str.substr(first_non_space);
            pathname = std::experimental::filesystem::path(pathname_str);
        }
        MapRange mapping = MapRange(range_start, range_end, offset, dev, flags, inode, pathname);
        mappings.push_back(mapping);
    }

    maps_file.close();
    return mappings;


}
