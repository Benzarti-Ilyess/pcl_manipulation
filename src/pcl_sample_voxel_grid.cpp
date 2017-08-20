#include<ros/ros.h>
#include<pcl/point_cloud.h>
#include<pcl_conversions/pcl_conversions.h>
#include<sensor_msgs/PointCloud2.h>
#include<pcl/filters/voxel_grid.h>
main(int argc,char**argv)
{
ros::init(argc,argv,"pcl_create_voxel_grid");
ros::NodeHandle	nh;
ros::Publisher	pcl_pub	=nh.advertise<sensor_msgs::PointCloud2>("pcl_output_voxel_grip",1);
pcl::PointCloud<pcl::PointXYZ>	cloud;
pcl::PointCloud<pcl::PointXYZ>	cloud_downsampled;
sensor_msgs::PointCloud2 output;
//	Fill	in	the	cloud	data
cloud.width	=1000;
cloud.height=100;
cloud.points.resize(cloud.width	*cloud.height);
for	(size_t	i=0;i<cloud.points.size();++i)
{
cloud.points[i].x=1024*rand()/(RAND_MAX	+1.0f);
cloud.points[i].y=1024*rand()/(RAND_MAX	+1.0f);
cloud.points[i].z=1024*rand()/(RAND_MAX	+1.0f);
}

pcl::VoxelGrid<pcl::PointXYZ>	voxelSampler;
voxelSampler.setInputCloud(cloud.makeShared());
voxelSampler.setLeafSize(0.2f,	0.2f,	0.2f);
voxelSampler.filter(cloud_downsampled);
//Convert	the	cloud	to	ROS	message
pcl::toROSMsg(cloud_downsampled,output);
output.header.frame_id="map";
ros::Rate loop_rate(1);
while(ros::ok())
{
pcl_pub.publish(output);
ros::spinOnce();
loop_rate.sleep();
}
return	0;
}