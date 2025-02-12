#ifndef FIBONACCIGENERATOR_H
#define FIBONACCIGENERATOR_H

#include <vector>
#include <stdexcept>
#include <sstream>
#include <limits>
#include <string>
#include <iostream>

namespace Industrial {

class FibonacciException : public std::exception {
public:
    explicit FibonacciException(const std::string& msg) : message(msg) {}
    virtual ~FibonacciException() throw() {}
    virtual const char* what() const throw() {
        return message.c_str();
    }
private:
    std::string message;
};

class ILogger {
public:
    virtual ~ILogger() {}
    virtual void log(const std::string& message) = 0;
};

class DefaultLogger : public ILogger {
public:
    virtual void log(const std::string& message) {
        std::cerr << message << std::endl;
    }
};

template<typename T>
class FibonacciGenerator {
public:
    explicit FibonacciGenerator(ILogger* logger = 0) : logger_(logger) {}

    std::vector<T> generate(size_t n) {
        if(logger_) logger_->log("Начало генерации последовательности Фибоначчи.");
        std::vector<T> sequence;
        if(n == 0) return sequence;
        sequence.push_back(static_cast<T>(0));
        if(n == 1) return sequence;
        sequence.push_back(static_cast<T>(1));
        for(size_t i = 2; i < n; ++i) {
            T next = computeNext(sequence[i-2], sequence[i-1]);
            if(sequence[i-1] > 0 && next < sequence[i-1]) {
                std::ostringstream oss;
                oss << "Обнаружено переполнение на позиции " << i;
                throw FibonacciException(oss.str());
            }
            sequence.push_back(next);
        }
        if(logger_) logger_->log("Завершение генерации последовательности Фибоначчи.");
        return sequence;
    }

protected:
    virtual T computeNext(const T& a, const T& b) {
        if(logger_) logger_->log("Вычисление следующего числа Фибоначчи.");
        if(std::numeric_limits<T>::max() - b < a) {
            std::ostringstream oss;
            oss << "Ошибка переполнения: невозможно вычислить " << a << " + " << b;
            throw FibonacciException(oss.str());
        }
        return a + b;
    }

private:
    ILogger* logger_;

#ifdef UNIT_TEST
    #include <gtest/gtest_prod.h>
    FRIEND_TEST(FibonacciGeneratorTest, TestComputeNext);
#endif
};

} 

#endif 
