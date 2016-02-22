/*
 * HDConfigView.cpp
 *
 *  Created on: 2015年3月24日
 *      Author: ian
 */

#include "HDConfigView.h"
#include <iostream>
#include <libxml/parser.h>
#include <libxml/xmlsave.h>
#include <cppcms/session_interface.h>
//#include <libxml/xpath.h>
//#include <libxml/xpathInternals.h>
#include <stdio.h>

#include <booster/log.h>

//#define SIMULATOR_MODE

using namespace std;
using namespace cppcms;

const string API_PATH = "/usr/local/modules/api/";

HDConfigView::HDConfigView(http::request &req, CGI_COMMAND cmd)
	: m_cmd(cmd)
	, m_session("")
	, m_loginStatus(0)
	, m_isStrOut(false)
{
	m_pReq = &req;
	m_map = m_pReq->post_or_get();
}

HDConfigView::~HDConfigView() {
}

string HDConfigView::xmlOut() {

	string ret;

	xmlDocPtr doc = NULL;       /* document pointer */
	xmlNodePtr root_node = NULL, node = NULL, node1 = NULL;/* node pointers */
	xmlDtdPtr dtd = NULL;       /* DTD pointer */

	switch(m_cmd) {
	case CMD_VOLUME_STATUS:
		root_node = xmlOutVolumeStatus();
		break;
	case CMD_FMT_GET_SYNC_SATTE:
		root_node = xmlOutFMTGetSyncState();
		break;
	case CMD_FMT_GET_AUTO_REBUILD_INFO:
		root_node = xmlOutFMTGetAutoRebuildInfo();
		break;
	case CMD_AJAXPLORER_STOP:
		root_node = xmlOutAJAXPlorerStop();
		break;
	case CMD_FMT_CREATE_DISKMGR:
		root_node = xmlOutFMTCreateDiskMGR();
		break;
	case CMD_SMART_HD_LIST:
		root_node = xmlOutSmartHDList();
		break;
	case CMD_SMART_XML_CREATE_TEST_LIST:
		root_node = xmlOutCreateTestList();
		break;
	case CMD_SMART_SCHEDULE_LIST:
		root_node = xmlOutSmartScheduleList();
		break;
	case CMD_SMART_GET_TEST_STATUS:
		root_node = xmlOutGetTestStatus();
		break;
	case CMD_SMART_SET_SCHEDULE:
	{
		std::multimap<string, string>::iterator it = m_map.find("f_flag");
		if(it != m_map.end()) {
			string paraFlag = it->second;
			if(paraFlag.compare("1") == 0)
				root_node = xmlOutSmartSetSchedule();
			else if(paraFlag.compare("0") == 0)
				root_node = xmlOutSmartDelSchedule();
		}
	}
		break;
	case CMD_SCANDISK_INFO:
		root_node = xmlOutSmartTestStart();
		break;
	case CMD_SMART_TEST_START:
		root_node = xmlOutScanDiskInfo();
		break;
	case CMD_CHECK_DISK_REMOUNT_STATUS:
		root_node = xmlOutCheckDiskRemountState();
		break;
	case CMD_SCANDISK_RUN_E2FSCK:
		root_node = xmlOutScanDiskRunE2fsck();
		break;
	case CMD_SCANDISK_FINISH:
		root_node = xmlOutScanDiskFinish();
		break;

	case CMD_CGI_IS_BUILD_IN_LANGUAGE:
		root_node = xmlOutIsBuildInLanguage();
		break;
	case CMD_CGI_GET_USER_LANGUAGE:
		root_node = xmlOutGetUserLanguage();
		break;
	case CMD_CGI_GET_SSL_INFO:
		root_node = xmlOutGetSslInfo();
		break;
	case CMD_UI_CHECK_WTO:
		ret = strOutUICheckWto();
		m_isStrOut = true;
		break;
	case CMD_FW_STATUS:
		ret = strOutFWStatus();
		m_isStrOut = true;
		break;

	case CMD_LOGIN:
		ret = strOutLogin();
		m_isStrOut = true;
		break;
	case CMD_LOGOUT:
		ret = strOutLogout();
		m_isStrOut = true;
		break;
	case CMD_NONE:
	default:
		break;
	}

	LIBXML_TEST_VERSION;

	doc = xmlNewDoc(BAD_CAST "1.0");

	xmlDocSetRootElement(doc, root_node);
	/*
	 *      * Dumping document to stdio or file
	 */
	//xmlSaveFormatFileEnc("-", doc, "UTF-8", 2);

	if(root_node != NULL) {
		xmlBufferPtr pBuff = xmlBufferCreate();
		xmlNodeDump(pBuff, doc, root_node, 2, 2);
		ret += (char *) pBuff->content;
		xmlBufferFree(pBuff);
	}

//	xmlSaveCtxtPtr ctxt;
//	ctxt = xmlSaveToFilename( "-", "UTF-8", XML_SAVE_FORMAT | XML_SAVE_NO_DECL);
//	if (ctxt != NULL) {
//		if (xmlSaveDoc(ctxt, doc) < 0) {
//		}
//		xmlSaveClose(ctxt);
//	}

	xmlFreeDoc(doc);

	xmlCleanupParser();

	return ret;
}

