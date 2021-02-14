//
// Created by penta on 2021-02-11.
//

#include <map>
#include <httplib.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

#include "apis.h"
#include "session.h"
#include "simulator/simulator.h"

using namespace rapidjson;

std::map<SessionID, Session*> MapSessionIDSession;
SessionID sid = 1;

void api::session::open (const httplib::Request &req, httplib::Response &res) {
    StringBuffer s;
    Writer<StringBuffer> writer(s);
    writer.StartObject();
    writer.Key("state");
    writer.Uint(0);
    writer.Key("sid");
    writer.Uint(sid);
    writer.EndObject();
    res.set_content(s.GetString(), "text/json");
    MapSessionIDSession.insert(std::pair<SessionID, Session*>(sid++, new Session()));
}

void api::session::close (const httplib::Request &req, httplib::Response &res) {
    auto sd = req.params.find("sid");
    if (sd != req.params.end()) {
        auto t = MapSessionIDSession.find(atoi(sd->second.c_str()));
        if (t != MapSessionIDSession.end()) {
            Session* sp = t->second;
            delete sp;
            MapSessionIDSession.erase(t);
            StringBuffer s;
            Writer<StringBuffer> writer(s);
            writer.StartObject();
            writer.Key("state");
            writer.Uint(0);
            writer.EndObject();
            res.set_content(s.GetString(), "text/json");
        } else {
            StringBuffer s;
            Writer<StringBuffer> writer(s);
            writer.StartObject();
            writer.Key("state");
            writer.Uint(1);
            writer.EndObject();
            res.set_content(s.GetString(), "text/json");
        }
    } else {

        StringBuffer s;
        Writer<StringBuffer> writer(s);
        writer.StartObject();
        writer.Key("state");
        writer.Uint(1);
        writer.EndObject();
        res.set_content(s.GetString(), "text/json");
    }
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
