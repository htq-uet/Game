#pragma once
class ImpTimer
{
public:
	ImpTimer();
	~ImpTimer();


	void start();
	void stop();
	void paused();
	void unpaused();

	int get_tick();

	bool is_paused();
	bool is_started();

private:
	int start_tick;
	int pause_tick;

	bool is_pause;
	bool is_start;
};

