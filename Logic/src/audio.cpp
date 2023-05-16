#include "audio.h"

Audio::Audio()
    :   proceedAudio(false), buffer(&array)
{
    if (format.sampleRate() == -1) {
        format.setSampleRate(6000);
        format.setChannelCount(1);
        format.setSampleSize(32);
        format.setCodec("audio/pcm");
        format.setByteOrder(QAudioFormat::LittleEndian);
        format.setSampleType(QAudioFormat::Float);
    }

    QAudioDeviceInfo devInfo = QAudioDeviceInfo::defaultInputDevice();

    if (!devInfo.isFormatSupported(format)) {
        throw std::runtime_error("WAV format not supported, cannot play audio");
    }
}

QByteArray Audio::getAudioData() {
    return array;
}
