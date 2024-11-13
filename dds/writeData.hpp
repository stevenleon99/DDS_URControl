#pragma once

#include <fstream>
#include <sstream>

#include <dds/pub/ddspub.hpp>
#include <dds/core/Time.hpp>
#include <rti/util/util.hpp>  // for sleep()
#include <rti/config/Logger.hpp>  // for logging

static const DDS_UnsignedLong USEC_to_NANOSEC = 1000UL;
static const DDS_UnsignedLong SEC_to_NANOSEC = 1000000000UL;
static const DDS_UnsignedLong SEC_to_USEC = 1000000UL;

int writeFile(std::string msg, std::string filename) {
    std::ofstream myfile;
    myfile.open (filename, std::ios::app);
    myfile << msg;
    myfile.close();
    return 0;
}

inline timeval getTime() {
    struct timeval tv;

    // Check if gettimeofday is successful
    if (gettimeofday(&tv, NULL) != 0) {
        // Return a zero time if gettimeofday fails (can also use DDS_TIME_ZERO if defined)
        tv.tv_sec=0; tv.tv_usec=0;
        return tv;
    }

    return tv;
}