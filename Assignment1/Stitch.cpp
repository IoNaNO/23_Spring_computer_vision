#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/calib3d.hpp>

int main(int argc,char **argv){
    if(argc!=3){
        std::cerr<<"Wrong argc!"<<"Usage:"<<argv[0]<<"<image1> <image2>"<<std::endl;
        return -1;
    }
    cv::Mat image1=cv::imread(argv[1]);
    cv::Mat image2=cv::imread(argv[2]);

    if(image1.empty()||image2.empty()){
        std::cerr<<"Error: Could not read input images." << std::endl;
        return -1;
    }

    // Convert image to grayscale
    cv::Mat I1,I2;
    cv::cvtColor(image1,I1,cv::COLOR_BGR2GRAY);
    cv::cvtColor(image2,I2,cv::COLOR_BGR2GRAY);

    // Init sift feature detector
    cv::Ptr<cv::SIFT> sift=cv::SIFT::create();

    // Detect keypoints and compute decriptors
    std::vector<cv::KeyPoint> keypoint1,keypoint2;
    cv::Mat descriptors1,descriptors2;
    sift->detectAndCompute(I1,cv::noArray(),keypoint1,descriptors1);
    sift->detectAndCompute(I2,cv::noArray(),keypoint2,descriptors2);

    // Initialize BF matcher
    cv::BFMatcher matcher(cv::NORM_L2);
    // Match descriptors
    std::vector<cv::DMatch> matches;
    matcher.match(descriptors1,descriptors2,matches);
    // Drwa matches
    cv::Mat img_matches;

    // Show match result
    cv::drawMatches(image1,keypoint1,image2,keypoint2,matches,img_matches);
    cv::namedWindow("oriMatches",cv::WINDOW_AUTOSIZE);
    cv::imshow("oriMatches",img_matches);
    
    // Keep only good matches
    float min_dist=matches.begin()->distance;
    for(auto&it:matches){
        min_dist=std::min(min_dist,it.distance);
    }
    std::vector<cv::DMatch> good_matches;
    for(auto&it:matches){
        if(it.distance<=(2*min_dist)){
            good_matches.push_back(it);
        }
    }

    // Show good match result
    cv::drawMatches(image1,keypoint1,image2,keypoint2,good_matches,img_matches);
    cv::namedWindow("goodMatches",cv::WINDOW_AUTOSIZE);
    cv::imshow("goodMatches",img_matches);
    // cv::waitKey(0);

    // Use RANSAC to find homography
    std::vector<cv::Point2f> src,dst;
    for(auto&it:good_matches){
        src.push_back(keypoint1[it.queryIdx].pt);
        dst.push_back(keypoint2[it.trainIdx].pt);
    }
    cv::Mat H=cv::findHomography(src,dst,cv::RANSAC);

    // Warp the first image using the found homography and blend both images together
    cv::Mat result;
    cv::warpPerspective(image1,result,H,cv::Size(image1.cols+image2.cols,image1.rows));
    image2.copyTo(result(cv::Rect(0,0,image2.cols,image2.rows)));

    // Display the result
    cv::namedWindow("Stitching",cv::WINDOW_AUTOSIZE);
    cv::imshow("Stitching",result);
    cv::waitKey(0);

    return 0;
}