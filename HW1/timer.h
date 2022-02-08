#include <iostream>
#include <chrono>
// typedef std::cout out;

class Timer {
public:
    Timer(const char* const f_name) : func_name_(f_name){
        start_ = std::chrono::high_resolution_clock::now();
    }

    ~Timer() {
        end_ = std::chrono::high_resolution_clock::now();
	    duration_ = end_ - start_;
        float ms = duration_.count() * 1000.0f;
        
        std::cout<<func_name_<<" duration: "<<ms << "ms " << std::endl;
    }

private:
    const char* const func_name_;
    std::chrono::time_point<std::chrono::high_resolution_clock> start_, end_;
	std::chrono::duration<float> duration_;
};
