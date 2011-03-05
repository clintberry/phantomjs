#include <QObject>
#include "qcommandline.h"

class Options : public QObject
{
  Q_OBJECT
public:
    Options();
    QString proxy;
    QString port;
    QString file;
    QStringList args;
public slots:
    void parseError(const QString & name);
    void switchFound(const QString & name);
    void optionFound(const QString & name, const QVariant & value);
    void paramFound(const QString & name, const QVariant & value);
 private:
    QCommandLine *cmdline;
};
