// Autor: 1953921 Yuanzhe Chen 
#include<opencv2/opencv.hpp>
#include<vector>
#include<fstream>

const int cali_w=9;
const int cali_h=6;
const float cali_size=26; // mm
const std::string input_path="image/";
const std::string output_filename="camera_intrinsic.txt";

// Camera instrinsic
cv::Mat cameraMatrix,distCoeffs;

void cameraCalibration(){
    // Read from file
    std::vector<cv::Mat> images;
    std::vector<cv::String> imagePaths;
    cv::glob(input_path + "*.jpg", imagePaths, false);
    for (const auto& imagePath : imagePaths) {
        images.push_back(cv::imread(imagePath));
    }
    if(images.empty()){
        std::cerr<<"Error: Could not read input images." << std::endl;
        exit(-1);
    }
    // Compute for each image
    std::vector<std::vector<cv::Point2f>> imagePoints;
    std::vector<std::vector<cv::Point3f>> objectPoints;
    cv::Size boardSize(cali_w,cali_h);
    for(auto&image:images){
        cv::Mat image_gray;
        cv::cvtColor(image,image_gray,cv::COLOR_BGR2GRAY);
        std::vector<cv::Point2f> corners;
        if(cv::findChessboardCorners(image_gray,boardSize,corners)){
            cv::cornerSubPix(image_gray,corners,cv::Size(11,11),cv::Size(-1,-1),cv::TermCriteria(cv::TermCriteria::EPS+cv::TermCriteria::COUNT,30,0.1));
            cv::drawChessboardCorners(image,boardSize,corners,true);
            imagePoints.push_back(corners);
            std::vector<cv::Point3f> obj;
            for(int i=0;i<cali_h;i++){
                for(int j=0;j<cali_w;j++){
                    obj.push_back(cv::Point3f(j*cali_size,i*cali_size,0));
                }
            }
            objectPoints.push_back(obj);
        }
    }
    // Compute camera matrix and distortion coefficients
    cv::calibrateCamera(objectPoints,imagePoints,images[0].size(),cameraMatrix,distCoeffs,cv::noArray(),cv::noArray(),cv::CALIB_ZERO_TANGENT_DIST);

    // Save cameraMatrix and distCoeffs to file
    std::ofstream output_file(output_filename);
    if(output_file.is_open()){
        output_file<<"Camera Matrix:\n"<<cameraMatrix<<std::endl;
        output_file<<"Distortion Coefficients:\n"<<distCoeffs<<std::endl;
        output_file.close();

        std::cout<<"intrinsics saved to "<<output_filename<<std::endl;
    }
    else{
        std::cerr<<"Error: Could not open file "<<output_filename<<std::endl;
    }
}

// Generate BEV
void bevGenerator(){
    // Read from file
    cv::Mat image=cv::imread("input.jpg");
    
    // Unidistort image
    cv::Mat undistorted;
    cv::Mat undistorted_grey;
    cv::undistort(image,undistorted,cameraMatrix,distCoeffs);
    cv::imshow("undistorted",undistorted);
    cv::cvtColor(undistorted,undistorted_grey,cv::COLOR_BGR2GRAY);

    // Find feature in undistorted coordinate
    cv::Size boardSize(cali_w,cali_h);
    cv::Mat srcpoints,dstpoints;
    std::vector<cv::Point2f> corners;
    if(cv::findChessboardCorners(undistorted_grey,boardSize,corners,cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_NORMALIZE_IMAGE)){
        cv::cornerSubPix(undistorted_grey, corners, cv::Size(11, 11), cv::Size(-1, -1), cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::COUNT, 30, 0.1));
        srcpoints=(cv::Mat_<float>(4,2)<<corners[0].x,corners[0].y,corners[8].x,corners[8].y,corners[cali_h*cali_w-1].x,corners[cali_h*cali_w-1].y,corners[cali_h*cali_w-9].x,corners[cali_h*cali_w-9].y);

        std::cout<<corners<<std::endl;
    }
    else{
        std::cerr<<"Error: Could not find chessboard corners."<<std::endl;
        exit(-1);
    }

    // Features in world coordinate
    std::vector<cv::Point2f> obj;
    for(int i=0;i<cali_h;i++){
        for(int j=0;j<cali_w;j++){
            obj.push_back(cv::Point2f(j*cali_size,i*cali_size));
        }
    }
    dstpoints=(cv::Mat_<float>(4,2)<<obj[0].x,obj[0].y,obj[8].x,obj[8].y,obj[cali_h*cali_w-1].x,obj[cali_h*cali_w-1].y,obj[cali_h*cali_w-9].x,obj[cali_h*cali_w-9].y);
    dstpoints+=cv::Scalar(undistorted.size().width/4,undistorted.size().height/4);

    std::cout<<obj<<std::endl;

    // Perspective transform  
    cv::Mat M=cv::getPerspectiveTransform(srcpoints,dstpoints);
    cv::Mat result_raw;
    cv::warpPerspective(undistorted,result_raw,M,undistorted.size());

    // Get final result
    cv::Mat result;
    cv::Mat enlarge;
    double scale_factor=2.0;
    
    // Enlarge result
    cv::resize(result_raw,enlarge,cv::Size(result_raw.size().width*scale_factor,result_raw.size().height*scale_factor));
    // Crop result
    cv::Mat res_grey;
    cv::cvtColor(enlarge,res_grey,cv::COLOR_BGR2GRAY);
    cv::Mat mask;
    cv::threshold(res_grey,mask,0,255,cv::THRESH_BINARY);
    cv::Rect bbox=cv::boundingRect(mask);
    result=enlarge(bbox);

    // Show result
    cv::imshow("result_raw",result_raw);
    cv::imshow("result",result);
    cv::waitKey();
    cv::destroyAllWindows();

    // Save result
    cv::imwrite("result.jpg",result);
}

int main(){
    cameraCalibration();
    bevGenerator();
    return 0;
}