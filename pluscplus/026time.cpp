#include<iostream>
#include<chrono>
#include<thread>

struct Timer {

  std::chrono::time_point<std::chrono::steady_clock> start, end;
  std::chrono::duration<float> duration;

  Timer() {
    start = std::chrono::high_resolution_clock::now();
  }
  ~Timer()
  {
    end = std::chrono::high_resolution_clock::now();

    duration = end - start;

    float ms = duration.count() * 1000.0f;
    std::cout << "Timer took " << ms << " ms" << std::endl;
  }
};


int main027() {

  Timer timer;

  using namespace std::literals::chrono_literals;

  std::this_thread::sleep_for(1s);

  return 1;

}
