#include <atomic>

template<typename T>
class my_shared_ptr
{
public:
    my_shared_ptr(T* p, int* ref_cnt_addr=nullptr){
        if (ref_cnt_addr==nullptr){
            c_ = new int;
            *c_ = 0;
        }else{
            c_ = ref_cnt_addr;
        }

        *c_ ++;
        p_ = p;
    }

    T* get(){
        return p_;
    }

    int* cnt(){
        return c_;
    }
    
    my_shared_ptr(const my_shared_ptr<T>& src){
        p_ = src.get();
        c_ = src.cnt();
        *c_++;
    }

    my_shared_ptr<T> operator=(const my_shared_ptr<T>& src){
        return my_shared_ptr<T>(src.get(),src.cnt);
    }

    ~my_shared_ptr(){
        *c_--;
        if (*c_==0){
            delete p_;
        }
    }

private:
    int* c_ = nullptr;
    T* p_ = nullptr;
};