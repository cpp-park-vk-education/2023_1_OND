#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "icontroller.h"
#include "../../UI/guestmainwindow.h"
#include "questionmodel.h"

class Controller : public IController
{
public:
    Controller();
    void recordStart();
    QString recordStop();
    void setQuestionModel(QuestionModel*);
    void showMain();
    ~Controller();
private:
    GuestMainWindow* mainWindow_;
    QuestionModel* questionModel_;
};

#endif // CONTROLLER_H
