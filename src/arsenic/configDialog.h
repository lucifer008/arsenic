#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>
#include <QSettings>
#include <QScopedPointer>

namespace Ui {
class ConfigDialog;
}

class ConfigDialog : public QDialog {
    Q_OBJECT

  public:
    explicit ConfigDialog(QWidget* parent = nullptr);
    ~ConfigDialog();
    void loadSettings();

  private slots:
    void saveSettings();
    // void reject();

  private:
    const QScopedPointer<Ui::ConfigDialog> m_ui;
};

#endif // CONFIGDIALOG_H
