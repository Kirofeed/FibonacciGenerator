#include <iostream>
#include <sstream>
#include "FibonacciGenerator.h"

using namespace Industrial;

int main(int argc, char** argv) {
    size_t n = 10;
    if(argc > 1) {
        std::istringstream iss(argv[1]);
        if(!(iss >> n)) {
            std::cerr << "Некорректное значение: " << argv[1] << std::endl;
            return 1;
        }
    }
    DefaultLogger logger;
    FibonacciGenerator<int> fibGen(&logger);
    try {
        std::vector<int> sequence = fibGen.generate(n);
        std::cout << "Первые " << n << " чисел Фибоначчи:" << std::endl;
        for(size_t i = 0; i < sequence.size(); ++i) {
            std::cout << sequence[i] << " ";
        }
        std::cout << std::endl;
    } catch(const FibonacciException& ex) {
        std::cerr << "Ошибка генерации последовательности: " << ex.what() << std::endl;
        return 1;
    }
    return 0;
}
