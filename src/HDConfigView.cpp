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
//#include <libxml/xpath.h>
//
//#include <libxml/xpathInternals.h>

using namespace std;
using namespace cppcms;

HDConfigView::HDConfigView(http::request &req, CGI_COMMAND cmd)
	: m_cmd(cmd)
{
	m_pReq = &req;
}

HDConfigView::~HDConfigView() {
}

void HDConfigView::xmlOut() {

	xmlDocPtr doc = NULL;       /* document pointer */
	xmlNodePtr root_node = NULL, node = NULL, node1 = NULL;/* node pointers */
	xmlDtdPtr dtd = NULL;       /* DTD pointer */

	LIBXML_TEST_VERSION;

	doc = xmlNewDoc(BAD_CAST "1.0");

	switch(m_cmd) {
	case CMD_VOLUME_STATUS:
		root_node = xmlOutVolumeStatus();
		break;
	case CMD_NONE:
	default:
		break;
	}

//	string paraFlag = m_pReq->get("f_flag");
//	root_node = xmlNewNode(NULL, BAD_CAST "config");
//
//	xmlNewChild(root_node, NULL, BAD_CAST "flag", BAD_CAST paraFlag.c_str());
//	xmlNewChild(root_node, NULL, BAD_CAST "state", BAD_CAST "0");

	if(root_node == NULL)
		return;

	xmlDocSetRootElement(doc, root_node);
	/*
	 *      * Dumping document to stdio or file
	 */
	//xmlSaveFormatFileEnc("-", doc, "UTF-8", 2);

	xmlSaveCtxtPtr ctxt;
	ctxt = xmlSaveToFilename( "-", "UTF-8", XML_SAVE_FORMAT | XML_SAVE_NO_DECL);
	if (ctxt != NULL) {
		if (xmlSaveDoc(ctxt, doc) < 0) {
		}
		xmlSaveClose(ctxt);
	}

	xmlFreeDoc(doc);

	xmlCleanupParser();
}

xmlNodePtr HDConfigView::xmlOutVolumeStatus() {
	string paraFlag = m_pReq->get("f_flag");

	xmlNodePtr root_node = NULL;
	root_node = xmlNewNode(NULL, BAD_CAST "config");

	xmlNewChild(root_node, NULL, BAD_CAST "flag", BAD_CAST paraFlag.c_str());
	xmlNewChild(root_node, NULL, BAD_CAST "state", BAD_CAST "0");
	return root_node;
}
