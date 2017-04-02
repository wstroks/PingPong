#include "OpencvProcessing.h"


OpencvProcessing::OpencvProcessing()
{
}

void  OpencvProcessing::detectPlayers(Mat &img,int playerNum,Scalar HSVmin,Scalar HSVmax)
{

            //converte de BGR para HSV
			cvtColor(img, _hsvImg, COLOR_BGR2HSV);


			_threshFeed(playerNum, HSVmin, HSVmax);

			_morphOps(_threshHoldImg);
			imshow("Threshhold", _threshHoldImg);

			if (waitKey(10) == 'c'){
				_showContour = !_showContour;
			}
			if (_showContour == true){
			
				_findContours(img,playerNum);
			}

		
	
}

void OpencvProcessing::_threshFeed(int playerNum, Scalar HSVmin, Scalar HSVmax)
{

	namedWindow("Threshhold", 1);
	//namedWindow("Controller", 1);

	////--create the Trackbars.

	///show the HSV video
	inRange(_hsvImg, HSVmin, HSVmax, _threshHoldImg);

}

void OpencvProcessing::_morphOps(Mat &_threshHoldImg)
{

	erode(_threshHoldImg, _threshHoldImg, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	//erode(threshholdimg,threshholdimg,getStructuringElement(MORPH_ELLIPSE,Size(5,5)));
	//dilation is just the opposite of erosoin  ie contrcts the black and expands the white region.
	dilate(_threshHoldImg, _threshHoldImg, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

}

void OpencvProcessing::_findContours(Mat &img,int playerNum)
{
        //encontrando momentos
		Moments objmoment = moments(_threshHoldImg);

		float m01 = objmoment.m01;
		float m10 = objmoment.m10;
		float area = objmoment.m00;


		float centerX = m10 / area;



		if (area >= 1000){
		
            vector <vector<Point> > contours;
			vector <Vec4i> hierarchy;

			int largestContour;

			findContours(_threshHoldImg, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

			double minArea = contourArea(contours[0], false);

			for (int i = 0; i < contours.size(); i++){

				double Area = contourArea(contours[i], false);
				if (Area >= minArea){
					minArea = Area;
					largestContour = i;
				}
			}
			if (contours.size() >= 1 && playerNum==1){

				centerYplayer1 = m01 / area;

				drawContours(img, contours, largestContour, Scalar(0, 255, 0), 1);

				circle(img, Point(centerX, centerYplayer1), 3, Scalar(255, 0, 0), 1, 8);


			}
			else if (contours.size() >= 1){
			
				centerYplayer2 = m01 / area;

				drawContours(img, contours, largestContour, Scalar(0, 255, 0), 1);

				circle(img, Point(centerX, centerYplayer2), 3, Scalar(0, 0, 255), 1, 8);
			}
		}
	
}
void OpencvProcessing::DrawBall(Point center,Mat &img)
{
	//draw the ball
	circle(img, center, ballRadius, Scalar(255, 255, 255), -2);
}

void OpencvProcessing::DrawBatPlayer1(Mat &img, Point pt1, Point pt2)
{
    rectangle(img, pt1, pt2, Scalar(255, 0, 0), -1, 8);
}

void OpencvProcessing::DrawBatPlayer2(Mat &img, Point pt1, Point pt2)
{
    rectangle(img, pt1, pt2, Scalar(0, 0, 255), -1, 8);
}

void OpencvProcessing::textOverlay( Mat &img,int &score1,int &score2)
{
	Score1 = score1;
	Score2 = score2;

	char str1[10],str2[10];
	sprintf(str1, "Score: %d", Score1);
	sprintf(str2, "Score: %d", Score2);
	
	putText(img, str1, score1point, 2, 1, Scalar(255, 0, 0), 2, 8);
	putText(img, str2, score2point, 2, 1, Scalar(0, 0, 255), 2, 8);
}
