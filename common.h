#ifndef NERELL_GUI_COMMON_H
#define NERELL_GUI_COMMON_H

#include <iostream>
#include "json.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

using namespace std;
using json = nlohmann::json;

#define DATA_INVALID    "DATA_INVALID"
#define DATA_UNPARSABLE "DATA_UNPARSABLE"

#define RESPONSE_OK     "OK"
#define RESPONSE_ERROR  "ERROR"

#define ACTION_EXIT         "EXIT"
#define ACTION_ECHO         "ECHO"
#define ACTION_GET_STATE    "GET_STATE"
#define ACTION_UPDATE_STATE "UPDATE_STATE"
#define ACTION_PHOTO        "PHOTO"

struct JsonResult {
    string status;
    string action;
    string errorMessage;
    json datas;
};

struct JsonQuery {
    string action;
    json datas;
};

#endif //NERELL_GUI_COMMON_H
