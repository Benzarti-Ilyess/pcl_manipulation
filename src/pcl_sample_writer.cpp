#include<ros/ros.h>
#include<pcl/point_cloud.h>
#include<pcl_conversions/pcl_conversions.h>
#include<sensor_msgs/PointCloud2.h>
#include<pcl/io/pcd_io.h>

void saving_point_clouds(const sensor_msgs::PointCloud2 & input)
{
pcl::PointCloud<pcl::PointXYZ> cloud;
pcl::fromROSMsg(input,cloud);
ROS_INFO("hi");
pcl::io::savePCDFileASCII("ilyess1.pcd",cloud);
ROS_INFO("goodbye");


}

int main(int argc, char**argv)
{

ros::init(argc,argv,"pcl_writer");
ros::NodeHandle nh; 
ros::Subscriber pcl_sub = nh.subscribe("kitti/velo/pointcloud",10,saving_point_clouds);
ros::spin();





	return 0;
}