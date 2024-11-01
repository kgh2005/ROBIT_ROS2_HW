#ifndef chatter_gui_MAIN_WINDOW_H
#define chatter_gui_MAIN_WINDOW_H

/*****************************************************************************
** Includes
*****************************************************************************/

#include <QMainWindow>
#include "QIcon"
#include <QString>
#include <QLabel>
#include <QPushButton>
#include "chatter_gui/talker_node.hpp"
#include "chatter_gui/listener_node.hpp"

#include "ui_mainwindow.h"

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  std::shared_ptr<Talker> talker_node;     // talker 노드 객체
  std::shared_ptr<Listener> listener_node; // listener 노드 객체
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

private slots:
  void on_btn_send_clicked();
  void displayMessage(const QString& msg);

private:
  Ui::MainWindowDesign* ui;

  QLineEdit* messageInput;        // 메시지 입력 필드
  QLabel* receivedMessageLabel;   // 수신 메시지 표시 라벨

  void closeEvent(QCloseEvent* event);
};

#endif  // chatter_gui_MAIN_WINDOW_H