string HDConfigView::getAPIStdOut(string apiCmd) {
	char buff[256];
	memset(buff, 0, sizeof(buff));
	FILE *fd = popen(apiCmd.c_str(), "r");
	while((fgets(buff, 256, fd)) != NULL) {
	}
	pclose(fd);

	return string(buff);
}

vector<string> HDConfigView::split(string str) {

	vector<string> ret;
	string delimiters = ",";
	size_t current;
	size_t next = -1;
	do
	{
		current = next + 1;
		next = str.find_first_of( delimiters, current );
		ret.push_back(str.substr(current, next - current));
	}
	while (next != string::npos);

	return ret;
}

xmlNodePtr HDConfigView::xmlOutVolumeStatus() {
	std::multimap<string, string>::iterator it;
	string paraFlag;

	it = m_map.find("f_flag");
	if(it != m_map.end())
		paraFlag = it->second;

	xmlNodePtr root_node = NULL;
	root_node = xmlNewNode(NULL, BAD_CAST "config");

	xmlNewChild(root_node, NULL, BAD_CAST "flag", BAD_CAST paraFlag.c_str());
	xmlNewChild(root_node, NULL, BAD_CAST "state", BAD_CAST "0");
	return root_node;
}

xmlNodePtr HDConfigView::xmlOutFMTGetSyncState() {

	xmlNodePtr root_node = NULL;
	root_node = xmlNewNode(NULL, BAD_CAST "config");

	xmlNewChild(root_node, NULL, BAD_CAST "res", BAD_CAST "1");
	xmlNewChild(root_node, NULL, BAD_CAST "wait_sync", BAD_CAST "0");
	return root_node;
}

xmlNodePtr HDConfigView::xmlOutFMTGetAutoRebuildInfo() {

	xmlNodePtr root_node = NULL;
	root_node = xmlNewNode(NULL, BAD_CAST "config");

	xmlNewChild(root_node, NULL, BAD_CAST "auto_sync", BAD_CAST "0");
	return root_node;
}

xmlNodePtr HDConfigView::xmlOutAJAXPlorerStop() {

	xmlNodePtr root_node = NULL;
	root_node = xmlNewNode(NULL, BAD_CAST "config");

	xmlNewChild(root_node, NULL, BAD_CAST "res", BAD_CAST "1");
	return root_node;
}

xmlNodePtr HDConfigView::xmlOutFMTCreateDiskMGR() {

	xmlNodePtr root_node = NULL;
	root_node = xmlNewNode(NULL, BAD_CAST "config");

	xmlNewChild(root_node, NULL, BAD_CAST "res", BAD_CAST "1");
	return root_node;
}

