#include "qtobii-dev-track.h"
#include "ui_qtobii-dev-track-window.h"

namespace qtobii {

QTobiiDevTrack::QTobiiDevTrack(QWidget *parent)
  : QMainWindow(parent), ui(new Ui::QTobiiDevTrackWindow) {

  ui->setupUi(this);
}

QTobiiDevTrack::~QTobiiDevTrack() {
  if (ui != nullptr) {
    delete ui;
    ui = nullptr;
  }
}

} // namesapce qtobii
