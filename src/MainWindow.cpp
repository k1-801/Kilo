#include "../include/MainWindow.hpp"
#include "ui_MainWindow.h"

/**
 * This file is a part of Kilo project.
 * Kilo - basic physical particles' interaction simulator
 *
 * @project Kilo
 * @author k1-801
 */

// Qt
#include <QPushButton>
#include <QFileDialog>
#include <QLibraryInfo>

#include "../include/Core.hpp"
#include "../include/DialogParticleList.hpp"
#include "../include/Runner.hpp"
#include "../include/WidgetAxis.hpp"

namespace Kilo
{
    MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
    {
        // Translator
        _locale = QLocale::system().name();
        _trKilo.load(":/lang/Kilo_" + _locale);
        _trQt  .load("qt_"          + _locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
        qApp->installTranslator(&_trKilo);
        qApp->installTranslator(&_trQt);

        ui->setupUi(this);
        ui->retranslateUi(this);

        connect(ui->actionOpen,   &QAction::triggered, this, &MainWindow::_open);
        connect(ui->actionSave,   &QAction::triggered, this, &MainWindow::_save);
        connect(ui->actionSaveAs, &QAction::triggered, this, &MainWindow::_saveAs);
        connect(ui->actionReload, &QAction::triggered, this, &MainWindow::_reload);
        connect(ui->actionRun,    &QAction::triggered, this, &MainWindow::run);
        connect(ui->actionStop,   &QAction::triggered, this, &MainWindow::stop);

        Core  * c = &Core::getInstance();
        Runner* r = &Runner::getInstance();
        WidgetModel* m = ui->widgetModel;
        connect(this, &MainWindow::destroyed,    r,    &Runner     ::stop);
        connect(this, &MainWindow::destroyed,    c,    &Core       ::quit);
        connect(this, &MainWindow::run,          r,    &Runner     ::simRun);
        connect(this, &MainWindow::stop,         r,    &Runner     ::simStop);
        connect(this, &MainWindow::open,         c,    &Core       ::open);
        connect(this, &MainWindow::save,         c,    &Core       ::save);
        connect(this, &MainWindow::clear,        c,    &Core       ::clear);
        connect(this, &MainWindow::changeZoom,   m,    &WidgetModel::changeZoom);
        connect(r,    &Runner    ::stateChanged, this, &MainWindow ::on_runnerStateChanged);
    }

    MainWindow::~MainWindow()
    {
        delete ui;
    }

    QString MainWindow::_openDialog()
    {
        return QFileDialog::getOpenFileName(NULL, tr("Open model"), "", tr("Kilo model file(*.kmf)"));
    }

    QString MainWindow::_saveDialog()
    {
        return QFileDialog::getSaveFileName(NULL, tr("Save model"), "", tr("Kilo model file (*.kmf)"));
    }

    void MainWindow::_open()
    {
        emit stop();
        QString p = _openDialog();
        if(!p.isEmpty())
        {
            if(QFile::exists(p))
            {
                emit open(p);
            }
        }
    }

    void MainWindow::_save()
    {
        emit stop();
        if(_path.isEmpty())
            _saveAs();
        else
            emit save(_path);
    }

    void MainWindow::_saveAs()
    {
        emit stop();
        emit save(_saveDialog());
    }

    void MainWindow::_reload()
    {
        emit open(Core::getInstance().getPath());
    }

    void MainWindow::_clear()
    {
        emit stop();
        emit clear();
    }

    void MainWindow::_list()
    {
        emit stop();
        DialogParticleList d;
        d.run();
    }

// UI slots
    void MainWindow::on_pushButtonOpen_clicked        (){_open  ();}
    void MainWindow::on_pushButtonSave_clicked        (){_save  ();}
    void MainWindow::on_pushButtonSaveAs_clicked      (){_saveAs();}
    void MainWindow::on_pushButtonReload_clicked      (){_reload();}
    void MainWindow::on_pushButtonRun_clicked         (){emit run  ();}
    void MainWindow::on_pushButtonStop_clicked        (){emit stop ();}
    void MainWindow::on_pushButtonClear_clicked       (){emit clear();}
    void MainWindow::on_pushButtonParticleList_clicked(){_list();}

// Runner button state updater
    void MainWindow::on_runnerStateChanged(bool s)
    {
        ui->pushButtonRun   ->setDisabled(s);
        ui->    actionRun   ->setDisabled(s);
        ui->pushButtonStop  ->setDisabled(!s);
        ui->    actionStop  ->setDisabled(!s);

        ui->pushButtonOpen  ->setDisabled(s);
        ui->    actionOpen  ->setDisabled(s);
        ui->pushButtonSave  ->setDisabled(s);
        ui->    actionSave  ->setDisabled(s);
        ui->pushButtonSaveAs->setDisabled(s);
        ui->    actionSaveAs->setDisabled(s);
    }

    void MainWindow::on_horizontalSliderPrecision_valueChanged (){_modChange();}
    void MainWindow::on_horizontalSliderShadow_valueChanged    (){_modChange();}
    void MainWindow::on_horizontalSliderZoom_valueChanged      (){_modChange();}
    void MainWindow::on_horizontalSliderSmartclean_valueChanged(){_modChange();}
    void MainWindow::on_checkBoxAutoclean_toggled  (){_modChange();}
    void MainWindow::on_checkBoxSpheres_toggled    (){_modChange();}
    void MainWindow::on_checkBoxTraectories_toggled(){_modChange();}
    void MainWindow::on_checkBoxSmartclean_toggled (){_modChange();}

    void MainWindow::modReceiver(int precision, int shadow, int smartclean, int zoom, bool ac, bool sc, bool sp, bool tr)
    {
        ui->horizontalSliderPrecision ->setValue(precision);
        ui->horizontalSliderShadow    ->setValue(shadow);
        ui->horizontalSliderSmartclean->setValue(smartclean);
        ui->horizontalSliderZoom      ->setValue(zoom);
        ui->checkBoxAutoclean  ->setChecked(ac);
        ui->checkBoxSpheres    ->setChecked(sp);
        ui->checkBoxTraectories->setChecked(tr);
        ui->checkBoxSmartclean ->setChecked(sc);
    }
    void MainWindow::_modChange()
    {
        Core::getInstance().setModparams(
                    ui->horizontalSliderPrecision ->value(),
                    ui->horizontalSliderShadow    ->value(),
                    ui->horizontalSliderSmartclean->value(),
                    ui->horizontalSliderZoom      ->value(),
                    ui->checkBoxAutoclean  ->isChecked(),
                    ui->checkBoxSmartclean ->isChecked(),
                    ui->checkBoxSpheres    ->isChecked(),
                    ui->checkBoxTraectories->isChecked());
        emit changeZoom(Core::getInstance().getZoom());
    }
}
