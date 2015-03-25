#ifndef _PARSE_COMMAND_
#define _PARSE_COMMAND_

#include <string>
#include "CommandDefine.h"


class ParseCommand {
public:
	ParseCommand(std::string);
	virtual ~ParseCommand();

	CGI_COMMAND getCGICmd();
	int getCmdNumber() { return iCmdNumber; }

private:

	int iCmdNumber;
};

#endif
