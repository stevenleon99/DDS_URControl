// convert the dds datatype to matlab datatype
#include "URController.hpp"
#include "../Matlab_URController/URController.h"

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

#include <iostream>
#include <cstring>
#include <sstream>

using namespace boost::interprocess;

int DDSin_to_Matlabin(URController &Min, DesireJoint Din) {
    auto ori_theta_arr = Din.oriThetaArr();
    auto desired_pos_arr = Din.desiredPosArr();
    for (auto i=0; i<6; i++) {
        Min.rtU.ori_theta_arr[i] = static_cast<real_T>(ori_theta_arr[i]);
        Min.rtU.desire_pos_orient_arr[i] = static_cast<real_T>(desired_pos_arr[i]);
    }
    return 1;
}

void writeshmio(DesireJoint mem){
    shared_memory_object::remove("position");

    shared_memory_object shm(create_only, "position", read_write);
    shm.truncate(1024);
    mapped_region region(shm, read_write);

    auto vec = mem.desiredPosArr();
    std::ostringstream oss;

    for (size_t i = 0; i < vec.size(); ++i) {
        oss << vec[i];
        if (i != vec.size() - 1) {
            oss << ",";
        }
    }

    std::string result = oss.str();
    char message[result.size() + 1];
    std::strcpy(message, result.c_str());

    // Write data into the shared memory
    std::memcpy(region.get_address(), message, sizeof(message));

    std::cout << "Message written to shared memory: " << message << std::endl;
}
