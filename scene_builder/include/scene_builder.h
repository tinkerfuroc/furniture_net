#ifndef __FURNITURE_NET_SCENE_BUILDER_H__
#define __FURNITURE_NET_SCENE_BUILDER_H__

#include <opencv2/opencv.hpp>
#include <vector>

namespace furoc {
namespace furniturenet {
class SceneBuilder {
public:
    void GetScene(std::vector<cv::Mat> &imgs, std::vector<cv::Mat> &label_imgs) = 0;
};
}
}

#endif
