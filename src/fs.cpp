#include "fs.hpp"
#include <iostream>
#include <sstream>

std::vector<std::string> split (const std::string &s, char delim) {
    std::vector<std::string> result;
    std::stringstream ss (s);
    std::string item;

    while (getline (ss, item, delim)) {
        result.push_back (item);
    }

    return result;
}

FileSystem::FileSystem(vd_size_t nb_block, vd_size_t block_len)
    : vd(virtualDisk(nb_block, block_len))
{
    std::cout << nb_block << " " << block_len * 1024 << std::endl;
    _magicBlock._nb_blocks_max = nb_block;
    _magicBlock._blocks_len = block_len * 1024;
    _magicBlock._nb_blocks_used = 0;
    // _nb_max_files = nb_block - 1;
    __registerMagicBlock();
}

FileSystem::FileSystem(char *path) : vd(virtualDisk(path))
{
    __getMagicBlock();
    // _nb_max_files = _magicBlock._nb_block - 1;
    // debug();
}

fileData_t *FileSystem::__getFileFromPath(std::string path, fileData_t* dir)
{
    if (dir == nullptr) return nullptr;

    for (auto &it : dir->files) {
        if (!it.is_directory) continue;
        if (it.name == path) return &it;
    }
    return nullptr;
}

fileData_t *FileSystem::__getFileFromPath(char *path)
{
    auto paths = split(path, '/');
    if (paths.size() == 0) return nullptr;
    fileData_t *currentDir = (fileData_t*)vd.__getBlock(1);
    
    for (auto &it : paths) {
        currentDir = __getFileFromPath(it, currentDir);
    }
    return currentDir;
}

bool FileSystem::__registerFile(char *path, fileData_t file)
{
    return false;
}

bool FileSystem::create(char *path, char *filename, bool isDirectory)
{
    fileData_t fileData;

    vd_size_t block = __getBlock();
    if (block == -1)
        throw std::runtime_error("failed getting a new block when creating a file");

    fileData.path = path;
    fileData.name = filename;
    fileData.is_directory = isDirectory;
    fileData.blocks.push_back(block);

    // __registerMagicBlock();
    return __registerFile(path, fileData);
}

vd_size_t FileSystem::open(char *path)
{
    // for (auto it : _magicBlock.files) {
    //     if (strcmp(it.name, path) == 0) {
    //         auto fd = __newFd();
    //         _fds[fd] = it;
    //         return fd;
    //     }
    // }
    // std::cerr << "fd failed for file:\t " << path << std::endl;
    return -1;
}

void FileSystem::debug()
{
    // std::cout << "magic block:" << std::endl;
    // std::cout << "nb block:\t" << _magicBlock._nb_block << std::endl;
    // std::cout << "blocks_len :\t" << _magicBlock._blocks_len << std::endl;
    // std::cout << "nb_files :\t" << _magicBlock.nb_files << std::endl;
    // std::cout << "nb file max:\t" << _nb_max_files << std::endl;

    // for (const auto &it : _magicBlock.files)
    //     __printFileStat(it);
}

vd_size_t FileSystem::write(vd_size_t fd, void *ptr, vd_size_t len)
{
    // fileData_t file = __getFileFromFD(fd);

    // if (file.block == (vd_size_t)-1) return 0;

    // if (len + sizeof(fileData_t) > _magicBlock._blocks_len)
    //     len = _magicBlock._blocks_len - sizeof(fileData_t);
    // file.size = len;

    // vd.__write(file.block, &file, sizeof(fileData_t));
    // vd.__write(file.block, ptr, len, sizeof(fileData_t));

    // for (auto &it : _magicBlock.files) {
    //     if (it.block == file.block)
    //         it = file;
    // }
    // return len;
    return -1;
}


vd_size_t FileSystem::read(vd_size_t fd, void *ptr, vd_size_t len)
{
    // fileData_t file = __getFileFromFD(fd);

    // if (file.block == (vd_size_t)-1) return 0;

    // if (len + sizeof(fileData_t) > _magicBlock._blocks_len)
    //     len = _magicBlock._blocks_len - sizeof(fileData_t);

    // vd.__read(file.block, ptr, len, sizeof(fileData_t));

    // return len;
    return -1;
}

fileData_t FileSystem::stat(char *path)
{
    // for (auto &it : _magicBlock.files) {
    //     if (strcmp(it.name, path) == 0) {
    //         return it;
    //     }
    // }
    // throw std::runtime_error("file not found");
    fileData_t file;
    return file;
}

/*------------------------------------------------------------------*/

fileData_t FileSystem::__getFileFromFD(vd_size_t fd)
{
    // fileData_t file;
    // try {
    //     file = _fds.at(fd);
    // } catch (std::out_of_range &e) {
    //     file.block = -1;
    // }
    // return file;
    fileData_t file;
    return file;
}

vd_size_t FileSystem::__newFd()
{
    // if (_fds.size() == 0)
    //     return 3; // 0,1,2 are use by the system(its not relate to our file descriptor but why not c:)
    
    // for (auto key = _fds.begin(), it = _fds.begin().operator++(); it != _fds.end(); it++, key++)
    //     if (key->first + 1 != it->first)
    //         return key->first + 1;

    // return _fds.rbegin()->first + 1;
    return -1;
}

void FileSystem::__registerMagicBlock()
{
    vd.__write(MAGICBLOCK_BLOCK, &_magicBlock, sizeof(vd_size_t) * 3);
    // vd.__write(MAGICBLOCK_BLOCK, _magicBlock.files.data(), _magicBlock.files.size() * sizeof(fileData_t), sizeof(vd_size_t) * 3);
}

void FileSystem::__getMagicBlock()
{
    vd.__read(MAGICBLOCK_BLOCK, &_magicBlock, sizeof(vd_size_t) * 3);
    // _magicBlock.files.resize( _magicBlock.nb_files);
    // vd.__read(MAGICBLOCK_BLOCK, _magicBlock.files.data(), _magicBlock.nb_files * sizeof(fileData_t), sizeof(vd_size_t) * 3);
}

vd_size_t FileSystem::__getBlock()
{
    _nextBlock++;
    return _nextBlock -1;
}

void FileSystem::__printFileStat(const fileData_t &file)
{
    // std::cout << "file name=" << file.name;
    // std::cout << "\t file size=" << file.size;
    // std::cout << "\tblok used=" << file.block << std::endl;
}