#include "questionmodel.h"
#include <QDebug>

QuestionModel::QuestionModel()
{
    recorder_ = new RecorderRunner;
}

QuestionModel::~QuestionModel()
{
    delete recorder_;
}

void QuestionModel::startRecord() {
    recorder_->start();
}

void QuestionModel::stopRecord() {
    recorder_->stop();
    audioData_ = recorder_->getAudioData();
}

std::string QuestionModel::sendAudioRequest() {
    std::string msg = "empty";
    qDebug() << QString("lkd2");
    std::string res = client_->sendAndRecieve(std::move(msg));
    return res;
}

void QuestionModel::setClient(std::shared_ptr<IClientTCP> client) {
    client_ = client;
}
