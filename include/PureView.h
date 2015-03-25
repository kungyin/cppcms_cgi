#ifndef _PURE_VIEW_
#define _PURE_VIEW_

#include <cppcms/http_request.h>
#include <cppcms/service.h>

class PureView {
public:

	virtual void xmlOut() = 0;
	virtual ~PureView() {}

protected:
	cppcms::http::request *m_pReq;


private:

};

#endif
