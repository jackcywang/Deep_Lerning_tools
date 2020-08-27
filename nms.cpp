#include <iostream>
#include <vector>
#include <algorithm>

struct Bbox{
    int x1;
    int y1;
    int x2;
    int y2;
    float score;
    Bbox(int x1_, int y1_, int x2_, int y2_, float s):
        x1(x1_), y1(y1_), x2(x2_),y2(y2_),score(s){};
};

float iou(Bbox box1, Bbox box2){
    float area1 = (box1.x2 - box1.x1 + 1) * (box1.y2 - box1.y1 + 1);
    float area2 = (box2.x2 - box2.x1 + 1) * (box2.y2 - box2.y1 + 1);
    int x11 = std::max(box1.x1, box2.x1);
    int y11 = std::max(box1.y1, box2.y1);
    int x22 = std::min(box1.x2, box2.x2);
    int y22 = std::min(box1.y2, box2.y2);
    if(x11>x22 || y11>=y22){
        return 0;
    }
    else{
        float intersection = (x22 - x11 + 1)*(y22 - y11 + 1);
        return intersection/(area1 + area2 - intersection);
    }
}

bool cmpScore(Bbox box1, Bbox box2) {
	return box1.score < box2.score; // 升序排列, 令score最大的box在vector末端
};


std::vector<Bbox> nms(std::vector<Bbox>& vecbox, float threshold){
    // auto cmpScore = [](Bbox box1, Bbox box2) {
	// return box1.score < box2.score; // 升序排列, 令score最大的box在vector末端
    // };
    std::sort(vecbox.begin(),vecbox.end(),cmpScore);
    std::vector<Bbox> pickedBbox;
    while(vecbox.size()>0){
        pickedBbox.emplace_back(vecbox.back());
        vecbox.pop_back();
        for(int i=0;i < vecbox.size(); i++){
            if(iou(pickedBbox.back(),vecbox[i]) >= threshold){
                vecbox.erase(vecbox.begin()+i);
            }
        }
    }
    return pickedBbox;
}

int main() {
    std::vector<Bbox> vecBbox;
    vecBbox.emplace_back(Bbox(187, 82, 337, 317, 0.9));
    vecBbox.emplace_back(Bbox(150, 67, 305, 282, 0.75));
    vecBbox.emplace_back(Bbox(246, 121, 368, 304, 0.8));

    auto pickedBbox = nms(vecBbox, 0.5);

    for (auto box : pickedBbox) {
	std::cout << box.x1 << ", " <<
		box.y1 << ", " <<
		box.x2 << ", " <<
		box.y2 << ", " <<
		box.score << std::endl;
    }
    return 0;
}