/*
 * CommandDefine.h
 *
 *  Created on: 2015年3月25日
 *      Author: ian
 */

#ifndef COMMANDDEFINE_H_
#define COMMANDDEFINE_H_

enum CGI_COMMAND {
	CMD_NONE = 0,
    CMD_VOLUME_STATUS,
	CMD_FMT_GET_SYNC_SATTE,
	CMD_FMT_GET_AUTO_REBUILD_INFO,
	CMD_AJAXPLORER_STOP,
	CMD_FMT_CREATE_DISKMGR,
	CMD_SMART_HD_LIST,
	CMD_SMART_XML_CREATE_TEST_LIST,
	CMD_SMART_SCHEDULE_LIST,
	CMD_SMART_GET_TEST_STATUS,
	CMD_SMART_SET_SCHEDULE,
	CMD_SMART_TEST_START,
	CMD_SCANDISK_INFO,
	CMD_CHECK_DISK_REMOUNT_STATUS,
	CMD_SCANDISK_RUN_E2FSCK,
	CMD_SCANDISK_FINISH,

	CMD_CGI_IS_BUILD_IN_LANGUAGE,
	CMD_CGI_GET_USER_LANGUAGE,
	CMD_CGI_GET_SSL_INFO,
	CMD_UI_CHECK_WTO,
	CMD_FW_STATUS,
	CMD_LOGIN,
	CMD_LOGOUT
};


#endif /* COMMANDDEFINE_H_ */
