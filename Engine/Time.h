#pragma once
#include <chrono>

class Time
{
public:
	// Returns the duration of the last frame in seconds
	float DeltaTime() const { return deltaTime; } 

	// Measures time since it was last called and sets it to DeltaTime() return value;
	void Mark()
	{
		deltaTime = std::chrono::duration<float>(std::chrono::steady_clock::now() - last).count();
		last = std::chrono::steady_clock::now();
	}

	// Returns time passed since the program was started in seconds
	float TimeSinceStart() 
	{ 
		return std::chrono::duration<float>(std::chrono::steady_clock::now() - startTime).count();
	}

private:
	std::chrono::steady_clock::time_point last;
	const std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();
	float deltaTime = 0;
};