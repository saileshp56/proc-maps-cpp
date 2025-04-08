#ifndef MAPRANGE_H
#define MAPRANGE_H

#include <string>
#include <unistd.h>
#include <experimental/filesystem>


using std::string;

struct MapRange {
public:
    MapRange() {
        this->offset = 0;
        this->dev = "";
        this->flags = "";
        this->inode = 0;

    }
    MapRange(size_t range_start, size_t range_end, size_t offset, const string& dev, const string& flags, size_t inode, std::experimental::filesystem::path pathname) {
        this->range_start = range_start;
        this->range_end = range_end;
        this->offset = offset;
        this->dev = dev;
        this->flags = flags;
        this->inode = inode;
        this->pathname = pathname;

    }

    std::experimental::filesystem::path* filename();
    bool is_exec() const;
    bool is_read() const;
    bool is_write() const;
    size_t size() const;
    // Returns the byte number in base 10
    size_t start() const;


    size_t offset;
    string dev;
    string flags;
    size_t inode;

private:
    size_t range_start;
    size_t range_end;
    std::experimental::filesystem::path pathname;

    
    
};

#endif
