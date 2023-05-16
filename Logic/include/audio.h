#ifndef AUDIO_H
#define AUDIO_H

#include <QObject>
#include <QAudioDeviceInfo>
#include <QAudioFormat>
#include <QAudioInput>
#include <QAudioOutput>
#include <QBuffer>
#include <QByteArray>

class Audio 
{
    
public:
    explicit Audio();
    virtual void start() = 0;
    virtual void stop() = 0;
    QByteArray getAudioData();
    QString audio;
protected:
    bool proceedAudio;
    QBuffer buffer;
    QByteArray array;
    QAudioFormat format;




};

#endif // AUDIO_H
