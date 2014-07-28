#include "applicationdesktop.h"

#include <iostream>

#include "logging.h"

_INITIALIZE_EASYLOGGINGPP

int main(int argc, char *argv[])
{
    LOG(INFO) << "Starting application";

    ApplicationDesktop app(1280, 720);

    if(!app.init()){
        // ToDo: Exceptions please!
        LOG(ERROR) << "Initialization of application failed" << std::endl;
    }

    int returnValue = app.exec();

    return returnValue;
}
