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

#define ACTION_EXIT           "EXIT"
#define ACTION_ECHO           "ECHO"
#define ACTION_GET_CONFIG     "GET_CONFIG"
#define ACTION_UPDATE_STATE   "UPDATE_STATE"
#define ACTION_UPDATE_MATCH   "UPDATE_MATCH"
#define ACTION_UPDATE_PHOTO   "UPDATE_PHOTO"

struct JsonResult {
    string status;
    string action;
    string errorMessage;
    json data;
};

struct JsonQuery {
    string action;
    json data;
};

#endif //NERELL_GUI_COMMON_H
