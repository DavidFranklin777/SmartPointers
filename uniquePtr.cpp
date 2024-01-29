#include <iostream>

using namespace std;

template <typename T>

class uniquePtr
{
    public:
    uniquePtr(T* ptr = nullptr): pointer(ptr)
    {
        cout << "Constructor" << endl;
    }

    // Copy constructor must be deleted
    uniquePtr(const uniquePtr<T>& uniqueObj) = delete;

    // Copy assignment operator must be deleted
    uniquePtr& operator=(const uniquePtr<T>& uniqueObj) = delete;


    // Move constructor
    uniquePtr(uniquePtr<T>&& uniqueObj)
    {
        cout << "Move constructor" << endl;
        this->pointer = uniqueObj.pointer;
        uniqueObj.pointer = nullptr;
    }

    // Move assignment operator
    uniquePtr& operator=(uniquePtr<T>&& uniqueObj)
    {
        if(this != &uniqueObj)
        {
            if (this->pointer)
            {
                delete (this->pointer);               
            }
            cout << "Move assignment " << endl;
            this->pointer = uniqueObj.pointer;
            uniqueObj.pointer = nullptr;
        }
        return *this;
    }

    // Arrow operator overloading
    // Since uniquePtr object must be treated like a pointer, we ensure that we can use an arrow operator
    // Note that the arrow operator basically returns this pointer after overloading
    uniquePtr* operator->()
    {
        cout << "Arrow operator " << endl;
        return (this);
    }

    // If we dereference uniquePtr, you get the data pointed by this->pointer
    T& operator*()
    {
        cout << "Dereferencing pointer " << endl;
        return *(this->pointer);
    }

    // Dangerous function, since it returns the pointer
    // Whoever uses it must not assume ownership and perform operations such as delete, if done, the program encounters undefined behavior
    T* get()
    {
        cout << "Getting pointer" << endl;
        return this->pointer;
    }

    // A function to reset the uniquePtr
    void reset(T* ptr = nullptr)
    {
        if(this->pointer)
        {
            delete (this->pointer);
        }

        cout << "Resetting " << endl;   

        this->pointer = ptr;
    }

    ~uniquePtr()
    {
        cout << "Destructor " << endl;
        if(this->pointer)
        {
            delete (this->pointer);
            this->pointer = nullptr;
        }
    }

    private:
    T* pointer;

};


int main()
{

    uniquePtr<int> ptr1(new int(5));
    //uniquePtr<int> ptr2(ptr1);
    //uniquePtr<int> ptr3 = ptr1;

    uniquePtr<int> ptr4 = move(ptr1);
    uniquePtr<int> ptr5(move(ptr4));
    uniquePtr<int> ptr6;
    ptr6 = move(ptr5);

    int *test = ptr6->get();

    cout << *ptr6 << endl;

    cout << "Unique Pointer " << endl;
    return 0;
}