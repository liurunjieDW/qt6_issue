#include "cpp2qml.h"
#include <QCoreApplication>
#include <QThread>
Cpp2Qml::Cpp2Qml(QObject *parent)
    : QObject{parent}
{

}


Cpp2Qml *Cpp2Qml::instance()
{
    static Cpp2Qml* object = nullptr;
    if (nullptr == object) {
        object = new Cpp2Qml(qApp);
    }
    return object;
}


void Cpp2Qml::setQuickViewProvider(const QQuickView *quickView)
{
    this->quickView = const_cast<QQuickView*>(quickView);
}

QQuickText *Cpp2Qml::findText(const QString &objectName) const
{
    QQuickText * quickText = nullptr;
    do {
        if (QThread::currentThread() != thread()) {
                qWarning() << __FUNCTION__ << __LINE__ << objectName;
            break;
        }
        if (nullptr == quickView) {
            qWarning() << "nullptr == quickView";
            break;
        }
        QQuickItem *rootObject = quickView->rootObject();
        if (nullptr == rootObject) {
            qWarning() << "nullptr == rootObject";
            break;
        }
        quickText = rootObject->findChild<QQuickText *>(objectName);
        if (nullptr == quickText) {
            qWarning() << "nullptr == quickText" << objectName;
            break;
        }
    } while (false);
    return quickText;
}
void Cpp2Qml::findTextBy_qt_qFindChild_helper(){
    do {
        const QString objectName("qmlnodetext");
        static QQuickText* textItem = G_QML_2_CPP->findText(objectName);
        if (nullptr == textItem) {
            qWarning() << "can't find text from cpp2qml -- " << objectName;
            break;
        }
        qInfo() << "find text from cpp2qml -- " << objectName;
    }while(0);
}
