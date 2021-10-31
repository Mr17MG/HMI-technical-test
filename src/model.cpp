#include "include/model.h"

SensorModel::SensorModel(QObject *parent) : QAbstractListModel(parent){}

void SensorModel::addSensor(const Sensor &sensor)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_sensors << sensor;
    endInsertRows();
}

int SensorModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return m_sensors.count();
}

QVariant SensorModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= m_sensors.count())
        return QVariant();

    const Sensor &sensor = m_sensors[index.row()];
    if (role == TypeRole)
        return sensor.type();
    else if (role == StateRole)
        return sensor.state();
    else if (role == StrengthRole)
        return sensor.strength();
    else if (role == NameRole)
        return sensor.name();
    else if (role == TypeNameRole)
        return sensor.typeName();
    return QVariant();
}

QMap<QString,QVariant> SensorModel::getByIndex(int index)
{
    QMap<QString,QVariant> map;

    Sensor sensor = this->m_sensors.at(index);
    map.insert("type",QVariant(sensor.type()));
    map.insert("state",QVariant(sensor.state()));
    map.insert("name",QVariant(sensor.name()));
    map.insert("typeName",QVariant(sensor.typeName()));
    map.insert("strength",QVariant(sensor.strength()));
    return map;
}

void SensorModel::setDataByIndex(int index, QVariant value, int role)
{
    Sensor item = this->m_sensors.at(index);

    switch (role) {
    case TypeRole:
        item.setType(value.toInt());
        break;
    case StateRole:
        emit stateChanged(index,value.toInt());
        item.setState(value.toInt());
        break;
    case StrengthRole:
        emit strengthChanged(index,value.toFloat());
        item.setStrength(value.toFloat());
        break;
    case NameRole:
        item.setName(value.toString());
        break;
    case TypeNameRole:
        item.setTypeName(value.toString());
        break;
    }

    this->m_sensors.replace(index,item);

}

QHash<int, QByteArray> SensorModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[TypeRole] = "type";
    roles[StateRole] = "state";
    roles[StrengthRole] = "strength";
    roles[NameRole] = "name";
    roles[TypeNameRole] = "typeName";
    return roles;
}

