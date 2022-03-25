#pragma once
#include "CommonFunction.h"
#include "BaseObj.h"

#define GRAVITY_SPEED 0.3
#define MAX_FALL_SPEED 10
#define PLAYER_SPEED 2
#define BLANK_TILE 0
#define JUMP_VAL 10
class PlayerObj : public BaseObj
{
public:
	PlayerObj();
	~PlayerObj();

	enum WalkType {
		WALK_RIGHT = 0,
		WALK_LEFT = 1,
		STAY_LEFT = 2,
		STAY_RIGHT=3,
	};

	bool LoadImg(string path, SDL_Renderer* renderer);
	void show(SDL_Renderer* des);
	void handleEvent(SDL_Event e, SDL_Renderer* renderer);
	void setclip(); 
	
	void DoPlayer(Map& mapdata);

	void CheckToMap(Map& mapdata);
	void UpdateImgPlayer(SDL_Renderer* des);

private:
	float xval;
	float yval;

	float xpos;
	float ypos;

	int widthframe;
	int heightframe;

	SDL_Rect FRAME_CLIP[7];


	Input input_type;
	int frame;
	int status;
	bool onground=false;

};

