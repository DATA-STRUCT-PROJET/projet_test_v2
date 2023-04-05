#pragma once
#include <unistd.h>
#include "vd.hpp"
#include <map>
#include <list>

struct fileData_t {
    std::string path;
    std::string name;
    bool is_directory = false;
    std::list<vd_size_t> blocks; // size == 1 for directory
    std::list<fileData_t> files; // only used for directory
    vd_size_t size = 0; // only used for files
};

class FileSystem
{
    #define MAGICBLOCK_BLOCK 0
    public:
        FileSystem(vd_size_t nb_block, vd_size_t block_len = 4);
        FileSystem(char *path);
        ~FileSystem() = default;

        bool create(char *path, char *filename, bool isDirectory = false);
        vd_size_t open(char *path); // return fd?? // path is just a filename for now
        void close(char *path);
        void close(vd_size_t fd);
        
        vd_size_t write(vd_size_t fd, void *ptr, vd_size_t len);
        vd_size_t read(vd_size_t fd, void *ptr, vd_size_t len);
        fileData_t stat(char *path);

        void debug();
        bool save(char *path) {
            __registerMagicBlock();
            return vd.__save(path);
        }

    private:
        void __registerMagicBlock();
        void __getMagicBlock();

        bool __registerFile(char *path, fileData_t file);
        fileData_t *__getFileFromPath(char *path);
        fileData_t *__getFileFromPath(std::string path, fileData_t*);

        vd_size_t __getBlock();
        vd_size_t __newFd();
        fileData_t __getFileFromFD(vd_size_t fd);

        void __printFileStat(const fileData_t&);

    private:
        vd_size_t _nextBlock = 1; // MAGICBLOCK_BLOCK + 1 the def of MAGICBLOCK_BLOCK dosent make any sense cuz is must be equal to 0 in every circumstance
        // vd_size_t _nb_max_files;
        virtualDisk vd;
        MagicBlock_t _magicBlock;
        std::map<vd_size_t, fileData_t> _fds;
};