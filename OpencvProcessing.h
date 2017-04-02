#pragma once

#include <string>
#include <vector>
//#include <sstream>


#include<opencv\cv.h>
#include<opencv2\opencv.hpp>

using namespace cv;

class OpencvProcessing
{
public:
	
	OpencvProcessing();
	
	Mat CameraFeed;
	
    //pontos para escrever a pontuação
	Point score1point = Point(80, 45);
	Point score2point = Point(480, 45);
	

	int ballRadius = 6;


	float centerYplayer1=0;
	float centerYplayer2=0;


	int lowH;
	int highH;

	int lowS;
	int highS;

	int lowV;
	int highV;
	
	int Score1 = 0, Score2 = 0;


	void DrawBall(Point center,Mat &img);

	void DrawBatPlayer1(Mat &img,Point pt1,Point pt2);

	void DrawBatPlayer2(Mat &img, Point pt1, Point pt2);

	void textOverlay(Mat &img,int &score1,int &score2);

	void detectPlayers(Mat &img, int playerNum, Scalar HSVmin, Scalar HSVmax);

private:
	bool _isAlreadyThreshed = false;
	bool _showContour = false;
	Mat _hsvImg;
	Mat _threshHoldImg;
	Mat _equalizedHist;

	void _threshFeed(int playerNum, Scalar HSVmin, Scalar HSVmax);
	void _morphOps(Mat &_threshHoldImg);
	void _findContours(Mat &img, int playerNum);
	
};

