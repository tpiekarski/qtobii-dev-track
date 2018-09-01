#ifndef QTOBIILOGGINGINTERFACE_H
#define QTOBIILOGGINGINTERFACE_H

#include <QObject>
#include <QString>

namespace qtobii {
class QTobiiLoggingInterface {

public:
  virtual ~QTobiiLoggingInterface() {
    // Only defined to make sure all destructors will be called along inheritance.
  }

  enum MessageType {
    DATA,
    DEBUG,
    MESSAGE
  };

public slots:
  virtual void debug(QString message) = 0;
  virtual void data(QString message) = 0;
  virtual void log(QString message) = 0;

};
} // namespace qtobii

#endif // QTOBIILOGGINGINTERFACE_H
