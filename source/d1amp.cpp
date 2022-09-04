#include "d1amp.h"

#include <QBuffer>

D1Amp::D1Amp(QString path)
    : file()
{
    this->load(path);
}

D1Amp::~D1Amp()
{
    if (this->file.isOpen())
        this->file.close();
}

bool D1Amp::load(QString ampFilePath)
{
    // Opening AMP file with a QBuffer to load it in RAM
    if (!QFile::exists(ampFilePath))
        return false;

    if (this->file.isOpen())
        this->file.close();

    this->file.setFileName(ampFilePath);

    if (!this->file.open(QIODevice::ReadOnly))
        return false;

    QByteArray fileData = this->file.readAll();
    QBuffer fileBuffer(&fileData);

    if (!fileBuffer.open(QIODevice::ReadOnly))
        return false;

    // Read AMP binary data
    QDataStream in(&fileBuffer);
    in.setByteOrder(QDataStream::LittleEndian);

    this->tileCount = this->file.size();

    quint8 readBytr;
    this->properties.clear();
    this->types.clear();
    for (int i = 0; i < this->tileCount; i++) {
        in >> readBytr;
        this->types.append(readBytr);
        in >> readBytr;
        this->properties.append(readBytr);
    }

    return true;
}

QString D1Amp::getFilePath()
{
    if (!this->file.isOpen())
        return QString();

    return this->file.fileName();
}

quint8 D1Amp::getTileType(quint16 tileIndex)
{
    if (tileIndex >= this->tileCount)
        return 0;

    return this->types.at(tileIndex);
}

quint8 D1Amp::getTileProperties(quint16 tileIndex)
{
    if (tileIndex >= this->tileCount)
        return 0;

    return this->properties.at(tileIndex);
}
