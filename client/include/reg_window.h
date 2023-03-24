#ifndef REG_WINDOW_H
#define REG_WINDOW_H

#include <QWidget>

namespace Ui {
class reg_window;
}

class reg_window : public QWidget {
  Q_OBJECT

public:
  explicit reg_window(QWidget *parent = nullptr);
  ~reg_window();
  QString getName();
  QString getSurname();
  QString getPass();
  QString getBio();
  QString getCompName();
  QString getConfPass();
  bool checkPass();

signals:
  void register_button_clicked2();

private slots:
  void on_nameLineEdit_textEdited(const QString &arg1);
  void on_passwordLineEdit_textEdited(const QString &arg1);
  void on_confirmLineEdit_textEdited(const QString &arg1);
  void on_registerPushButton_clicked();

  void on_surnameLineEdit_textEdited(const QString &arg1);

  void on_companyNameLineEdit_textEdited(const QString &arg1);

  void on_companyBioLineEdit_textEdited(const QString &arg1);

private:
  Ui::reg_window *ui;
  QString m_userName;
  QString m_userSurname;
  QString m_userPass;
  QString m_confirmation;
  QString m_companyName;
  QString m_companyBio;
};

#endif // REG_WINDOW_H
