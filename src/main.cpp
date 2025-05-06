#include "manager/manager.h"

int main(int argc, char* argv[]) {
    try {
        Manager().run(argc, argv);
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}