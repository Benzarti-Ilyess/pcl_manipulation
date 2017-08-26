#include<ros/ros.h>
#include<pcl/point_cloud.h>
#include<pcl_conversions/pcl_conversions.h>
#include<sensor_msgs/PointCloud2.h>
#include<pcl/filters/voxel_grid.h>
class cloud_voxel
{
public:
	cloud_voxel();
	void voxel_handler(const sensor_msgs::PointCloud2 & input);

protected:
	ros::NodeHandle nh;
	ros::Subscriber pcl_sub;
	ros::Publisher pcl_pub;


};


cloud_voxel::cloud_voxel()
{
pcl_sub = nh.subscribe("/statistical_outlier_removal_cloud",10,&cloud_voxel::voxel_handler,this);
pcl_pub = nh.advertise<sensor_msgs::PointCloud2>("downsampled_voxel_grid",1);
}


void cloud_voxel::voxel_handler(const sensor_msgs::PointCloud2 & input)
{
pcl::PointCloud<pcl::PointXYZ> cloud, cloud_downsampled;
sensor_msgs::PointCloud2 voxel_cloud;
pcl::fromROSMsg(input,cloud);
pcl::VoxelGrid<pcl::PointXYZ> voxel_sampler;
voxel_sampler.setInputCloud(cloud.makeShared());
voxel_sampler.setLeafSize(0.02f,0.02f,0.02f);
voxel_sampler.filter(cloud_downsampled);
pcl::toROSMsg(cloud_downsampled,voxel_cloud);
pcl_pub.publish(voxel_cloud);
}



int main(int argc ,char ** argv)
{ ros::init(argc,argv,"down_sampling_voxel_grid");

cloud_voxel pcl_cloud;
ros::spin();

	return 0;
}