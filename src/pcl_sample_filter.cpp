#include<ros/ros.h>
#include<pcl/point_cloud.h>
#include<pcl_conversions/pcl_conversions.h>
#include<sensor_msgs/PointCloud2.h>
#include<pcl/filters/statistical_outlier_removal.h>

class cloud_filter{

public:
	cloud_filter();
	void cloud_sub_pub(const sensor_msgs::PointCloud2& input);

protected:
	ros::NodeHandle nh;
	ros::Subscriber pcl_sub;
	ros::Publisher pcl_pub;
};

cloud_filter::cloud_filter()
{
pcl_sub = nh.subscribe("/pcl_reader_output",10,&cloud_filter::cloud_sub_pub,this);
pcl_pub = nh.advertise<sensor_msgs::PointCloud2>("statistical_outlier_removal_cloud",1);
}
void cloud_filter::cloud_sub_pub(const sensor_msgs::PointCloud2 & input)
{
pcl::PointCloud<pcl::PointXYZ> cloud, filtered_cloud;
sensor_msgs::PointCloud2 result;
pcl::fromROSMsg(input,cloud);
pcl::StatisticalOutlierRemoval<pcl::PointXYZ> statFilter;
statFilter.setInputCloud(cloud.makeShared());
statFilter.setMeanK(50);
statFilter.setStddevMulThresh(0.2);
statFilter.filter(filtered_cloud);
pcl::toROSMsg(filtered_cloud,result);
result.header.frame_id="map";
pcl_pub.publish(result);

}
int main(int argc,char ** argv)
{
ros::init(argc,argv,"statistical_outlier_removal_filter");
cloud_filter filter;
ros::spin();
return 0;

}