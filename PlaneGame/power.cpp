#include "power.h"

Power::Power() {}

void Power::move(){
    v += a;
    this->moveBy(0,v);
}
