#include <QAbstractListModel>
#include "include/sensor.h"
#include <QDebug>

class SensorModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Types{ Anemometer, Compass, GPS, Gyro };
    Q_ENUMS(Types)

    enum States{ Warning, Nominal, Error };
    Q_ENUMS(States)

    enum SensorRoles {
        TypeRole = Qt::UserRole + 1,
        StateRole,
        StrengthRole,
        NameRole,
        TypeNameRole
    };
    Q_ENUMS(SensorRoles)

    SensorModel(QObject *parent = 0);

    void addSensor(const Sensor &sensor);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE QMap<QString, QVariant> getByIndex(int index);

    Q_INVOKABLE void setDataByIndex(int index,QVariant value,int role);

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<Sensor> m_sensors;


signals:
    void stateChanged(int index,int state);
    void strengthChanged(int index, float strength);
};
