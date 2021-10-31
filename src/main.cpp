#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>

#include "include/model.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.addImportPath("qrc:/");

    SensorModel *model = new SensorModel();

    model->addSensor(Sensor(model->GPS,"GPS", "Front gps"    , model->Warning, 33));
    model->addSensor(Sensor(model->GPS,"GPS", "Rear gps"     , model->Warning, 62));
    model->addSensor(Sensor(model->GPS,"GPS", "Starboard gps", model->Warning, 40));
    model->addSensor(Sensor(model->GPS,"GPS", "Port gps"     , model->Nominal, 53));

    model->addSensor(Sensor(model->Compass,"Compass", "Compass #1", model->Warning, 29));
    model->addSensor(Sensor(model->Compass,"Compass", "Compass #2", model->Error,   47));
    model->addSensor(Sensor(model->Compass,"Compass", "Compass #3", model->Error,   79));
    model->addSensor(Sensor(model->Compass,"Compass", "Compass #4", model->Error,   42));

    model->addSensor(Sensor(model->Anemometer,"Anemometer", "Primary anemometer"  , model->Nominal, 52));
    model->addSensor(Sensor(model->Anemometer,"Anemometer", "Secondary anemometer", model->Nominal, 77));

    model->addSensor(Sensor(model->Gyro,"Gyro", "Main gyro"  , model->Warning, 19));
    model->addSensor(Sensor(model->Gyro,"Gyro", "Backup gyro", model->Nominal, 33));

    engine.rootContext()->setContextProperty("myModel",model);

    qmlRegisterType<SensorModel>("MyModel",1,0,"MyModel");

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
