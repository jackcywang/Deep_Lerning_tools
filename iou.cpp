#include <iostream>
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
    float area1 = (box1.x2 - box1.x1 + 1)*(box1.y2 - box1.y1 +1);
    float area2 = (box2.x2 - box2.x1 + 1)*(box2.y2 - box2.y1 + 1);
    int xx1 = std::max(box1.x1,box2.x1);
    int xx2 = std::min(box1.x2,box2.x2);
    int yy1 = std::max(box1.y1, box2,y1);
    int yy2 = std::min(box1.y2, box2.y2);
    if(xx1>=xx2 || yy1 > yy2){
        return 0;
    }
    else{
        float interaction= (xx2 - xx1 + 1)*(yy2 - yy1 + 1);
        return interaction/(area1 + area2 - interaction);
    }
}