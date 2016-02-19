#pragma once
class Timer
{
private:
	float countdown;
	float countdowncopy;
	bool active;

public:
	Timer(float countdown);
	Timer();
	~Timer();

	float GetTimer();
	void SetTimer(float countdown);

	bool GetActive();
	void Start();
	void Stop();

	bool Update(float dt);

};

