#ifndef CPP2QML_H
#define CPP2QML_H

#include <QObject>
#include <QQuickView>
#include <private/qquicktext_p.h>

class Cpp2Qml : public QObject
{
    Q_OBJECT
public:
#define G_QML_2_CPP (Cpp2Qml::instance())
    static Cpp2Qml* instance();
    void setQuickViewProvider(const QQuickView* quickView);
    void findTextBy_qt_qFindChild_helper();

private:
    explicit Cpp2Qml(QObject *parent = nullptr);
    QQuickView* quickView = nullptr;
    QQuickText* findText(const QString& objectName) const;
};

#endif // CPP2QML_H
