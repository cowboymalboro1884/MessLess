#include "project_chat.h"
#include "ui_project_chat.h"

ProjectChat::ProjectChat(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ProjectChat)
{
  ui->setupUi(this);
}

ProjectChat::~ProjectChat()
{
  delete ui;
}
