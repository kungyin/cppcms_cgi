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
#include <cppcms/session_interface.h>
#include <cppcms/http_cookie.h>

#include <booster/log.h>
#include <booster/shared_ptr.h>

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
	if(request().script_name().compare("/cgi-bin/login_mgr.cgi") != 0) {
		cppcms::http::cookie my_cookie = request().cookie_by_name("username");
		//std::string user = my_cookie.value();

		if(my_cookie.empty()) {
			//BOOSTER_ERROR("script name") << request().script_name();
			response().status(cppcms::http::response::not_found);
			response().out();
			return;
		}
	}

	std::multimap<string, string> map = request().post_or_get();
	std::multimap<string, string>::iterator it = map.find(CGI_PARA_CMD_NAME);
	if(it != map.end()) {
		string paraCmd = it->second;
		ParseCommand parse(paraCmd);
		CGI_COMMAND cmd = parse.getCGICmd();

//		string s = request().get("cmd");
//		    content::message c;
//		    c.text=" CGI command is:" + s;
//		    render("message",c);

		HDConfigView cv(request(), cmd);
		string responseOut = cv.xmlOut();

		response().io_mode(cppcms::http::response::nogzip);
		if(!cv.isStrOut())
			response().set_content_header("text/xml");

		if(paraCmd.compare("login") == 0) {
			string name = cv.getUsername();
			int age = 0;
			if(!name.empty())
				age = 31536000;

			cppcms::http::cookie cookieName("uname", map.find("username")->second, age, "/");
			response().set_cookie(cookieName);
			cppcms::http::cookie cookieRem("rembMe", "checked", age, "/");
			response().set_cookie(cookieRem);
			cppcms::http::cookie cookiePw("password", map.find("pwd")->second, age, "/");
			response().set_cookie(cookiePw);

			int status = cv.getLoginStatus();
			if(status == 1) {
				cppcms::http::cookie c("username", map.find("username")->second, 0, "/");
				c.browser_age();
				response().set_cookie(c);
				response().set_redirect_header("../web/home.html?v=8401878");
			}
			else if(status == 0){
				response().set_redirect_header("../web/relogin.html");
			}
		}
		else if(paraCmd.compare("logout") == 0) {
			response().set_redirect_header("..");
		}

		response().out() << responseOut;
	}
}

int main(int argc,char ** argv)
{
    booster::shared_ptr<booster::log::sinks::file> f(new booster::log::sinks::file());
    f->append();
    f->max_files(10);
    f->open("/tmp/test.log");
    booster::log::logger::instance().add_sink(f);
    booster::log::logger::instance().set_default_level(booster::log::notice);

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
