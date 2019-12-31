#include "D435.h"

D435Sensor::D435Sensor()
{
	init();
}

D435Sensor::~D435Sensor()
{
	pipeline.stop();
	cv::destroyAllWindows();
	
}


bool D435Sensor::init()
{
	rs2::config config;
    config.enable_stream( rs2_stream::RS2_STREAM_COLOR, color_width, color_height, rs2_format::RS2_FORMAT_BGR8, color_fps );
    config.enable_stream( rs2_stream::RS2_STREAM_DEPTH, depth_width, depth_height, rs2_format::RS2_FORMAT_Z16, depth_fps );

    // Start Pipeline
    pipeline_profile = pipeline.start( config );
}

void D435Sensor::run() 
{

	bool record = false;
	int m_frameIdx = 0;
	createRGBDFolders();

	while (true) 
	{
		rs2::frameset frameset = pipeline.wait_for_frames();

		// Retrieve Aligned Frame
		rs2::align align( rs2_stream::RS2_STREAM_COLOR );
		aligned_frameset = align.process( frameset );
		if( !aligned_frameset.size() ){
			return;
		}

		// Retrieve Color Frame
		color_frame = aligned_frameset.get_color_frame();

		// Retrive Frame Information
		color_width = color_frame.as<rs2::video_frame>().get_width();
		color_height = color_frame.as<rs2::video_frame>().get_height();

		// Retrieve Depth Frame
		depth_frame = aligned_frameset.get_depth_frame();

		// Retrive Frame Information
		depth_width = depth_frame.as<rs2::video_frame>().get_width();
		depth_height = depth_frame.as<rs2::video_frame>().get_height();
		
		color_mat = cv::Mat( color_height, color_width, CV_8UC3, const_cast<void*>( color_frame.get_data() ) );
		depth_mat = cv::Mat( depth_height, depth_width, CV_16SC1, const_cast<void*>( depth_frame.get_data() ) );

		
		if( (!color_mat.empty()) && (!depth_mat.empty()) ){
        	cv::imshow( "Color", color_mat );
			cv::Mat scale_mat;
			depth_mat.convertTo( scale_mat, CV_8U, -255.0 / 10000.0, 255.0 ); // 0-10000 -> 255(white)-0(black)
			//depth_mat.convertTo( scale_mat, CV_8U, 255.0 / 10000.0, 0.0 ); // 0-10000 -> 0(black)-255(white)

			// Apply False Colour
			//cv::applyColorMap( scale_mat, scale_mat, cv::COLORMAP_BONE );

			// Show Depth Image
			cv::imshow( "Depth", scale_mat );	
			int key = cv::waitKey(5);
			
			if (key == 'q' ) {
				break;
			}

			if (key == 'r' ) {
				if (!record) 
					record = true;
			}

			if (record) {
				cv::imwrite(m_strRGBDFolder + "/rgb/" + to_string(m_frameIdx) + ".png", color_mat);
				cv::imwrite(m_strRGBDFolder + "/depth/" + to_string(m_frameIdx) + ".png", depth_mat);
				m_frameIdx++;
			}
    	}

    }
}