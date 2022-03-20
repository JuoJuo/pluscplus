#include<iostream>
#include<thread>

static bool s_Finished = false;

void DoWork() {

  using namespace std::literals::chrono_literals;

  std::cout << "start thread id=" << std::this_thread::get_id;

  while (!s_Finished)
  {
    std::cout << "Working...\n";
    std::this_thread::sleep_for(1s);
  }
}

int main025() {

  std::thread m_worker(DoWork);
  std::cin.get();

  s_Finished = true;

  m_worker.join();
  std::cout << "Finished" << std::endl;

  std::cout << "start thread id=" << std::this_thread::get_id;
  std::cin.get();
  return 1;
}
