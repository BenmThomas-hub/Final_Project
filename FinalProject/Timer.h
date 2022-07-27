#include <iostream>
#include <string>
#include <chrono>

class Timer {
	private:
		std::chrono::time_point<std::chrono::system_clock> start_point;
		std::chrono::time_point<std::chrono::system_clock> end_point;
		double duration;

	public:
		Timer();              //constructor
		~Timer();             //deconstructor
		void start();         //starts the timer
		void stop();          //ends the timer
		double getDuration(); //calculates the duration of the timer in nanoseconds
};

Timer::Timer() {}

Timer::~Timer() {}

void Timer::start() {
	start_point = std::chrono::system_clock::now();
}

void Timer::stop() {
	end_point = std::chrono::system_clock::now();
}

double Timer::getDuration() {
	
	duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_point - start_point).count();
	
	//duration = duration / 1000;
	
	return duration;
}
