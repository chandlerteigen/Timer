/*
Programmer: Chandler Teigen
Date: 10-10-19
Notes: class T must be something like std::chrono::nanoseconds, std::chrono::microseconds etc
*/

#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <iostream>
#include <fstream>

std::ostream &operator<<(std::ostream &lhs, std::chrono::hours &rhs)
{
    lhs << rhs.count() << "hr" << std::endl;
    return lhs;
}

std::ostream &operator<<(std::ostream &lhs, std::chrono::minutes &rhs)
{
    lhs << rhs.count() << "min" << std::endl;
    return lhs;
}

std::ostream &operator<<(std::ostream &lhs, std::chrono::seconds &rhs)
{
    lhs << rhs.count() << "s" << std::endl;
    return lhs;
}

std::ostream &operator<<(std::ostream &lhs, std::chrono::milliseconds &rhs)
{
    lhs << rhs.count() << "ms" << std::endl;
    return lhs;
}

std::ostream &operator<<(std::ostream& lhs, std::chrono::microseconds &rhs)
{
    lhs << rhs.count() << "us";
    return lhs;
}

std::ostream &operator<<(std::ostream &lhs, std::chrono::nanoseconds &rhs)
{
    lhs << rhs.count() << "ns" << std::endl;
    return lhs;
}


namespace ct {

    template<class T>
    class Timer
    {
    public:
    Timer();
    ~Timer();

    T get_length();

    void start();

    void stop();

    void print_time();

    void print_time_to_file(std::ofstream &outfile);

    private:
        std::chrono::high_resolution_clock::time_point start_time, stop_time;
        T length;
    };

    template<class T>
    class Scope_Timer
    {
        public:
        Scope_Timer();

        ~Scope_Timer();

        private:
        void print_time();
        void print_time_to_file(std::ofstream &outfile);

        std::chrono::high_resolution_clock::time_point start_time, stop_time;
        T length;
    };

}

template<class T>
ct::Timer<T>::Timer()
{
    length = std::chrono::duration_cast<T> (std::chrono::high_resolution_clock::duration::zero());
}

template<class T>
ct::Timer<T>::~Timer()
{
    
}

template<class T>
T ct::Timer<T>::get_length()
{
    return length;
}

template<class T>
void ct::Timer<T>::start()
{
    start_time = std::chrono::high_resolution_clock::now();
}

template<class T>
void ct::Timer<T>::stop()
{
    stop_time = std::chrono::high_resolution_clock::now();
    auto t2 = std::chrono::time_point_cast<T> (stop_time);
    auto t1 = std::chrono::time_point_cast<T> (start_time);
    long long duration_count = t2.time_since_epoch().count() - t1.time_since_epoch().count();
    T dur(duration_count);
    length = dur;
}

template<class T>
void ct::Timer<T>::print_time()
{
    std::cout << length;
}

template<class T>
void ct::Timer<T>::print_time_to_file(std::ofstream &outfile)
{
    outfile << length;
}



/***************************************************************/

template <class T>
ct::Scope_Timer<T>::Scope_Timer()
{
    start_time = std::chrono::high_resolution_clock::now();
}

template <class T>
ct::Scope_Timer<T>::~Scope_Timer()
{
    stop_time = std::chrono::high_resolution_clock::now();
    auto t2 = std::chrono::time_point_cast<T> (stop_time);
    auto t1 = std::chrono::time_point_cast<T> (start_time);
    long long duration_count = t2.time_since_epoch().count() - t1.time_since_epoch().count();
    T dur(duration_count);
    length = dur;
    print_time();
}

template <class T>
void ct::Scope_Timer<T>::print_time()
{
    std::cout << length;
}

template <class T>
void ct::Scope_Timer<T>::print_time_to_file(std::ofstream &outfile)
{
    outfile << length;
}

#endif
