#ifndef _HD_CONFIG_VIEW_
#define _HD_CONFIG_VIEW_

#include <cppcms/http_request.h>
#include <libxml/tree.h>
#include "PureView.h"
#include "CommandDefine.h"


class HDConfigView : public PureView {
public:
	HDConfigView(cppcms::http::request &, CGI_COMMAND);
	virtual ~HDConfigView();

	virtual void xmlOut();

private:

	xmlNodePtr xmlOutVolumeStatus();
	//cppcms::http::request *m_pReq;
	CGI_COMMAND m_cmd;
};

#endif
