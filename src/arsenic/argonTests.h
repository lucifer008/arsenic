#ifndef ARGONTESTS_H
#define ARGONTESTS_H

#include <QDialog>

namespace Ui {
class ArgonTests;
}

class ArgonTests : public QDialog
{
    Q_OBJECT

public:
    explicit ArgonTests(QWidget *parent = nullptr);
    ~ArgonTests();

private:
    const QScopedPointer<Ui::ArgonTests> m_ui;
};

#endif // ARGONTESTS_H
