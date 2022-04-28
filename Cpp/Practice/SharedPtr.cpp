#include<iostream>

using namespace std;

template <class T>
class SharedPtr
{
    private:
    T* _ptr;
    mutable int* _counter;
    void dispose()
    {
        if(--(*_counter)==0)
        {
            delete _ptr;
            delete _counter;
        }
    }
public:

    explicit SharedPtr(T* p = nullptr):_ptr(p),_counter(new int(1)){ if(ptr) {}
    SharedPtr(SharedPtr<T>& ptr)
    {
        _ptr=ptr._ptr;
        _counter=ptr._counter;
        (*_counter)++;
    }
    
    SharedPtr<T>& operator=(const SharedPtr<T>& ptr)
    {
    }



};