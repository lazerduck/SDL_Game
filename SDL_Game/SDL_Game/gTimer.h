#pragma once
class gTimer
{
private:
	bool start;
public:
	float Time;
	
	gTimer(void)
	{
		start = false;
		Time = 0;
	}

	void Start()
	{
		start = true;
	}

	void Pause()
	{
		start = false;
	}

	void Stop()
	{
		start = false;
		Time = 0;
	}
	void Update(float DeltaTime)
	{
		if(start)
		{
			Time += DeltaTime;
		}
	}

	~gTimer(void)
	{
	}
};

