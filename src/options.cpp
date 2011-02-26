#include "qcommandline.h"
#include <QApplication>
#include <QDebug>
#include <QVariant>
#include <QString>

#include "options.h"

Options::Options()
{

    static const struct QCommandLineConfigEntry conf[] =
    {
      { QCommandLine::Option, 'i', "proxy", "Proxy IP Address", QCommandLine::Optional },
      { QCommandLine::Option, 'p', "port", "Proxy Port", QCommandLine::Optional },
      { QCommandLine::Param, '\0', "file", "The Script File", QCommandLine::Mandatory },
      { QCommandLine::Param, '\0', "args", "Arguments", QCommandLine::OptionalMultiple },
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
Options::switchFound(const QString & name)
{

}

void
Options::optionFound(const QString & name, const QVariant & value)
{
    if("proxy" == name.toAscii()){
        this->proxy =  value.toString();
    }
    else if("port" == name.toAscii()){
        this->port = value.toString();
    }

}

void
Options::paramFound(const QString & name, const QVariant & value)
{
    if("file" == name.toAscii()){
        this->file = value.toString();
    }
    else if("args" == name.toAscii()){
        this->args.append(value.toString());
    }
}

void
Options::parseError(const QString & error)
{
  qWarning() << qPrintable(error);
  cmdline->showHelp(true, -1);
  QCoreApplication::quit();
}

