#include <mutex>
#include <memory>

class Singleton{
public:
    static std::shared_ptr<Singleton> get_instance(){
        if (s_inst_==nullptr){
            std::lock_guard<std::mutex> lock(mutex_);
            if (s_inst_ == nullptr)
            {
                s_inst_ = std::shared_ptr<Singleton>(new Singleton);
            }
        }
        return s_inst_;
    }

private:
    Singleton(){};
    Singleton(const Singleton& s);
    const Singleton& operator=(const Singleton& s);
    static std::shared_ptr<Singleton> s_inst_;
    static std::mutex mutex_;
};
std::shared_ptr<Singleton> Singleton::s_inst_ = nullptr;
std::mutex Singleton::mutex_;

int main(){
    std::shared_ptr<Singleton> s = Singleton::get_instance();
}