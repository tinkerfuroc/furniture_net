#include <boost/filesystem.hpp>
#include <boost/thread/thread.hpp>
#include <iostream>
#include <pcl/point_cloud.h>
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/point_types.h>
#include <pcl/io/vtk_lib_io.h>
#include <pcl/io/vtk_io.h>
#include <pcl/console/print.h>
#include <pcl/console/parse.h>
#include <pcl/console/time.h>
#include <pcl/visualization/pcl_visualizer.h>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <string>
#include <vector>

using std::string;
using std::vector;
using std::cout;
using std::endl;

typedef pcl::PointXYZ  pointType;

class Ply2depth
{
public:
    Ply2depth(int width=640, int height=480)
        : range_img_(cv::Mat::zeros(width, height, CV_32FC1))
    {
        ;
    }
    
    int load(string s)
    {
        return pcl::io::loadPolygonFilePLY(s, mesh_);
    }
    
    void process()
    {
        pol_ = mesh_.polygons;
        pcl::fromPCLPointCloud2(mesh_.cloud, pc_); 
        for (int i=0; i<pol_.size(); i++) 
        {
            vector<pointType> ver;
            vector<uint32_t> &vertices = pol_[i].vertices; 
            for (int j=0; j<vertices.size(); j++)
            {
                ver.push_back(pc_[vertices[j]]);
            }
            draw(ver);
        }
    }

    void draw(vector<pointType> ver)
    {
        
    }
    
    void save(string s)
    {
       
    }
    
private:
    pcl::PolygonMesh mesh_; 
    pcl::PointCloud<pointType> pc_;
    vector<pcl::Vertices> pol_;
    cv::Mat range_img_;
};

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cout<<"usage: ply2pcd input.ply output.pcd";
        return -1;
    }
    
    string input_path(argv[1]);
    string output_path(argv[2]);
    
    Ply2depth p;
    if (p.load(input_path) != -1)
    {
        p.process();
        p.save(output_path);
    }
    else
        ;
    return 0;
}
