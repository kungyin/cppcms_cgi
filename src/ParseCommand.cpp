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

const char CGI_PARA_COMMANDS[][255] = {
	"cgi_Volume_Status",
	"cgi_FMT_Get_Sync_State",
	"cgi_FMT_Get_Auto_Rebuild_Info",
	"cgi_AJAXPlorer_Stop",
	"cgi_FMT_Create_DiskMGR",
	"cgi_SMART_HD_List",
	"SMART_XML_Create_Test_List",
	"SMART_Schedule_List",
	"SMART_Get_Test_Status",
	"SMART_Set_Schedule",
	"SMART_Test_Start",
	"ScanDisk_info",
	"cgi_Check_Disk_Remount_State",
	"ScanDisk_run_e2fsck",
	"ScanDisk_Finish",

	/**** Home Page ****/
	"cgi_is_build_in_language",
	"cgi_get_user_language",
	"cgi_get_ssl_info",
	"ui_check_wto",
	"cgi_get_fw_status",
	"login",
	"logout"

};

//const string CGI_CMD_NAME = "cmd";

ParseCommand::ParseCommand(string cmd)
	: iCmdNumber(-1)
{
	if( !cmd.empty() ) {
		int cgiCommandNum = sizeof(CGI_PARA_COMMANDS)/sizeof(CGI_PARA_COMMANDS[0]);
		for(int i = 0; i < cgiCommandNum; i++) {
			string s(CGI_PARA_COMMANDS[i]);
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
}