xmlNodePtr HDConfigView::xmlOutSmartHDList() {

	std::multimap<string, string>::iterator it;
	string paraPage;
	string paraRp;
	string paraQuery;
	string paraQtype;
	string paraField;
	string paraUser;

	it = m_map.find("page");
	if(it != m_map.end())
		paraPage = it->second;
	it = m_map.find("rp");
	if(it != m_map.end())
		paraRp = it->second;
	it = m_map.find("query");
	if(it != m_map.end())
		paraQuery = it->second;
	it = m_map.find("qtype");
	if(it != m_map.end())
		paraQtype = it->second;
	it = m_map.find("f_field");
	if(it != m_map.end())
		paraField = it->second;
	it = m_map.find("user");
	if(it != m_map.end())
		paraUser = it->second;

	xmlNodePtr root_node = NULL;
	root_node = xmlNewNode(NULL, BAD_CAST "rows");
	xmlNodePtr rowNode1 = xmlNewChild(root_node, NULL, BAD_CAST "row", NULL);

	xmlNewProp(rowNode1, BAD_CAST "id", BAD_CAST "1");
	xmlNodePtr cellNode = xmlNewChild(rowNode1, NULL, BAD_CAST "cell", NULL);
	xmlNodePtr inputNode = xmlNewChild(cellNode, NULL, BAD_CAST "input", NULL);
	xmlNewProp(inputNode, BAD_CAST "type", BAD_CAST "checkbox");
	xmlNewProp(inputNode, BAD_CAST "value", BAD_CAST "0,sda,S1F0HDP7");
	xmlNewProp(inputNode, BAD_CAST "id", BAD_CAST "smart_hdd_num_0");
	xmlNewProp(inputNode, BAD_CAST "name", BAD_CAST "smart_hdd_num");
	xmlNewChild(rowNode1, NULL, BAD_CAST "cell", BAD_CAST "Disk1");
	xmlNewChild(rowNode1, NULL, BAD_CAST "cell", BAD_CAST "Seagate");
	xmlNewChild(rowNode1, NULL, BAD_CAST "cell", BAD_CAST "ST3000DM001-9YN166");
	xmlNewChild(rowNode1, NULL, BAD_CAST "cell", BAD_CAST "-");
	xmlNewChild(rowNode1, NULL, BAD_CAST "cell", BAD_CAST "-");

	xmlNodePtr rowNode2 = xmlNewChild(root_node, NULL, BAD_CAST "row", NULL);
	xmlNewProp(rowNode2, BAD_CAST "id", BAD_CAST "2");
	xmlNodePtr cellNode2 = xmlNewChild(rowNode2, NULL, BAD_CAST "cell", NULL);
	xmlNodePtr inputNode2 = xmlNewChild(cellNode2, NULL, BAD_CAST "input", NULL);
	xmlNewProp(inputNode2, BAD_CAST "type", BAD_CAST "checkbox");
	xmlNewProp(inputNode2, BAD_CAST "value", BAD_CAST "1,sdb,S1F0HDP9");
	xmlNewProp(inputNode2, BAD_CAST "id", BAD_CAST "smart_hdd_num_0");
	xmlNewProp(inputNode2, BAD_CAST "name", BAD_CAST "smart_hdd_num");
	xmlNewChild(rowNode2, NULL, BAD_CAST "cell", BAD_CAST "Disk2");
	xmlNewChild(rowNode2, NULL, BAD_CAST "cell", BAD_CAST "Seagate");
	xmlNewChild(rowNode2, NULL, BAD_CAST "cell", BAD_CAST "ST3000DM001-9YN166");
	xmlNewChild(rowNode2, NULL, BAD_CAST "cell", BAD_CAST "-");
	xmlNewChild(rowNode2, NULL, BAD_CAST "cell", BAD_CAST "-");

	xmlNewChild(root_node, NULL, BAD_CAST "page", BAD_CAST paraPage.c_str());
	xmlNewChild(root_node, NULL, BAD_CAST "total", BAD_CAST "2");
	return root_node;
}


xmlNodePtr HDConfigView::xmlOutCreateTestList() {

	xmlNodePtr root_node = NULL;
	root_node = xmlNewNode(NULL, BAD_CAST "config");

	xmlNewChild(root_node, NULL, BAD_CAST "send_mail", BAD_CAST "0");
	xmlNewChild(root_node, NULL, BAD_CAST "smart_mail", BAD_CAST "0");

	return root_node;
}

