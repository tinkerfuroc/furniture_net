#include <boost/filesystem.hpp>
#include <boost/thread/thread.hpp>
#include <iostream>

#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/range_image/range_image.h>
#include <pcl/common/common_headers.h>
#include <pcl/visualization/range_image_visualizer.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/console/parse.h>

#include <string>
#include <vector>

using std::string;
using std::vector;


bool live_update = false;


class PCDProcessor
{
public:
    PCDProcessor()
        : cloud_ptr_(new pcl::PointCloud<pcl::PointXYZ>),
        coordinate_frame(pcl::RangeImage::CAMERA_FRAME),
        ang_res_x(0.5f), ang_res_y(0.5f)
    {
        ;
    }

    int load(string s)
    {
        return pcl::io::loadPCDFile<pcl::PointXYZ> (s, *cloud_ptr_);
    }

    void genRangeImg()
    {
        pcl::PointCloud<pcl::PointXYZ>& cloud = *cloud_ptr_;
        Eigen::Affine3f scene_sensor_pose (Eigen::Affine3f::Identity());
        scene_sensor_pose = Eigen::Affine3f(
            Eigen::Translation3f (
                cloud.sensor_origin_[0],
                cloud.sensor_origin_[1],
                cloud.sensor_origin_[2]
            )
        ) * Eigen::Affine3f(cloud.sensor_orientation_);
        float noise_level = 0.0;
        float min_range = 0.0f;
        int border_size = 1;
        boost::shared_ptr<pcl::RangeImage> range_image_ptr(new pcl::RangeImage);
        pcl::RangeImage& range_image = *range_image_ptr;   
        range_image.createFromPointCloud(
            cloud, 
            ang_res_x, 
            ang_res_y,
            pcl::deg2rad (360.0f), 
            pcl::deg2rad (180.0f),
            scene_sensor_pose, 
            coordinate_frame, 
            noise_level, 
            min_range, 
            border_size
        );
        
    }
private:
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_ptr_;
    float ang_res_x;
    float ang_res_y;
    pcl::RangeImage::CoordinateFrame coordinate_frame;
    
};

int main()
{
    boost::filesystem::path path = boost::filesystem::current_path();
    boost::filesystem::recursive_directory_iterator itr(path);
    PCDProcessor p;
    while (itr != boost::filesystem::recursive_directory_iterator())
    {
        string filepath = itr->path().string();
        std::cout << filepath << std::endl;
        if (p.load(filepath) != -1)
        {
            p.genRangeImg();
        }
        else
            ;
        ++itr;
    }
}
