#include "fs.hpp"
#include <unistd.h>
#include <fstream>
#include <sstream>

int openFromSave(char *path)
{
    FileSystem fs(path);
    char* file = (char*)"fichier1111111";
    auto fd = fs.open(file);
    auto stat = fs.stat(file);
    auto ptr = new char[stat.size];
    std::cout << "size read = " << fs.read(fd, ptr, stat.size);
    write(1, (char*)"salut\n", 6);
    write(1, ptr, stat.size);
    // std::cout << stat.size << " " << stat.block << std::endl;
    return 0;
}

int main(int ac, char **av)
{
    if (av[1] != nullptr)
        return openFromSave(av[1]);
    FileSystem fs((vd_size_t)65535);

    std::ifstream file("file.txt");
    std::stringstream buff;
    if (!file.is_open())
        return -1;
    buff << file.rdbuf();

    fs.create((char*)".", (char*)"fichier1111111");
    fs.create((char*)".", (char*)"fichier2222222");
    fs.create((char*)".", (char*)"fichier3");
    fs.create((char*)".", (char*)"fichier4");
    fs.create((char*)".", (char*)"fichier5");
    fs.create((char*)".", (char*)"fichier6");
    fs.create((char*)".", (char*)"fichier7");
    fs.create((char*)".", (char*)"fichier8");
    fs.create((char*)".", (char*)"fichier9");
    auto fd = fs.open((char*)"fichier1111111");
    fs.open((char*)"fichier2222222");
    fs.open((char*)"fichier3");
    fs.write(fd, buff.str().data(), buff.str().length());
    // fs.create((char*)"fichier9");
    // fs.debug();
    fs.save((char*)"save.data");
    return 0;
}