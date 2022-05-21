
#pragma once
#include "CommonFunction.h"
#include "BaseObj.h"
#include "OtherObj.h"

#define GRAVITY_SPEED 0.2
#define MAX_FALL_SPEED 4
#define PLAYER_SPEED 2
#define BLANK_TILE 0
#define JUMP_VAL 8
#define PINK_FISH 5
#define BLACK_FISH 6
#define POISON 4
#define PINK_LIQUID 7
#define BLACK_LIQUID 8


class Player : public BaseObj
{
public:
	Player();
	~Player();

	enum WalkType {
		WALK_RIGHT = 0,
		WALK_LEFT = 1,
		STAY_LEFT = 2,
		STAY_RIGHT = 3,
		JUMP=4,
	};

	bool LoadImg(string path, SDL_Renderer* renderer);
	void show1(SDL_Renderer* des);
	void show2(SDL_Renderer* des);
	void handleEvent1(SDL_Event e, SDL_Renderer* renderer,Mix_Chunk* sound[5]);
	void handleEvent2(SDL_Event e, SDL_Renderer* renderer, Mix_Chunk* sound[5]);
	void setclip();

	void DoPlayer1(Map& mapdata, int p);
	void DoPlayer2(Map& mapdata, int p);

	void CheckToMap1(Map& mapdata);
	void CheckToMap2(Map& mapdata);

	void CheckToMus(int p, OtherObj &mushroom);

	void CheckToGate(int p,OtherObj &gate_);

	void UpdateImgPlayer1(SDL_Renderer* des);
	void UpdateImgPlayer2(SDL_Renderer* des);

	
	void PinkFish_Player1();
	void BlackFish_Player1();
	void PinkLiquid_Player1();
    int getScore1()
	{
	    int score;
	    score = pinkfish1 + blackfish1 + pinkliquid1;
	    return score;
	}
	
	
	void PinkFish_Player2();
	void BlackFish_Player2();
	void BlackLiquid_Player2();
    int getScore2()
	{
	    int score;
	    score = pinkfish2 + blackfish2 + blackliquid2;
	    return score;
	}
	
	
	void setPos(float x,float y)
	{
		xpos = x;
		ypos = y;
	}
	void nextLevel(bool check) {
		check = true;
	}

	bool checkNextLevelP1() {
		return nextLevelPlayer[0];
	}
	bool checkNextLevelP2() {
		return nextLevelPlayer[1];
	}
	int GameOver1() { return gameoverState; }
	int GameOver2() { return gameoverState; }
	
	void changeState() {
		if (gameoverState == 1)
		{
			gameoverState = 0;
		}
	}

private:

	int pinkfish1;
	int blackfish1;
	int pinkliquid1;


	int pinkfish2;
	int blackfish2;
	int blackliquid2;

	float xval;
	float yval;
	float xpos;
	float ypos;

	int widthframe;
	int heightframe;

	bool nextLevelPlayer[2]={0,0};

	SDL_Rect FRAME_CLIP[7];


	Input input_type;
	int frame;
	int status;
	bool onground=false;
	int gameoverState=0;
};
