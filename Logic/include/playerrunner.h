#ifndef PLAYERRUNNER_H
#define PLAYERRUNNER_H


#include <QAudioOutput>
#include "audio.h"

class PlayerRunner: public Audio
{
    
    QAudioOutput player;
public:
    explicit PlayerRunner();
    void start() override;
    void stop() override;
};

#endif // PLAYERRUNNER_H
