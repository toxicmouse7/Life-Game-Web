#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class GameSessionController : public drogon::HttpController<GameSessionController>
{
private:

public:
    METHOD_LIST_BEGIN
        ADD_METHOD_TO(GameSessionController::getFieldWithSeed, "/{1}", Get, Post);
    METHOD_LIST_END

    void getFieldWithSeed(const HttpRequestPtr& req,
                          std::function<void(const HttpResponsePtr&)>&& callback,
                          const std::string& seed);
};
