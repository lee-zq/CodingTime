#include <iostream>
#include <memory>
#include <mutex>

template <typename T>
class Singleton
{
public:
    static std::shared_ptr<T> get_instance()
    {
        static std::mutex s_mutex;
        if (s_inst_ == nullptr)
        {
            std::lock_guard<std::mutex> lock(s_mutex);
            if (s_inst_ == nullptr)
            {
                s_inst_ = std::shared_ptr<T>(new T());
            }
        }
        return s_inst_;
    }

private:
    Singleton(){};
    Singleton(const Singleton& s);
    const Singleton& operator=(const Singleton& s);
    static std::shared_ptr<T> s_inst_;
};

template <typename T>
std::shared_ptr<T> Singleton<T>::s_inst_ = nullptr;

class AIAgent
{
public:
    void run()
    {
        std::cout << "Hello" << std::endl;
    };
};

int main()
{
    std::shared_ptr<AIAgent> s = Singleton<AIAgent>::get_instance();
    s->run();
}

// AI+HPC
// 深度学习算法落地过程中涉及的模块：
// 算法(训练)-》工程部署-》上层应用
//     |           |
// 训练框架《==》推理引擎