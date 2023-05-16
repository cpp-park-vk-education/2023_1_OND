#ifndef QUESTIONMODEL_H
#define QUESTIONMODEL_H

#include "recorderrunner.h"
#include <memory>
#include "iclienttcp.h"

class QuestionModel
{
public:
    QuestionModel();
    void startRecord();
    void stopRecord();
    std::string sendAudioRequest();
    void setClient(std::shared_ptr<IClientTCP>);
    ~QuestionModel();
private:
    RecorderRunner* recorder_;
    std::shared_ptr<IClientTCP> client_;
    QByteArray audioData_;
};

#endif // QUESTIONMODEL_H
