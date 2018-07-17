#ifndef QTOBII_DEV_TRACK_H
#define QTOBII_DEV_TRACK_H

#include <QMainWindow>

// Forward declaration
namespace Ui { class QTobiiDevTrackWindow; }

namespace qtobii {
class QTobiiDevTrack : public QMainWindow {

  Q_OBJECT

public:
  explicit QTobiiDevTrack(QWidget *parent = 0);
  ~QTobiiDevTrack();

private:
  Ui::QTobiiDevTrackWindow *ui;

};
} // namespace qtobii

#endif // QTOBII_DEV_TRACK_H
