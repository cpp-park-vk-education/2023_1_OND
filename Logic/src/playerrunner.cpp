#include "playerrunner.h"
#include <QDebug>

PlayerRunner::PlayerRunner() : Audio(),
    player(format) {
}

void PlayerRunner::start() {
    buffer.open(QBuffer::ReadOnly);
    player.start(&buffer);
    qDebug() << QString("player start");
}

void PlayerRunner::stop() {
    player.stop();
    buffer.seek(0);
    buffer.close();
    qDebug() << QString("player stop");
    qDebug() << array;
}

