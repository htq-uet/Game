#include "ImpTimer.h"
#include "CommonFunction.h"


ImpTimer::ImpTimer() {
	start_tick = 0;
	pause_tick = 0;
	is_pause = false;
	is_start = false;

}
ImpTimer::~ImpTimer() {

}
void ImpTimer::start() {
	is_start = true;
	is_pause = false;
	start_tick = SDL_GetTicks();
}

void ImpTimer::stop() {
	is_start = false;
	is_pause = false;
}

void ImpTimer::paused() {
	if (is_start = true) {
		is_pause = true;
		pause_tick = SDL_GetTicks() - start_tick;
	}
}

void ImpTimer::unpaused() {
	if (is_pause == true) {
		is_pause = false;
		start_tick = SDL_GetTicks() - pause_tick;
		pause_tick = 0;
	}
}
int ImpTimer::get_tick() {
	if (is_start == true) {
		if (is_pause == true) {
			return pause_tick;
		}
		else { return SDL_GetTicks() - start_tick; }
	}
	return 0;
}
bool ImpTimer::is_started() {
	return is_start;
}
bool ImpTimer::is_paused() {
	return is_pause;
}
