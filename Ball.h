#pragma once

#include "Bat.h"

enum Direction {UPRIGHT=1,UPLEFT=2,DOWNRIGHT=3,DOWNLEFT=4};

class Ball
{
public:


	Ball();

    //guarda a proxima posição da bola
	double initialPosX, initialPosY;

	int direction;
	
	
	

	void move(double &posX, double &PosY, Mat &Img,Bat bat);
	void randomDirectionGenerator();

private:

	OpencvProcessing _processBall;
	Bat	_bat;

    //detecta colisão
	void  _detectCollision(double &posX,double &posY,int &randomDirection,double frameWidth,double frameHeight);

};

