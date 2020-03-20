#pragma once
#include <unordered_set>
using namespace std;

#pragma cle def GREEN_POSITION {"level":"green",\
  "cdf": [\
    {"remotelevel":"==orange", \
     "direction": "egress", \
     "guardhint": { "oneway": "true"}}\
  ] }}

#pragma cle def ORANGE_POSITION {"level":"orange",\
  "cdf": [\
    {"remotelevel":"==green", \
     "direction": "egress", \
     "guardhint": { "oneway": "true"}}\
  ] }

#pragma cle def ORANGE_DISTANCE {"level":"orange",\
  "cdf": [\
    {"remotelevel":"==green", \
     "direction": "egress", \
     "guardhint": { "oneway": "true"}}\
  ] }


class Subject;
class Observer
{
public:
  virtual void update(Subject *) = 0;
};

class Subject
{
public:
  void attach(Observer *o) {
    _observers.insert(o);
  };
  void detach(Observer *o) {
    _observers.erase(o);
  };
  void detachAll() {
    _observers.clear();
  };
  virtual void notify() = 0;

protected:
  unordered_set<Observer *> _observers;
};

class Trailer
{
public:
    int seq;
    int rqr;
    int oid;
    short mid;
    short crc;

    Trailer() {}
};
