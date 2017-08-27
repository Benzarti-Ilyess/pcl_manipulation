#include<ros/ros.h>
#include<pcl/point_cloud.h>
#include<pcl_conversions/pcl_conversions.h>
#include<sensor_msgs/PointCloud2.h>
#include<pcl/io/pcd_io.h>

int main (int argc,char ** argv)
{

ros::init(argc,argv,"pcl_reader");
ros::NodeHandle nh;

ros::Publisher pcl_pub = nh.advertise<sensor_msgs::PointCloud2>("pcl_reader_output",1);
sensor_msgs::PointCloud2 output;
pcl::PointCloud<pcl::PointXYZ> cloud;
pcl::io::loadPCDFile("table.pcd",cloud);

pcl::toROSMsg(cloud,output);

output.header.frame_id="map";
ros::Rate loop_rate(1);

while(ros::ok())
{

	pcl_pub.publish(output);
	ros::spinOnce();
	loop_rate.sleep();
} 

	return 0;
}