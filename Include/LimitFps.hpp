#include <chrono>
#include <cstddef>
#include <thread>

class LimitFps
{
  public:
    LimitFps(size_t max_fps) : m_MinElapsedTime(1'000'000'000 / max_fps)
    {
        m_Start = std::chrono::high_resolution_clock::now();
    }
    ~LimitFps()
    {
        const auto end = std::chrono::high_resolution_clock::now();
        const auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - m_Start);
        if (elapsed < m_MinElapsedTime)
        {
            std::this_thread::sleep_for(m_MinElapsedTime - elapsed);
        }
    }

  private:
    std::chrono::nanoseconds m_MinElapsedTime;
    std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> m_Start;
};
