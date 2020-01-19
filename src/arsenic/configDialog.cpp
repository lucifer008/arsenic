#include "configDialog.h"
#include "Config.h"
#include "ui_configDialog.h"
#include "constants.h"
#include <QCheckBox>
#include <QLineEdit>
#include <QComboBox>
#include <QMessageBox>

ConfigDialog::ConfigDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::ConfigDialog)
{
    m_ui->setupUi(this);
    connect(this, SIGNAL(accepted()), SLOT(saveSettings()));
    //connect(this, SIGNAL(rejected()), SLOT(reject()));
    connect(m_ui->checkBox_empty, SIGNAL(toggled(bool)),
                m_ui->spinBox_clip, SLOT(setEnabled(bool)));
    loadSettings();
}

/*******************************************************************************

*******************************************************************************/

ConfigDialog::~ConfigDialog()
{

}

/*******************************************************************************

*******************************************************************************/

void ConfigDialog::loadSettings()
{
    if (config()->hasAccessError()) {
            QString warn_text = QString(tr("Access error for config file %1").arg(config()->getFileName()));
            QMessageBox::warning(this, tr("Could not load configuration"), warn_text);
        }

    m_ui->editExtension->setText(config()->get("extension").toString());
    m_ui->comboMemory->setCurrentIndex(config()->get("CRYPTO/argonMemory").toInt());
    m_ui->comboOps->setCurrentIndex(config()->get("CRYPTO/argonItr").toInt());
    m_ui->comboAlgo->setCurrentText(config()->get("CRYPTO/cryptoAlgo").toString());
    m_ui->editName->setText(config()->get("userName").toString());
    m_ui->spinBox_clip->setValue(config()->get("SECURITY/clearclipboardtimeout").toInt());
    m_ui->checkBox_empty->setChecked(config()->get("SECURITY/clearclipboard").toBool());
}

/*******************************************************************************

*******************************************************************************/

void ConfigDialog::saveSettings()
{
    config()->set("extension",                         m_ui->editExtension->text());
    config()->set("CRYPTO/argonMemory",                m_ui->comboMemory->currentIndex());
    config()->set("CRYPTO/argonItr",                   m_ui->comboOps->currentIndex());
    config()->set("CRYPTO/cryptoAlgo",                 m_ui->comboAlgo->currentText());
    config()->set("userName",                          m_ui->editName->text());
    config()->set("SECURITY/clearclipboardtimeout",    m_ui->spinBox_clip->value());
    config()->set("SECURITY/clearclipboard",           m_ui->checkBox_empty->isChecked());
}

/*******************************************************************************

*******************************************************************************/

