# 23_Spring_computer_vision
TJU SSE 2023 Spring CV Assignments
## Where is the assignment document
```bash
│  
└─Assignment1
    │  1953921_Assignment1.md
    │  1953921_Assignment1.pdf
```
## How to run the code
The OpenCV version I used: 3.4.19-dev
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
2. Assignment2
    - BEV
        ```bash
        g++ -std=c++11 BEV.cpp -o bev.o `pkg-config --cflags --libs opencv4`
        ./bev.o
        ```