#include "../include/proc_maps/MapRange.hpp"

std::experimental::filesystem::path* MapRange::filename() {
    return &pathname;
}
bool MapRange::is_exec() const {
     return (flags[2] != '-');
}
bool MapRange::is_read() const {
    return (flags[0] != '-');
}
bool MapRange::is_write() const {
    return (flags[1] != '-');
}
size_t MapRange::size() const {
    return range_end - range_start;
}
size_t MapRange::start() const {
    return range_start;
}