xmlNodePtr HDConfigView::xmlOutSmartScheduleList() {

	std::multimap<string, string>::iterator it;
	string paraPage;
	string paraRp;
	string paraQuery;
	string paraQtype;
	string paraField;
	string paraUser;

	it = m_map.find("page");
	if(it != m_map.end())
		paraPage = it->second;
	it = m_map.find("rp");
	if(it != m_map.end())
		paraRp = it->second;
	it = m_map.find("query");
	if(it != m_map.end())
		paraQuery = it->second;
	it = m_map.find("qtype");
	if(it != m_map.end())
		paraQtype = it->second;
	it = m_map.find("f_field");
	if(it != m_map.end())
		paraField = it->second;
	it = m_map.find("user");
	if(it != m_map.end())
		paraUser = it->second;

	xmlNodePtr root_node = NULL;
	root_node = xmlNewNode(NULL, BAD_CAST "rows");
	xmlNodePtr rowNode = xmlNewChild(root_node, NULL, BAD_CAST "row", NULL);

	xmlNewProp(rowNode, BAD_CAST "id", BAD_CAST "1");
	xmlNewChild(rowNode, NULL, BAD_CAST "cell", BAD_CAST "S.M.A.R.T - Quick");
	xmlNewChild(rowNode, NULL, BAD_CAST "cell", BAD_CAST "Disk1,Disk2");
	xmlNewChild(rowNode, NULL, BAD_CAST "cell", BAD_CAST "MON 17:00 / Weekly");
	xmlNodePtr jsCellNode = xmlNewChild(rowNode, NULL, BAD_CAST "cell", NULL);
	xmlNodePtr aNode = xmlNewChild(jsCellNode, NULL, BAD_CAST "a", NULL);
	//xmlNewProp(aNode, BAD_CAST "href", BAD_CAST "javascript:onclick=create_schedule_wait(0)");
	xmlNewProp(aNode, BAD_CAST "href", BAD_CAST "javascript:onclick=create_schedule_wait(0)><IMG border='0' src='/web/images/delete_over.png'");

	//xmlNodePtr imgNode = xmlNewChild(jsCellNode, NULL, BAD_CAST "IMG", NULL);
	//xmlNewProp(imgNode, BAD_CAST "border", BAD_CAST "0");
	//xmlNewProp(imgNode, BAD_CAST "src", BAD_CAST "/web/images/delete_over.png");

	xmlNewChild(root_node, NULL, BAD_CAST "page", BAD_CAST paraPage.c_str());
	xmlNewChild(root_node, NULL, BAD_CAST "total", BAD_CAST "1");
	return root_node;
}

xmlNodePtr HDConfigView::xmlOutGetTestStatus() {

	xmlNodePtr root_node = NULL;
	root_node = xmlNewNode(NULL, BAD_CAST "Button");

	xmlNewChild(root_node, NULL, BAD_CAST "State", BAD_CAST "0:");
	return root_node;
}

xmlNodePtr HDConfigView::xmlOutSmartSetSchedule() {
	std::multimap<string, string>::iterator it;
	string paraDevice;
	string paraType;
	string paraHour;
	string paraMin;
	string paraWeekly;
	string paraDay;
	string paraTestType;
	string paraSlot;
	string paraMailFlag;

	it = m_map.find("f_device");
	if(it != m_map.end())
		paraDevice = it->second;
	it = m_map.find("f_type");
	if(it != m_map.end())
		paraType = it->second;
	it = m_map.find("f_hour");
	if(it != m_map.end())
		paraHour = it->second;
	it = m_map.find("f_min");
	if(it != m_map.end())
		paraMin = it->second;
	it = m_map.find("f_weekly");
	if(it != m_map.end())
		paraWeekly = it->second;
	it = m_map.find("f_day");
	if(it != m_map.end())
		paraDay = it->second;
	it = m_map.find("f_test_type");
	if(it != m_map.end())
		paraTestType = it->second;
	it = m_map.find("f_slot");
	if(it != m_map.end())
		paraSlot = it->second;
	it = m_map.find("f_mail_flag");
	if(it != m_map.end())
		paraMailFlag = it->second;

	xmlNodePtr root_node = NULL;
	root_node = xmlNewNode(NULL, BAD_CAST "config");

	xmlNewChild(root_node, NULL, BAD_CAST "cmd", BAD_CAST "1:short:0 :00:00:1:06");
	return root_node;
}

xmlNodePtr HDConfigView::xmlOutSmartDelSchedule() {
	std::multimap<string, string>::iterator it;
	string paraMailFlag;

	it = m_map.find("f_mail_flag");
	if(it != m_map.end())
		paraMailFlag = it->second;

	xmlNodePtr root_node = NULL;
	root_node = xmlNewNode(NULL, BAD_CAST "config");

	xmlNewChild(root_node, NULL, BAD_CAST "cmd", BAD_CAST "null");
	return root_node;
}

