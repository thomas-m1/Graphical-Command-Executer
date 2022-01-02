#pragma once

#include <QFrame>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>

#include "command.h"

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);

// Forbid copy
private:
  MainWindow(const MainWindow &);

private slots:
  void handleExecute();
  void handleHistorySwitched();

private:
  std::vector<Command> m_commands;

  // Widgets
  QLabel *command_label;
  QLineEdit *user_input;
  QPushButton *execute_button;
  QLabel *output_label;
  QTextEdit *output_text_box;
  QLabel *exit_status_label;
  QLabel *exit_status_result;
  QFrame *horizontal_line;
  QLabel *history_label;
  QListWidget *history_text_box_list;
  QGridLayout *m_layout;
  QWidget *m_centralWidget;
};