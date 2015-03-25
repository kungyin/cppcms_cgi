/*
 * main.cpp
 *
 *  Created on: 2015年3月17日
 *      Author: ian
 */


#include <cppcms/application.h>
#include <cppcms/applications_pool.h>
#include <cppcms/service.h>
#include <cppcms/http_response.h>
#include <cppcms/http_request.h>

#include <iostream>
#include <map>

#include "content.h"
#include "ParseCommand.h"
#include "HDConfigView.h"
#include "CommandDefine.h"


using namespace std;

const string CGI_PARA_CMD_NAME = "cmd";

class cgiMain : public cppcms::application {
public:
	cgiMain(cppcms::service &srv) :
        cppcms::application(srv)
    {
    }
    virtual void main(std::string url);

private:
//    cppcms::service m_srv;
};

void cgiMain::main(std::string /*url*/)
{

	string paraCmd = request().get(CGI_PARA_CMD_NAME);
	if(!paraCmd.empty()) {
		ParseCommand parse(paraCmd);
		CGI_COMMAND cmd = parse.getCGICmd();
//	map<string, string> m = request().getenv();
//	cout << m.size() << endl;
//	cout << request().request_method() << endl;
//	cout << request().query_string() << endl;
//	cout << request().content_type() << endl;
//	cout << request().gateway_interface() << endl;
//	cout << request().auth_type() << endl;
//	cout << request().remote_addr() << endl;
//	cout << request().http_accept () << endl;
//	cout << request().post("cmd") << endl;
//	cout << request().http_connection() << endl;

//	cppcms::http::content_type a = request().content_type_parsed();
//	cout << a.type() << endl;
//	map<string, string> mm = request().content_type_parsed().parameters();
//	cout << mm.size() << endl;

	//cout << m.at(0) << endl;

//    response().out() <<
//        "<html>\n"
//        "<body>\n"
//        "  <h1>Hello World</h1>\n"
//        "</body>\n"
//        "</html>\n";

	//string s = request().get("cmd");
//    content::message c;
//    c.text=" CGI command is:" + s;
//    render("message",c);
		HDConfigView cv(request(), cmd);
		cv.xmlOut();
	}

}

int main(int argc,char ** argv)
{
    try {
        cppcms::service srv(argc,argv);
        srv.applications_pool().mount(
            cppcms::applications_factory<cgiMain>()
        );
        srv.run();
    }
    catch(std::exception const &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
