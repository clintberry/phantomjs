#ifndef TEST_H
# define TEST_H

#include <QObject>
#include "qcommandline.h"

class Test : public QObject
{
  Q_OBJECT
public:
    Test();
public slots:
    void parseError(const QString & name);
    void switchFound(const QString & name);
    void optionFound(const QString & name, const QVariant & value);
    void paramFound(const QString & name, const QVariant & value);
 private:
    QCommandLine *cmdline;
};

#endif
