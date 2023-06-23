#include "recorderrunner.h"
#include <QDebug>

RecorderRunner::RecorderRunner() : Audio(),
    recorder(format), player(format) {
}

void RecorderRunner::start() {
    buffer.open(QBuffer::WriteOnly);
    buffer.buffer().clear();
    buffer.seek(0);
    recorder.start(&buffer);
    qDebug() << QString("start");
}

void RecorderRunner::stop() {
    recorder.stop();
    buffer.seek(0);
      buffer.close();
      buffer.open(QBuffer::ReadOnly);
      player.start(&buffer);
      qDebug() << QString("player start");

      buffer.seek(0);
      //buffer.close();
    qDebug() << QString("stop");
    //qDebug() << array;
}

