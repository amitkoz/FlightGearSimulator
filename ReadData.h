#ifndef UNTITLED1_READDATA_H
#define UNTITLED1_READDATA_H

#include "allCommands.h"

#define  ARGsize 36

class ReadData {
    list<string> ls;
    map<string, Command *> mp;
public:

    void divData(string data) {
        while (data.size() > 0) {
            size_t found = data.find(",");
            if (found != std::string::npos) {
                string tolist = data.substr(0, found);
                ls.push_back(tolist);
                data = data.substr(found + 1, data.size());
            } else {
                ls.push_back(data);
                data = "";
            }
        }
    }

    // make map for all the info we will get from server
    void makeMap() {
        for (int i = 0; i < ARGsize; i++) {
            Command *c = new alltype();
            switch (i) {
                case 0:
                    c->setPath("/instrumentation/airspeed-indicator/indicated-speed-kt");
                    mp["a"] = {c};
                    break;

                case 1:
                    c->setPath("/sim/time/warp");
                    mp["b"] = {c};
                    break;

                case 2:
                    c->setPath("/controls/switches/magnetos");
                    mp["c"] = {c};
                    break;
                case 3:
                    c->setPath("/instrumentation/heading-indicator/offset-deg");
                    mp["d"] = {c};
                    break;
                case 4:

                    c->setPath("/instrumentation/altimeter/indicated-altitude-ft");
                    mp["e"] = {c};
                    break;
                case 5:

                    c->setPath("/instrumentation/altimeter/pressure-alt-ft");
                    mp["f"] = {c};
                    break;
                case 6:
                    c->setPath("/instrumentation/attitude-indicator/indicated-pitch-deg");
                    mp["g"] = {c};
                    break;
                case 7:
                    c->setPath("/instrumentation/attitude-indicator/indicated-roll-deg");
                    mp["h"] = {c};
                    break;
                case 8:
                    c->setPath("/instrumentation/attitude-indicator/internal-pitch-deg");
                    mp["i"] = {c};
                    break;
                case 9:
                    c->setPath("/instrumentation/attitude-indicator/internal-roll-deg");
                    mp["j"] = {c};
                    break;
                case 10:
                    c->setPath("/instrumentation/encoder/indicated-altitude-ft");
                    mp["k"] = {c};
                    break;
                case 11:
                    c->setPath("/instrumentation/encoder/pressure-alt-ft");
                    mp["l"] = {c};
                    break;
                case 12:
                    c->setPath("/instrumentation/gps/indicated-altitude-ft");
                    mp["m"] = {c};
                    break;
                case 13:
                    c->setPath("/instrumentation/gps/indicated-ground-speed-kt");
                    mp["n"] = {c};
                    break;
                case 14:
                    c->setPath("/instrumentation/gps/indicated-vertical-speed");
                    mp["o"] = {c};
                    break;
                case 15:
                    c->setPath("/instrumentation/heading-indicator/indicated-heading-deg");
                    mp["p"] = {c};
                    break;
                case 16:
                    c->setPath("/instrumentation/magnetic-compass/indicated-heading-deg");
                    mp["q"] = {c};
                    break;
                case 17:
                    c->setPath("/instrumentation/slip-skid-ball/indicated-slip-skid");
                    mp["r"] = {c};
                    break;
                case 18:
                    c->setPath("/instrumentation/turn-indicator/indicated-turn-rate");
                    mp["s"] = {c};
                    break;
                case 19:
                    c->setPath("/instrumentation/vertical-speed-indicator/indicated-speed-fpm");
                    mp["t"] = {c};
                    break;
                case 20:
                    c->setPath("/controls/flight/aileron");
                    mp["u"] = {c};
                    break;
                case 21:
                    c->setPath("/controls/flight/elevator");
                    mp["v"] = {c};
                    break;
                case 22:
                    c->setPath("/controls/flight/rudder");
                    mp["w"] = {c};
                    break;
                case 23:
                    c->setPath("/controls/flight/flaps");
                    mp["x"] = {c};
                    break;
                case 24:
                    c->setPath("/controls/engines/engine/throttle");
                    mp["y"] = {c};
                    break;
                case 25:
                    c->setPath("/controls/engines/current-engine/throttle");
                    mp["z"] = {c};
                    break;
                case 26:
                    c->setPath("/controls/switches/master-avionics");
                    mp["za"] = {c};
                    break;
                case 27:
                    c->setPath("/controls/switches/starter");
                    mp["zb"] = {c};
                    break;
                case 28:
                    c->setPath("/engines/active-engine/auto-start");
                    mp["zc"] = {c};
                    break;
                case 29:
                    c->setPath("/controls/flight/speedbrake");
                    mp["zd"] = {c};
                    break;
                case 30:
                    c->setPath("/sim/model/c172p/brake-parking");
                    mp["ze"] = {c};
                    break;
                case 31:
                    c->setPath("/controls/engines/engine/primer");
                    mp["zf"] = {c};
                    break;
                case 32:
                    c->setPath("/controls/engines/current-engine/mixture");
                    mp["zg"] = {c};
                    break;
                case 33:
                    c->setPath("/controls/switches/master-bat");
                    mp["zh"] = {c};
                    break;
                case 34:
                    c->setPath("/controls/switches/master-alt");
                    mp["zi"] = {c};
                    break;
                case 35:
                    c->setPath("/engines/engine/rpm");
                    mp["zj"] = {c};
                    break;
                default:
                    cerr << "error reading data";
            }

        }
    }

    // update values in maps
    map<string, Command *> setData(string data) {
        divData(data);
        for (auto x: mp) {
            string val = *ls.begin();
            x.second->setVal(val);
            ls.pop_front();
        }
        return this->mp;
    }

    ~ReadData() {
        for (auto x:this->mp) {
            if (x.second != NULL) {
                delete x.second;
            }
        }
    }
};


#endif //UNTITLED1_READDATA_H