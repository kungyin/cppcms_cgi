#ifndef _HD_CONFIG_VIEW_
#define _HD_CONFIG_VIEW_


#include <libxml/tree.h>
#include "PureView.h"
#include "CommandDefine.h"
#include <cppcms/http_request.h>

class HDConfigView : public PureView {
public:
	HDConfigView(cppcms::http::request &, CGI_COMMAND);
	virtual ~HDConfigView();

	virtual std::string xmlOut();

	std::string getUsername() { return m_session; }
	int getLoginStatus() { return m_loginStatus; }
	bool isStrOut() { return m_isStrOut; }

private:

	std::string getAPIStdOut(std::string);
	std::vector<std::string> split(std::string);

	xmlNodePtr xmlOutVolumeStatus();
	xmlNodePtr xmlOutFMTGetSyncState();
	xmlNodePtr xmlOutFMTGetAutoRebuildInfo();
	xmlNodePtr xmlOutAJAXPlorerStop();
	xmlNodePtr xmlOutFMTCreateDiskMGR();
	xmlNodePtr xmlOutSmartHDList();
	xmlNodePtr xmlOutCreateTestList();
	xmlNodePtr xmlOutSmartScheduleList();
	xmlNodePtr xmlOutGetTestStatus();
	xmlNodePtr xmlOutSmartSetSchedule();
	xmlNodePtr xmlOutSmartDelSchedule();
	xmlNodePtr xmlOutSmartTestStart();
	xmlNodePtr xmlOutScanDiskInfo();
	xmlNodePtr xmlOutCheckDiskRemountState();
	xmlNodePtr xmlOutScanDiskRunE2fsck();
	xmlNodePtr xmlOutScanDiskFinish();

	xmlNodePtr xmlOutIsBuildInLanguage();
	xmlNodePtr xmlOutGetUserLanguage();
	xmlNodePtr xmlOutGetSslInfo();
	std::string strOutUICheckWto();
	std::string strOutFWStatus();
	std::string strOutLogin();
	std::string strOutLogout();


	CGI_COMMAND m_cmd;
	std::string m_session;
	int m_loginStatus;
	bool m_isStrOut;
	std::multimap<std::string, std::string> m_map;
};

#endif
