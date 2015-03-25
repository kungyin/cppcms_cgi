#line 1 "../template/first.tmpl"
#include "content.h" 
#line 2 "../template/first.tmpl"
namespace my_skin {
	#line 3 "../template/first.tmpl"
	struct message :public cppcms::base_view
	#line 3 "../template/first.tmpl"
	{
	#line 3 "../template/first.tmpl"
		content::message &content;
	#line 3 "../template/first.tmpl"
		message(std::ostream &_s,content::message &_content): cppcms::base_view(_s),content(_content)
	#line 3 "../template/first.tmpl"
		{
	#line 3 "../template/first.tmpl"
		}
		#line 4 "../template/first.tmpl"
		virtual void render() {
			#line 7 "../template/first.tmpl"
			out()<<"\n"
				"<html>\n"
				"<body>\n"
				"<h1>";
			#line 7 "../template/first.tmpl"
			out()<<cppcms::filters::escape(content.text);
			#line 10 "../template/first.tmpl"
			out()<<"</h1>\n"
				"</body>\n"
				"<html>\n"
				"";
		#line 10 "../template/first.tmpl"
		} // end of template render
	#line 11 "../template/first.tmpl"
	}; // end of class message
#line 12 "../template/first.tmpl"
} // end of namespace my_skin
#line 13 "../template/first.tmpl"
namespace {
#line 13 "../template/first.tmpl"
 cppcms::views::generator my_generator; 
#line 13 "../template/first.tmpl"
 struct loader { 
#line 13 "../template/first.tmpl"
  loader() { 
#line 13 "../template/first.tmpl"
   my_generator.name("my_skin");
#line 13 "../template/first.tmpl"
   my_generator.add_view<my_skin::message,content::message>("message",true);
#line 13 "../template/first.tmpl"
    cppcms::views::pool::instance().add(my_generator);
#line 13 "../template/first.tmpl"
 }
#line 13 "../template/first.tmpl"
 ~loader() {  cppcms::views::pool::instance().remove(my_generator); }
#line 13 "../template/first.tmpl"
} a_loader;
#line 13 "../template/first.tmpl"
} // anon 