xmlNodePtr HDConfigView::xmlOutSmartTestStart() {
	std::multimap<string, string>::iterator it;
	string paraDevice;
	string paraType;
	string paraMailFlag;

	it = m_map.find("f_device");
	if(it != m_map.end())
		paraDevice = it->second;
	it = m_map.find("f_type");
	if(it != m_map.end())
		paraType = it->second;
	it = m_map.find("f_mail_flag");
	if(it != m_map.end())
		paraMailFlag = it->second;

	xmlNodePtr root_node = NULL;
	root_node = xmlNewNode(NULL, BAD_CAST "config");

	xmlNewChild(root_node, NULL, BAD_CAST "res", BAD_CAST "1");
	return root_node;
}


xmlNodePtr HDConfigView::xmlOutScanDiskInfo() {

	xmlNodePtr root_node = NULL;
	root_node = xmlNewNode(NULL, BAD_CAST "config");
	xmlNewChild(root_node, NULL, BAD_CAST "res", BAD_CAST "1");
	xmlNodePtr itemNode1 = xmlNewChild(root_node, NULL, BAD_CAST "item", NULL);
	xmlNewChild(itemNode1, NULL, BAD_CAST "opt_value", BAD_CAST "a");
	xmlNewChild(itemNode1, NULL, BAD_CAST "gui_value", BAD_CAST "All Volume(s)");

	xmlNodePtr itemNode2 = xmlNewChild(root_node, NULL, BAD_CAST "item", NULL);
	xmlNewChild(itemNode2, NULL, BAD_CAST "opt_value", BAD_CAST "Volume_1");
	xmlNewChild(itemNode2, NULL, BAD_CAST "gui_value", BAD_CAST "Volume_1");

	xmlNodePtr itemNode3 = xmlNewChild(root_node, NULL, BAD_CAST "item", NULL);
	xmlNewChild(itemNode3, NULL, BAD_CAST "opt_value", BAD_CAST "Volume_2");
	xmlNewChild(itemNode3, NULL, BAD_CAST "gui_value", BAD_CAST "Volume_2");

	return root_node;
}

xmlNodePtr HDConfigView::xmlOutCheckDiskRemountState() {
	xmlNodePtr root_node = NULL;
	root_node = xmlNewNode(NULL, BAD_CAST "config");

	xmlNewChild(root_node, NULL, BAD_CAST "res", BAD_CAST "0");
	return root_node;
}

xmlNodePtr HDConfigView::xmlOutScanDiskRunE2fsck() {
	xmlNodePtr root_node = NULL;
	root_node = xmlNewNode(NULL, BAD_CAST "script");
	xmlNodePtr textNode = xmlNewText(BAD_CAST "location.href='/web/dsk_mgr/hd_scandisk_state.html'");
	xmlAddChild(root_node, textNode);
	return root_node;
}

xmlNodePtr HDConfigView::xmlOutScanDiskFinish() {
	xmlNodePtr root_node = NULL;
	root_node = xmlNewNode(NULL, BAD_CAST "config");

	xmlNewChild(root_node, NULL, BAD_CAST "res", BAD_CAST "1");
	return root_node;
}

/***** Login/Logout *****/

xmlNodePtr HDConfigView::xmlOutIsBuildInLanguage() {

	xmlNodePtr root_node = NULL;
	root_node = xmlNewNode(NULL, BAD_CAST "flag");

#ifndef SIMULATOR_MODE
	xmlNodePtr textNode = xmlNewText(BAD_CAST getAPIStdOut(API_PATH + "sysapi_home -g build_in_language").c_str());
#else
	xmlNodePtr textNode = xmlNewText(BAD_CAST "1");
#endif

	xmlAddChild(root_node, textNode);
	return root_node;
}

xmlNodePtr HDConfigView::xmlOutGetUserLanguage() {
	xmlNodePtr root_node = NULL;
	root_node = xmlNewNode(NULL, BAD_CAST "language");

#ifndef SIMULATOR_MODE
	xmlNodePtr textNode = xmlNewText(BAD_CAST getAPIStdOut(API_PATH + "sysapi_home -g cgi_get_user_language").c_str());
#else
	xmlNodePtr textNode = xmlNewText(BAD_CAST "TC,TC.xml");
#endif

	xmlAddChild(root_node, textNode);
	return root_node;
}

