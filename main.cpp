#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQuickItem>
#include <QQmlContext>
#include <QUrl>
#include <QSurfaceFormat>
#include <QQuick3D>
#include <QDebug>
#include "cpp2qml.h"


int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    QSurfaceFormat format = QSurfaceFormat::defaultFormat();
    format.setVersion(3, 2);
    format.setRenderableType(QSurfaceFormat::OpenGLES);
    QSurfaceFormat::setDefaultFormat(QQuick3D::idealSurfaceFormat());
    qmlRegisterSingletonType<Cpp2Qml>(
                "Cpp2Qml", 1, 0, "Cpp2Qml",
                [](QQmlEngine* qml_engine, QJSEngine* js_engine) -> QObject* {
        (void)qml_engine;
        (void)js_engine;
        return dynamic_cast<QObject*>(G_QML_2_CPP);
    });
    QQuickView quickView;
    quickView.setColor(QColor(Qt::transparent));
    quickView.setFlags(Qt::Window | Qt::FramelessWindowHint);
    quickView.rootContext()->setContextProperty("mainwindow",&quickView);
    G_QML_2_CPP->setQuickViewProvider(&quickView);

    QObject::connect(&quickView, &QQuickView::statusChanged, [&]() {
        if (QQuickView::Ready == quickView.status()) {
            quickView.setGeometry(0, 0, 640, 480);
            quickView.show();
        } else {
            qDebug() << QString("load ") + quickView.source().toString() + QString(" failure!");
        }
    });
    quickView.setSource(QUrl(QStringLiteral("qrc:/qt_qFindChild_helper_minimal_example/main.qml")));
    G_QML_2_CPP->findTextBy_qt_qFindChild_helper();

    return application.exec();
}
