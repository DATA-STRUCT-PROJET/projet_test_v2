#include "prompt.hpp"
#include <sstream>
#include <string>
#include <iostream>
#include <algorithm>

PromptCommand::PromptCommand(PromptCommandEnum type, std::vector<std::string> args) : type(type), args(args)
{
}

PromptCommandEnum PromptCommand::getType()
{
	return type;
}

const std::vector<std::string>& PromptCommand::getArgs()
{
	return args;
}

Prompt::Prompt()
{
}

Prompt::~Prompt()
{
}

PromptCommandResultEnum Prompt::process(PromptCommand command)
{
	switch (command.getType()) {
	case CD:
		// TODO(ehdgks0627): Implement CD
		break;
	case LS:
		// TODO(ehdgks0627): Implement LS
		break;
	case TREE:
		// TODO(ehdgks0627): Implement TREE
		break;
	case CAT:
		// TODO(ehdgks0627): Implement CAT
		break;
	case TOUCH:
		// TODO(ehdgks0627): Implement TOUCH
		break;
	case RMDIR:
		// TODO(ehdgks0627): Implement RMDIR
		break;
	case RM:
		// TODO(ehdgks0627): Implement RM
		break;
	case MKDIR:
		// TODO(ehdgks0627): Implement MKDIR
		break;
	case ECHO:
		// TODO(ehdgks0627): Implement ECHO
		break;
    default:
        return PromptCommandResultEnum::FAILURE;
	}
}

PromptCommand PomprtCommandPraser::parse(std::string line)
{
	std::istringstream ss(line);
	std::string token;
	std::vector<std::string> args;
	PromptCommandEnum type = NONE;
	while (std::getline(ss, token, ' ')) {
		args.push_back(token);
	}
	if (args.size() == 0) {
		throw; // TODO(ehdgks0627): Handle error
	}

	// Make command lower
	std::string command = args.at(0);
	std::transform(command.begin(), command.end(), command.begin(),
		[](unsigned char c) { return std::tolower(c); });


	if (command == "cd") {
		type = CD;
	}
	else if (command == "ls") {
		type = LS;
	} 
	else if (command == "tree") {
		type = TREE;
	}
	else if (command == "cat") {
		type = CAT;
	}
	else if (command == "touch") {
		type = TOUCH;
	}
	else if (command == "rmdir") {
		type = RMDIR;
	}
	else if (command == "rm") {
		type = RM;
	}
	else if (command == "mkdir") {
		type = MKDIR;
	}
	else if (command == "echo") {
		type = ECHO;
	}
	args.erase(args.begin());

	return PromptCommand(type, args);
}
