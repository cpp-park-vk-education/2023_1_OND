#include "controller.h"


Controller::Controller() {
    mainWindow_ = new GuestMainWindow;
    questionModel_ = nullptr;
    mainWindow_->setController(static_cast<IController*>(this));
}

void Controller::recordStart() {
    questionModel_->startRecord();
}

QString Controller::recordStop(){
    questionModel_->stopRecord();
    return QString::fromStdString(questionModel_->sendAudioRequest());
}

void Controller::setQuestionModel(QuestionModel* newQm) {
    questionModel_ = newQm;
}


void Controller::showMain() {
    this->mainWindow_->show();
}

Controller::~Controller() {
    delete mainWindow_;
}

