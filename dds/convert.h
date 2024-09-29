// convert the dds datatype to matlab datatype
#include "URController.hpp"
#include "../Matlab_URController/URController.h"


int DDSin_to_Matlabin(URController &Min, DesireJoint Din) {
    auto ori_theta_arr = Din.oriThetaArr();
    auto desired_pos_arr = Din.desiredPosArr();
    for (auto i=0; i<6; i++) {
        Min.rtU.ori_theta_arr[i] = static_cast<real_T>(ori_theta_arr[i]);
        Min.rtU.desire_pos_orient_arr[i] = static_cast<real_T>(desired_pos_arr[i]);
    }
    return 1;
}