xmlNodePtr HDConfigView::xmlOutGetSslInfo() {
#ifndef SIMULATOR_MODE
	string apiOut = getAPIStdOut(API_PATH + "sysapi_home -g ssl_info");
#else
	string apiOut = "0,443";
#endif
	vector<string> fields = split(apiOut);
	if(fields.size() < 2)
		return NULL;

	xmlNodePtr root_node = NULL;
	root_node = xmlNewNode(NULL, BAD_CAST "ssl_info");

	xmlNewChild(root_node, NULL, BAD_CAST "enable", BAD_CAST fields.at(0).c_str());
	xmlNewChild(root_node, NULL, BAD_CAST "port", BAD_CAST fields.at(1).c_str());
	return root_node;
}

string HDConfigView::strOutUICheckWto() {
#ifndef SIMULATOR_MODE
	string apiOut = getAPIStdOut(API_PATH + "sysapi_home -g ui_check_wto");
#else
	string apiOut = "success";
#endif
	return apiOut;
}

string HDConfigView::strOutFWStatus() {
#ifndef SIMULATOR_MODE
	string apiOut = getAPIStdOut(API_PATH + "sysapi_home -g fw_status");
#else
	string apiOut = "1";
#endif
	return apiOut;
}

string HDConfigView::strOutLogin() {
	std::multimap<string, string>::iterator it;
	string paraUsername;
	string paraPwd;
	string paraPort;
	string paraType;
	string paraFUsername;
	string paraPrePwd;
	string paraSsl;
	string paraC1;
	string paraSslPort;

	it = m_map.find("username");
	if(it != m_map.end())
		paraUsername = it->second;
	it = m_map.find("pwd");
	if(it != m_map.end())
		paraPwd = it->second;
	it = m_map.find("port");
	if(it != m_map.end())
		paraPort = it->second;
	it = m_map.find("f_type");
	if(it != m_map.end())
		paraType = it->second;
	it = m_map.find("f_username");
	if(it != m_map.end())
		paraFUsername = it->second;
	it = m_map.find("pre_pwd");
	if(it != m_map.end())
		paraPrePwd = it->second;
	it = m_map.find("ssl");
	bool bSsl = false;
	if(it != m_map.end()) {
		paraSsl = it->second;
		if(paraSsl.compare("1") == 0)
			bSsl = true;
	}
	it = m_map.find("C1");
	if(it != m_map.end())
		paraC1 = it->second;
	it = m_map.find("ssl_port");
	if(it != m_map.end())
		paraSslPort = it->second;

#ifndef SIMULATOR_MODE
	string apiOut = getAPIStdOut(API_PATH + "sysapi_home -g login " + paraUsername + " " + paraPwd);
	//BOOSTER_ERROR("apiOut") << apiOut;
	//BOOSTER_ERROR("apiOut") << apiOut.size();
#else
	string apiOut = "1";
#endif

	if(bSsl) {
#ifndef SIMULATOR_MODE
		string sslEnableOut = getAPIStdOut("nas_cfg -s web ssl_enable 1");
		string sslPortOut = getAPIStdOut("nas_cfg -s web ssl_port 443");

		//todo: restart.
#endif
	}

	if(paraC1.compare("ON") == 0) {
		m_session = paraUsername;
	}

	if(apiOut.compare("1") == 0) {
		m_loginStatus = 1;
		//BOOSTER_ERROR("apiOut") << "login";
	}
	else {
		BOOSTER_ERROR("apiOut") << apiOut;
		BOOSTER_ERROR("apiOut size") << apiOut.size();
	}

	return "";
}

string HDConfigView::strOutLogout() {
	std::multimap<string, string>::iterator it;
	string paraUsername;
	string paraOS;

	it = m_map.find("name");
	if(it != m_map.end())
		paraUsername = it->second;
	it = m_map.find("os");
	if(it != m_map.end())
		paraOS = it->second;

#ifndef SIMULATOR_MODE
	string apiOut = getAPIStdOut(API_PATH + "sysapi_home -s logout " + paraUsername);
#else
	string apiOut = "1";
#endif
	m_loginStatus = -1;

	return "";
}
