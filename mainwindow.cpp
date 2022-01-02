
#include "mainwindow.h"

#include <QFont>
#include <QFontDatabase>

/**
 * @name   MainWindow::MainWindow
 * @brief  Initializes the MainWindow and its widgets
 * @param  parent: the optional parent QWidget of this MainWindow
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  command_label = new QLabel("Command:");
  user_input = new QLineEdit("");
  execute_button = new QPushButton("Execute");
  output_label = new QLabel("Output");
  output_text_box = new QTextEdit("");
  exit_status_label = new QLabel("Exit Status:");
  horizontal_line = new QFrame();
  exit_status_result = new QLabel("0");
  history_label = new QLabel("History");
  history_text_box_list = new QListWidget();

  // Equalize the width of all characters
  const QFont fixed_font = QFontDatabase::systemFont(QFontDatabase::FixedFont);

  user_input->setFont(fixed_font);
  output_text_box->setFont(fixed_font);
  output_text_box->setReadOnly(true);
  horizontal_line->setFrameShape(QFrame::HLine);  // Add a horizontal bar
  horizontal_line->setFrameShadow(QFrame::Sunken);
  history_text_box_list->setFont(fixed_font);

  // Automatically layout the widgets
  m_layout = new QGridLayout();
  m_layout->addWidget(command_label, 0, 0);
  m_layout->addWidget(user_input, 0, 1);
  m_layout->addWidget(execute_button, 0, 2);
  m_layout->addWidget(output_label, 1, 0, 1, 3);
  m_layout->addWidget(output_text_box, 2, 0, 1, 3);
  m_layout->addWidget(exit_status_label, 3, 0);
  m_layout->addWidget(exit_status_result, 3, 1);
  m_layout->addWidget(horizontal_line, 4, 0, 1, 3);
  m_layout->addWidget(history_label, 5, 0);
  m_layout->addWidget(history_text_box_list, 6, 0, 1, 3);

  // QMainWindow already has a layout.
  // To set a custom layout, we need to assign the layout to a widget,
  // and set the widget as the central widget of the window.
  m_centralWidget = new QWidget();
  m_centralWidget->setLayout(m_layout);
  setCentralWidget(m_centralWidget);

  setWindowTitle("CommandGUI");
  resize(600, 800);

  // Execute command when execute button is clicked
  connect(execute_button, &QPushButton::released, this, &MainWindow::handleExecute);
  // Execute command when return is pressed
  connect(user_input, &QLineEdit::returnPressed, this, &MainWindow::handleExecute);
  // Update command result when a different item is selected in the history list
  connect(history_text_box_list, &QListWidget::currentRowChanged, this, &MainWindow::handleHistorySwitched);
}

/**
 * @name   MainWindow::handleExecute
 * @brief  Retrieves the command text from the GUI, executes it,
 *         and adds the command along with its result to the history list.
 */
void MainWindow::handleExecute() {
  Command command(user_input->text());
  command.execute();

  // Generate a string to be displayed in the history list
  const QString next_index = QString::number(m_commands.size() + 1);
  const QString history_item_string = QString("%1. %2 (%3)").arg(next_index, command.get_command_text(), command.get_return_code());

  m_commands.push_back(command);
  history_text_box_list->addItem(history_item_string);

  // Select the last item in the history list, also trigger currentRowChanged
  history_text_box_list->setCurrentRow(m_commands.size() - 1);
}

/**
 * @name   MainWindow::handleHistorySwitched
 * @brief  Updates the command text, the result, and the return code
 *         based on the currently selected command in the history list.
 */
void MainWindow::handleHistorySwitched() {
  const int row = history_text_box_list->currentRow();
  user_input->setText(m_commands[row].get_command_text());
  output_text_box->setText(m_commands[row].get_result());
  exit_status_result->setText(m_commands[row].get_return_code());
}