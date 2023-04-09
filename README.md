# 23_Spring_computer_vision
 TJU SSE 2023 Spring CV Assignments
## How to run the code
1. Assignment1
    - RANSAC
        ```bash
        python3 RANSAC.py
        ```
    - PanoramaStitch
        ```bash
        g++ -std=c++11 Stitch.cpp -o sift_stitching.o `pkg-config --cflags --libs opencv4`
        ./sift_stitching.o mysse11.bmp mysse22.bmp
        ```
    - ORB
        ```bash
        g++ -std=c++11 ORB.cpp -o orb_matching.o `pkg-config --cflags --libs opencv4`
        ./orb_matching.o mysse11.bmp mysse22.bmp
        ```