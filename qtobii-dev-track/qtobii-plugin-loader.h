#ifndef QTOBIIPLUGINLOADER_H
#define QTOBIIPLUGINLOADER_H

#include "../qtobii-plugin-interface/qtobii-plugin-interface.h"
#include <QDir>
#include <QFileInfo>
#include <QObject>
#include <tobii_streams.h>

namespace qtobii {
class QTobiiPluginLoader : public QObject {

  Q_OBJECT

public:
  explicit QTobiiPluginLoader(QObject* parent = nullptr) : QObject(parent) {}
  QTobiiPlugin<tobii_gaze_point_callback_t, void*>* loadGazePointPlugin(QFileInfo* pluginFile);

};
} // namespace qtobii

#endif // QTOBIIPLUGINLOADER_H
