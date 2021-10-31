#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>

class Sensor
{
public:
    Sensor(int type, QString type_name, QString name, int state, float strength);

    int type() const;
    void setType(int type);

    int state() const;
    void setState(int state);

    float strength() const;
    void setStrength(float strength);

    QString typeName() const;
    void setTypeName(QString typeName);

    QString name() const;
    void setName(QString name);

private:
    int _type;
    int _state;

    float _strength;

    QString _name;
    QString _type_name;
};

#endif // SENSOR_H
