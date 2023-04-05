#pragma once
#include <iostream>
#include <string>
#include <vector>


enum PromptCommandEnum
{
    CD,
    LS,
    TREE,
    CAT,
    TOUCH,
    RMDIR,
    RM,
    MKDIR,
    ECHO,
    NONE
};

class PromptCommand
{
public:
    PromptCommand(PromptCommandEnum type, std::vector<std::string> args);

    PromptCommandEnum getType();
    const std::vector<std::string>& getArgs();
private:
    PromptCommandEnum type;
    std::vector<std::string> args;
};

enum PromptCommandResultEnum
{
    ERROR,
    FAILURE,
    SUCCESS,
};

class PomprtCommandPraser
{
public:
    static PromptCommand parse(std::string line);
};

class Prompt
{
public:
    Prompt();
    ~Prompt();

    PromptCommandResultEnum process(PromptCommand command);
private:
    std::string currentDirectory;
};