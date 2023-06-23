#ifndef RECORDERRUNNER_H
#define RECORDERRUNNER_H

#include "audio.h"

class RecorderRunner : public Audio
{
    QAudioInput recorder;
    QAudioOutput player;
public:
    explicit RecorderRunner();
    void start() override;
    void stop() override;
};

#endif // RECORDERRUNNER_H
