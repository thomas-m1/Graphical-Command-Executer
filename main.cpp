#include "mainwindow.h"

#include <QApplication>

/**
 * @name   main
 * @brief  Initializes, runs, and waits for QApplication and MainWindow to finish.
 * @param  argc: the number of arguments passed into this program
 * @param  argv: the arguments passed into this program
 * @return the return value of QApplication.exec()
 */
int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  MainWindow mainWindow;
  mainWindow.show();
  return app.exec();
}