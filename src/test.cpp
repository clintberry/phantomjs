#include "qcommandline.h"
#include <QApplication>
#include <QDebug>
#include <QVariant>

#include "test.h"

Test::Test()
{
  static const struct QCommandLineConfigEntry conf[] =
    {
      { QCommandLine::Option, 'h', "host", "Proxy Host", QCommandLine::Optional },
      { QCommandLine::Option, 'p', "port", "Proxy Port", QCommandLine::Optional },
      { QCommandLine::Param, '\0', "file", "The Script File", QCommandLine::Mandatory },
      QCOMMANDLINE_CONFIG_ENTRY_END
    };
  /*
   * Similar to:
   * cmdline->addOption("v", "verbose", "verbose level (0-3)");
   * cmdline->addSwitch("l", "list", "show a list")
   * cmdline->addParam("source", "the sources", QCommandLine::Mandatory|QCommandLine::Multiple);
   * cmdline->addParam("target", "the target", QCommandLine::Mandatory);
   */

   cmdline = new QCommandLine(this);
   cmdline->setConfig(conf);
   cmdline->enableVersion(true); // enable -v // --version
   cmdline->enableHelp(true); // enable -h / --help

  connect(cmdline, SIGNAL(switchFound(const QString &)),
          this, SLOT(switchFound(const QString &)));
  connect(cmdline, SIGNAL(optionFound(const QString &, const QVariant &)),
          this, SLOT(optionFound(const QString &, const QVariant &)));
  connect(cmdline, SIGNAL(paramFound(const QString &, const QVariant &)),
          this, SLOT(paramFound(const QString &, const QVariant &)));
  connect(cmdline, SIGNAL(parseError(const QString &)),
          this, SLOT(parseError(const QString &)));

  cmdline->parse();
}

void
Test::switchFound(const QString & name)
{
  qWarning() << "Switch:" << name;
}

void
Test::optionFound(const QString & name, const QVariant & value)
{
  qWarning() << "Option:" << name << value.toString();
}

void
Test::paramFound(const QString & name, const QVariant & value)
{
  qWarning() << "Param:" << name << value.toString();
}

void
Test::parseError(const QString & error)
{
  qWarning() << "cool";
  qWarning() << qPrintable(error);
  cmdline->showHelp(true, -1);
  QCoreApplication::quit();
}
