#ifndef D435SENSOR_H
#define D435SENSOR_H

#include "RGBDSensor.h"
#include <librealsense2/rs.hpp>
#include <opencv2/opencv.hpp>

class D435Sensor : public RGBDSensor
{
public:
	D435Sensor();

	~D435Sensor();

	bool init();

	void run();

private:
	// RealSense
    rs2::pipeline pipeline;
    rs2::pipeline_profile pipeline_profile;
    rs2::frameset aligned_frameset;

    // Color Buffer
    rs2::frame color_frame;
    cv::Mat color_mat;
    uint32_t color_width = 640;
    uint32_t color_height = 480;
    uint32_t color_fps = 60;

    // Depth Buffer
    rs2::frame depth_frame;
    cv::Mat depth_mat;
    uint32_t depth_width = 640;
    uint32_t depth_height = 480;
    uint32_t depth_fps = 60;
};


#endif