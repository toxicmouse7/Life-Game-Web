#include "GameSessionController.h"

#include <memory>
#include "LifeGameModel.hpp"

#define LG_MOD "lifeGameModel"

void GameSessionController::getFieldWithSeed(const HttpRequestPtr& req,
                                             std::function<void(const HttpResponsePtr&)>&& callback,
                                             const std::string& seed)
{
    std::vector<std::string> field;

    if (!req->session()->find(LG_MOD))
    {
        auto model = std::make_shared<LifeGameModel>("123");
        req->session()->insert(LG_MOD, model);
    }

    req->session()->modify<std::shared_ptr<LifeGameModel>>(LG_MOD,
                                                           [&field, seed](std::shared_ptr<LifeGameModel>& model)
                                                           {
                                                               if (model->getSeed() != seed)
                                                                   model = std::make_shared<LifeGameModel>(seed);
                                                               field = model->getEpoch();
                                                               model->newEpoch();
                                                           });

    HttpViewData data;
    data.insert("field", field);

    auto res = HttpResponse::newHttpViewResponse("GameView.csp", data);
    res->setStatusCode(drogon::k200OK);
    callback(res);
}
