// Autor: 1953921 Yuanzhe Chen 
#include<iostream>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/features2d.hpp>

int main(int argc,char** argv){
    if(argc!=3){
        std::cerr<<"Wrong argc!"<<"Usage:"<<argv[0]<<"<image1> <image2>"<<std::endl;
        return -1;
    }
    cv::Mat I1=cv::imread(argv[1]);
    cv::Mat I2=cv::imread(argv[2]);

    if(I1.empty()||I2.empty()){
        std::cerr<<"Error: Could not read input images." << std::endl;
        return -1;
    }

    // Init ORB feature detector
    cv::Ptr<cv::ORB> orb=cv::ORB::create();

    // Detect keypoints and compute decriptors
    std::vector<cv::KeyPoint> keypoint1,keypoint2;
    cv::Mat descriptors1,descriptors2;
    orb->detectAndCompute(I1,cv::noArray(),keypoint1,descriptors1);
    orb->detectAndCompute(I2,cv::noArray(),keypoint2,descriptors2);

    // Initialize BF matcher
    cv::BFMatcher matcher(cv::NORM_HAMMING);

    // Match descriptors
    std::vector<cv::DMatch> matches;
    matcher.match(descriptors1,descriptors2,matches);

    // Draw matches
    cv::Mat img_matches;
    cv::drawMatches(I1,keypoint1,I2,keypoint2,matches,img_matches);

    // Show result
    cv::namedWindow("Matches",cv::WINDOW_AUTOSIZE);
    cv::imshow("Matches",img_matches);
    cv::waitKey(0);
    return 0;
}