
#pragma once

#include <QString>

class Command {
public:
  Command(const QString command_text);
  ~Command();

  void execute();

  QString get_command_text() { return user_input; }
  void set_command_text(const QString value) { user_input = value; }
  QString get_result() { return m_result; }
  QString get_return_code() { return m_return_code; }

private:
  QString user_input;
  QString m_result;
  QString m_return_code;
};