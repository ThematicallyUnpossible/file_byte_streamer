#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>

#define G_OPERATION_SIZE 256

int main()
{

    std::cout << "Source file : ";
    std::string source{};
    std::getline(std::cin, source);

    std::cout << "Target file : ";
    std::string target{};
    std::getline(std::cin, target);

    int source_fd = open(source.c_str(), O_RDONLY);
    if(source_fd == -1){
        std::cerr << "- unable to get " <<  source << "'s file descriptor.\n";
        return 1;
    }

    int target_fd = open(target.c_str(), O_WRONLY);
    if(target_fd == -1){
        std::cerr << "- unable to get " << target <<  "'s file descriptor.\n";
        return 1;
    }

    char BUFFER[ G_OPERATION_SIZE ]{};
    int BYTEREAD{};
    int BYTEWRITE{};

    auto beginning = std::chrono::high_resolution_clock::now();

    while( (BYTEREAD = read(source_fd, BUFFER, G_OPERATION_SIZE )) != -1 ){
        if(BYTEREAD == 0){
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed {end - beginning};
            std::cout << "task finished in ";
            std::cout << std::fixed << std::setprecision(4);
            std::cout << elapsed.count() << "s\n";
            break;
        }
        else if(BYTEREAD > 0){
            BYTEWRITE = write(target_fd, BUFFER, BYTEREAD);
            std::cout << "- " << BYTEWRITE << " bytes written.\n";
            if(BYTEWRITE == -1)
            {
                std::cerr << "- write error\n";
                return 2;
            }
        }
    }
    if(BYTEREAD == -1){
        std::cerr << "- unable to read source\n";
        return 2;
    }



    close(source_fd);
    close(target_fd);
    return 0;
}
