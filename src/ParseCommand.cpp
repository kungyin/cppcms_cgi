/*
 * ParseCommand.cpp
 *
 *  Created on: 2015年3月13日
 *      Author: ian
 */

#include "ParseCommand.h"
//#include <cgicc/CgiDefs.h>
//#include <cgicc/Cgicc.h>
//#include <cgicc/HTTPHTMLHeader.h>
//#include <cgicc/HTMLClasses.h>

#include <iostream>

using namespace std;
//using namespace cgicc;

char CGI_COMMANDS[][255] = {
	"cgi_Volume_Status"
};

//const string CGI_CMD_NAME = "cmd";

ParseCommand::ParseCommand(string cmd)
	: iCmdNumber(-1)
{
	if( !cmd.empty() ) {
		int cgiCommandNum = sizeof(CGI_COMMANDS)/sizeof(CGI_COMMANDS[0]);
		for(int i = 0; i < cgiCommandNum; i++) {
			string s(CGI_COMMANDS[i]);
			if(s.compare(cmd) == 0) {
				iCmdNumber = i;
			}
		}
	}
	else {
		cout << "No text entered for first name" << endl;
	}
}

ParseCommand::~ParseCommand() {
}

CGI_COMMAND ParseCommand::getCGICmd() {
	if(iCmdNumber == -1)
		return CMD_NONE;

	return static_cast<CGI_COMMAND>(iCmdNumber+1);
	//switch()

}
