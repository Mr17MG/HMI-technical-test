#include "include/sensor.h"

Sensor::Sensor(int type, QString type_name,QString name, int state, float strength)
    : _type(type), _state(state),_strength(strength), _name(name),_type_name(type_name)
{
}

int Sensor::type() const
{
    return this->_type;
}

void Sensor::setType(int type)
{
    this->_type = type;
}

int Sensor::state() const
{
    return this->_state;
}

void Sensor::setState(int state)
{
    this->_state = state;
}

float Sensor::strength() const
{
    return this->_strength;
}

void Sensor::setStrength(float strength)
{
    this->_strength = strength;
}

QString Sensor::typeName() const
{
    return this->_type_name;
}

void Sensor::setTypeName(QString typeName)
{
    this->_type_name = typeName;
}

QString Sensor::name() const
{
    return this->_name;
}

void Sensor::setName(QString name)
{
    this->_name = name;
}
