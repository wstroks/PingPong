#include "gameSystem.h"
#include <iostream>

using namespace std;

gameSystem::gameSystem()
{
}

void gameSystem::InitGame()
{
    //inicializa a ola no centro da tela
	_ball.initialPosX = _feedWidth / 2;
	_ball.initialPosY = _feedHeight / 2;


	
    cout << "********************Comecem os jogos*********************\n\n";
	

	_ball.randomDirectionGenerator();

}

void gameSystem::startGame()
{
	VideoCapture Cap;

    //começa a captura
	Cap.open(0);
	if (!Cap.isOpened()){
        cerr << "Nenhuma webcam foi encontrada!\n\n";
	}


	_feedWidth = Cap.get(CV_CAP_PROP_FRAME_WIDTH);
	_feedHeight = Cap.get(CV_CAP_PROP_FRAME_HEIGHT);

    //inicializa o jogo
	InitGame();

	namedWindow("PingPongGame", 1);

	while (1){


		Cap >> _processOverlays.CameraFeed;

		waitKey(10);

		_trackPlayers();

        //detecta os jogadores

		
        //espera os jogadores estiverem prontos para jogar
		if (waitKey(10) == 'p'){
			_readyToPlay = true;
		}


		if (_readyToPlay==true){
		

			_ball.move(_ball.initialPosX, _ball.initialPosY, _processOverlays.CameraFeed,_bat);


			if (_playerNum == 1)
				_bat.moveBat(_processOverlays.CameraFeed, _processOverlays.centerYplayer1,_feedHeight);
			else
				_bat.moveBat(_processOverlays.CameraFeed, _processOverlays.centerYplayer2, _feedWidth,_feedHeight);


		}
		imshow("PingPongGame", _processOverlays.CameraFeed);
	}


}

void gameSystem::_defaultThreshVals()
{

    _processOverlays.lowH = 18;
    _processOverlays.highH = 35;

    _processOverlays.lowS = 102;
    _processOverlays.highS = 213;

    _processOverlays.lowV = 99;
    _processOverlays.highV = 220;
}

void gameSystem::_trackPlayers()
{
	if (_playerNum == 1){
        Scalar HSVmin = Scalar(19,102,99);
        Scalar HSVmax = Scalar(35,213,220);
		_processOverlays.detectPlayers(_processOverlays.CameraFeed, _playerNum, HSVmin, HSVmax);
		_playerNum = 2;
	}
	else{
        Scalar HSVmin = Scalar(30,98,81);
        Scalar HSVmax = Scalar(128,256,256);
		_processOverlays.detectPlayers(_processOverlays.CameraFeed, _playerNum, HSVmin, HSVmax);
		_playerNum = 1;
	}
	

}
