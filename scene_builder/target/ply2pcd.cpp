#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/point_types.h>
#include <pcl/io/vtk_lib_io.h>
#include <pcl/io/vtk_io.h>
#include <pcl/console/print.h>
#include <pcl/console/parse.h>
#include <pcl/console/time.h>
#include <pcl/visualization/pcl_visualizer.h>

using namespace pcl;
using namespace pcl::io;
using namespace pcl::console;


int main(int argc, char** argv) {
    bool binary = true;

    if (argc < 3) {
        std::cerr << "Usage:" << std::endl;
        std::cerr << argv[0] << " [-a] input.ply output.pcd" << std::endl;
        std::cerr << "\t-a\tASCII output" << std::endl;
        return (1);
    }

    if (argc == 4) {
        if (strncmp(argv[1], "-a", 2) != 0) {
            std::cerr << "Error: unknown option!" << std::endl;
            return (1);
        } else {
            binary = false;
            argv += 1;
        }
    }

    pcl::PolygonMesh mesh;

    pcl::io::loadPolygonFile(argv[1], mesh);
    pcl::PCDWriter pcdwriter;
    pcdwriter.writeBinary(argv[2], mesh.cloud);

    return (0);
}
