#include "Arduino.h"
#include "IMU.h"

IMU::IMU() {
    bno = Adafruit_BNO055(55);
    bno.begin();
    bno.setExtCrystalUse(true);
}

std::tuple<std_msgs::Float32, std_msgs::Float32>  IMU::read_IMUmsg_data() {

    imu::Quaternion quat = bno.getQuat();
    std_msgs::Float32 quatw, quatz;
    quatw.data = (float) quat.w();
    quatz.data = (float) quat.z();
    return std::make_tuple(quatw, quatz);
}

void IMU::read_compass() {
    //sensor_msgs::Compass Compass_msg;
    imu::Vector<3> magnetometer = bno.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);

    float Pi = 3.14159;
    float magnetic_heading = (atan2(magnetometer.y(), magnetometer.x()) * 180) / Pi;

    if (magnetic_heading < 0) {
        magnetic_heading = 360 + magnetic_heading;
    }
}



