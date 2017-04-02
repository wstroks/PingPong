#pragma once

#include "Ball.h"
//#include "Bat.h"

#include <string>

class gameSystem
{
public:
	gameSystem();
	void startGame();

private:
	OpencvProcessing _processOverlays;
	Ball _ball;
	Bat _bat;

	int _randomBallDirection;
	int _playerNum=1;
	bool _readyToPlay = false;

	void InitGame();
	double _feedWidth;
	double _feedHeight;
	
    //seta os valores do thesholder
	void _defaultThreshVals();
	
    //
	void _trackPlayers();

};

