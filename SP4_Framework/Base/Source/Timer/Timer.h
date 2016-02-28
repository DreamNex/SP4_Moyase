#ifndef TIMER_H
#define TIMER_H

class Timer
{
private:
	float duration;
	float dur_Copy;
	bool active;
	bool loop;
public:
	Timer(float duration);
	Timer();
	~Timer();

	float GetDuration();
	void SetDuration(float duration);

	bool GetActive();
	void Start();
	void Stop();

	bool Update(float dt);

};

#endif

