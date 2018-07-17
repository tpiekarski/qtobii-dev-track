#include "qtobii-dev-track.h"
#include <QApplication>

using namespace qtobii;

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  QTobiiDevTrack devTrack;
  devTrack.show();

  return app.exec();
}
