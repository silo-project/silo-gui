//
// Created by penta on 2021-02-11.
//

#include <map>
#include <httplib.h>
#include <tinyxml2.h>

#include "apis.h"
#include "session.h"
#include "../../lib/silo-main/src/simulator/simulator.h"

using namespace tinyxml2;

std::map<SessionID, Session*> MapSessionIDSession;
SessionID sid = 0;

void api::session::open (const httplib::Request &req, httplib::Response &res) {
    tinyxml2::XMLDocument xmlDoc;
    XMLElement* pRoot = xmlDoc.NewElement("session");
    XMLElement* psid = xmlDoc.NewElement("sid");
    psid->SetText(sid);
    pRoot->InsertEndChild(psid);
    xmlDoc.InsertFirstChild(pRoot);
    xmlDoc.ToText()
    MapSessionIDSession.insert(std::pair<SessionID, Session*>(sid++, new Session()));
}

void api::session::close (const httplib::Request &req, httplib::Response &res) {
    res.set_content("Hello World!", "text/plain");
}

void api::session::act(const httplib::Request &req, httplib::Response &res, const httplib::ContentReader &content_reader) {

}

Session::Session() {
    simulator = SimuCreate();
    NodeInit(simulator);
}

Session::~Session() {
    SimuDelete(simulator);
}
