#include <cmath>
#include <algorithm>
#include <husky_highlevel_controller/HsukyHighlevelController.hpp>

namespace husky_highlevel_controller {

HuskyHighlevelController::HuskyHighlevelController(ros::NodeHandle& nodeHandle) :
  nodeHandle_(nodeHandle), scan_sub_quenesize(200), sacn_topic("/scan"){
	if (!readParameters()) {
		ROS_ERROR("Could not read parameters.");
		ros::requestShutdown();
	}
	scan_subscriber = nodeHandle_.subscriber(sacn_topic, scan_sub_quenesize,          				&HuskyHighlevelController::scan_Callback, this)

}

SmbHighlevelController::~SmbHighlevelController()
{
}

bool SmbHighlevelController::readParameters() {
	bool success = true;
	success &= nodeHandle_.getParam(
			"/husky_highlevel_controller/scan_subscriber_topic_name", sacn_topic);
	success &= nodeHandle_.getParam(
			"/husky_highlevel_controller/scan_subscriber_queue_size",
			scan_sub_quenesize);
	return success;
}


Void HuskyHighlevelController::scan_Callback(const sensor_msgs::LaserScan::ConstPtr &msg){
	double min = msg->range_max;
	for (int i = 0; i < msg->ranges.size(); ++i) {
		if (msg->ranges[i] < min)
			min = msg->ranges[i];
	}
	ROS_INFO_STREAM_THROTTLE(2.0,"Minimum Range: " << min);
}

} /* husky_highlevel_controller */
