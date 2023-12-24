#include <iostream>
#include <vector>
#include <string>

#include <opencv2/opencv.hpp>
#include <vector>
#include <algorithm>
#include <iostream>
#include <vector>
#include <algorithm>

class Box {
public:
    int x1;
    int y1;
    int x2;
    int y2;
    float score;

    int area() {
        return (x2 - x1 + 1) * (y2 - y1 + 1);
    }
}Box;

// 计算两个边界框的交并比
float iou(const Box& box1, const Box& box2) {
    int x1 = std::max(box1.x1, box2.x1);
    int y1 = std::max(box1.y1, box2.y1);
    int x2 = std::min(box1.x2, box2.x2);
    int y2 = std::min(box1.y2, box2.y2);

    int width = std::max(0, x2 - x1 + 1);
    int height = std::max(0, y2 - y1 + 1);

    int intersection = width * height;
    int area1 = box1.area();
    int area2 = box2.area();

    float iou = static_cast<float>(intersection) / (area1 + area2 - intersection);

    return iou;
}

void nms(std::vector<Box>& input_boxes, float threshold, std::vector<Box>& output_boxes)
{
    std::sort(input_boxes.begin(), input_boxes.end(), [](const Box& a, const Box& b) { return a.score > b.score; });

    while (input_boxes.size() > 0)
    {
        Box box1 = input_boxes[0];
        output_boxes.push_back(box1);

        input_boxes.erase(input_boxes.begin());

        for (auto it = input_boxes.begin(); it != input_boxes.end(); )
        {
            Box box2 = *it;

            float iou = iou(box1, box2);

            if (iou > threshold)
                it = input_boxes.erase(it);
            else
                ++it;
        }
    }
}

int main(int argc, char** argv)
{

    std::vector<Box> input_boxes;
    input_boxes.push_back(Box(100, 100, 210, 210));
    input_boxes.push_back(Box(105, 105, 200, 200));
    input_boxes.push_back(Box(130, 130, 160, 160));
    input_boxes.push_back(Box(160, 160, 100, 100));
    input_boxes.push_back(Box(180, 180, 40, 40));

    std::vector<Box> output_boxes;
    nms(input_boxes, 0.3, output_boxes);

    for (size_t i = 0; i < output_boxes.size(); i++)
    {
        
    }

    return 0;
}