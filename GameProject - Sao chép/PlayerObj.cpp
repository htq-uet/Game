#include "PlayerObj.h"
PlayerObj::PlayerObj() {
	frame = 0;
	xpos = 400;
	ypos = 0;
	xval = 0;
	yval = 0;
	widthframe = 0;
	heightframe = 0;
	status = -1;
	onground = false;
	input_type.left = 0;
	input_type.right = 0;
	input_type.stayleft = 0;
	input_type.stayright = 0;
	input_type.jump = 0;
}
PlayerObj::~PlayerObj() {
	Free();
}
bool PlayerObj::LoadImg(string path, SDL_Renderer* renderer) {
	bool ktra = BaseObj::LoadImg(path, renderer);

	if (ktra == true) {
		widthframe = 32;
		heightframe = 32;
	}
	return ktra;
}

void PlayerObj::setclip() {
	if (widthframe > 0 && heightframe > 0) {
		FRAME_CLIP[0].x = 0;
		FRAME_CLIP[0].y = 0;
		FRAME_CLIP[0].w = widthframe;
		FRAME_CLIP[0].h = heightframe;

		FRAME_CLIP[1].x = widthframe;
		FRAME_CLIP[1].y = 0;
		FRAME_CLIP[1].w = widthframe;
		FRAME_CLIP[1].h = heightframe;

		FRAME_CLIP[2].x = widthframe*2;
		FRAME_CLIP[2].y = 0;
		FRAME_CLIP[2].w = widthframe;
		FRAME_CLIP[2].h = heightframe;

		FRAME_CLIP[3].x = widthframe*3 ;
		FRAME_CLIP[3].y = 0;
		FRAME_CLIP[3].w = widthframe;
		FRAME_CLIP[3].h = heightframe;

		FRAME_CLIP[4].x = widthframe*2;
		FRAME_CLIP[4].y = 0;
		FRAME_CLIP[4].w = widthframe;
		FRAME_CLIP[4].h = heightframe;

		FRAME_CLIP[5].x = widthframe;
		FRAME_CLIP[5].y = 0;
		FRAME_CLIP[5].w = widthframe;
		FRAME_CLIP[5].h = heightframe;

		FRAME_CLIP[6].x = 0;
		FRAME_CLIP[6].y = 0;
		FRAME_CLIP[6].w = widthframe;
		FRAME_CLIP[6].h = heightframe;


	}
}
void PlayerObj::show(SDL_Renderer* des) {
	UpdateImgPlayer(des);
	if ((input_type.left == 1 || input_type.right == 1|| input_type.stayright == 1|| input_type.stayleft == 1)&&onground==true&&input_type.jump==0) {
		if (frame >= 0) {
			++frame;
		}
		
	}
	else {
		frame = 0;
	}
	if (input_type.jump == 1) {
		frame = 0;
	}
	
	 if (frame / 6 >= 6) {
		frame=0;
	}
	
	rect.x = xpos;
	rect.y = ypos;

	SDL_Rect* currentclip = &FRAME_CLIP[frame/6];
	SDL_Rect renderQuad = {rect.x,rect.y,widthframe*3,heightframe*3 };

	if (currentclip != NULL)
	{
		renderQuad.w = 3*currentclip->w;
		renderQuad.h = 3*currentclip->h;
	}


	SDL_RenderCopy(des, texture, currentclip, &renderQuad);
}
void PlayerObj::handleEvent(SDL_Event e,SDL_Renderer* renderer) {
	if (e.type == SDL_KEYDOWN) {
		switch (e.key.keysym.sym) {
		case SDLK_d:
			status = WALK_RIGHT;
			input_type.right = 1;
			input_type.left = 0;
			input_type.stayleft = 0;
			input_type.stayright = 0;
			UpdateImgPlayer(renderer);
			break;

		case SDLK_a: 
			status = WALK_LEFT;
			input_type.left = 1;
			input_type.right = 0;
			input_type.stayleft = 0;
			input_type.stayright = 0;
			UpdateImgPlayer(renderer);

			break;
		case SDLK_w:
			input_type.jump = 1; 
			input_type.stayleft = 0;
			input_type.stayright = 0;
		default:
			break;
		}
	}
	else if (e.type == SDL_KEYUP) {
		switch (e.key.keysym.sym) {
		case SDLK_d: 
			status = STAY_RIGHT;
			if (onground == true) {
				input_type.stayright = 1;
			}
			input_type.right = 0;
			input_type.stayleft = 0;
			
			UpdateImgPlayer(renderer);

			break;
		case SDLK_a: 
			status = STAY_LEFT;
			if (onground == true) {
				input_type.stayleft = 1;
			}
			input_type.left = 0;
			input_type.stayright = 0;
			
			UpdateImgPlayer(renderer);

			break;
		default:
			break;
		}
	}
}
void PlayerObj::DoPlayer(Map& mapdata) {
	xval = 0;
	yval += GRAVITY_SPEED;

	if (yval >= MAX_FALL_SPEED) {
		yval = MAX_FALL_SPEED;
	}
	if (input_type.left == 1) {
		xval -= PLAYER_SPEED;
	}
	if (input_type.right == 1) {
		xval += PLAYER_SPEED;
	}
	if (input_type.jump == 1) {
		if (onground==true) {
			yval -= JUMP_VAL;
		}
		onground = false;

		input_type.jump = 0;
	}

	CheckToMap(mapdata);
}
void PlayerObj::CheckToMap(Map& mapdata) {
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;


	//check horizontal  
	int height_min = (heightframe * 3 < TILE_SIZE ? heightframe * 3 : TILE_SIZE); 

	x1 = (xpos+xval+15)/TILE_SIZE;
	x2 = (xpos + xval + widthframe*3 -10)/ TILE_SIZE;

	y1 = (ypos+20) / TILE_SIZE;
	y2 = (ypos + height_min +20) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAP_MAP_X && y1 >= 0 && y2 < MAP_MAP_Y) {
		if (xval > 0) {
			if (mapdata.tile[y1][x2] != BLANK_TILE|| mapdata.tile[y2][x2]!=BLANK_TILE) {
				xpos = (x2) * TILE_SIZE+10;
				xpos -= widthframe*3-10;
				xval = 0;
			}
		}
		else if (xval < 0) {
			if (mapdata.tile[y1][x1] != BLANK_TILE || mapdata.tile[y2][x1] != BLANK_TILE) {
				xpos = (x1) * TILE_SIZE+15;
				xval = 0;
			}
		}
	}
	//check vertical
	int width_min = widthframe*3< TILE_SIZE ? widthframe*3 : TILE_SIZE;
	x1 = (xpos+20) / TILE_SIZE;
	x2 = (xpos + width_min+20) / TILE_SIZE;

	y1 = (ypos + yval+15) / TILE_SIZE;
	y2 = (ypos + yval + heightframe*3 -17) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAP_MAP_X && y1 >= 0 && y2 < MAP_MAP_Y) {
		if (yval > 0) {
			if (mapdata.tile[y2][x1] != BLANK_TILE || mapdata.tile[y2][x2] != BLANK_TILE) {
				ypos = y2 * TILE_SIZE;
				ypos -= heightframe*3-17;
				yval = 0;
				onground = true;
			}
		}
		else if (yval < 0) {
			if (mapdata.tile[y1][x1] != BLANK_TILE || mapdata.tile[y1][x2] != BLANK_TILE) {
				ypos = (y1) * TILE_SIZE+10;

				yval = 0;
			}
		}
	}


	xpos += xval;
	ypos += yval;
	if (xpos < 0) {
		xpos = 0;
	}
	else if ((xpos + widthframe*3) > mapdata.maxx) {
		xpos = mapdata.maxx - widthframe*3 -1;
	}

	if (ypos < 0) {
		ypos = 0;
	}
	
}
void PlayerObj::UpdateImgPlayer(SDL_Renderer* des) {
	if (onground) {
		if (status == WALK_LEFT) {
			LoadImg("assets/player1left.png", des);
		}
		else if (status == WALK_RIGHT) {
			LoadImg("assets/player1.png", des);
		}
		else if (status == STAY_LEFT && input_type.jump == 0) {
			LoadImg("assets/stayleft.png",des);
		}
		else if (status == STAY_RIGHT && input_type.jump == 0) {
			LoadImg("assets/stayright.png",des);
		}
	}
	else {
		if (status == WALK_LEFT) {
			LoadImg("assets/player1left.png", des);
		}
		else if (status == WALK_RIGHT) {
			LoadImg("assets/player1.png", des);
		}
	}

}