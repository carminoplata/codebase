#include "sampleapp.hpp"
#include "config.h"
#include <iostream>
#include <sstream>
#include <string>

int main(){
    std::stringstream ss;

    ss << "Welcome to SampleApp " << APP_VERSION
       << "!";
    SampleApp app(ss.str());
    app.print(std::cout);
}