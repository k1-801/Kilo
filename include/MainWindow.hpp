#pragma once

#ifndef KILO_MAIN_WINDOW_HPP_INCLUDED
#define KILO_MAIN_WINDOW_HPP_INCLUDED

/**
 * This file is a part of Kilo project.
 * Kilo - basic physical particles' interaction simulator
 *
 * @project Kilo
 * @author k1-801
 */

// Qt
#include <QMainWindow>
#include <QString>
#include <QTranslator>

namespace Kilo
{
    namespace Ui
    {
        class MainWindow;
    }
    class MainWindow;
}

namespace Kilo
{
    class MainWindow : public QMainWindow
    {
        Q_OBJECT

        private:
            Ui::MainWindow* ui;
            QString     _path;
            QString     _locale;
            QTranslator _trKilo;
            QTranslator _trQt;

            QString _openDialog();
            QString _saveDialog();

        private:
            void _open();
            void _save();
            void _saveAs();
            void _reload();
            void _clear();
            void _list();
            void _modChange();

        public:
            MainWindow(QWidget *parent = 0);
            ~MainWindow();
            void modReceiver(int, int, int, int, bool, bool, bool, bool);

        private slots:
            void on_pushButtonOpen_clicked();
            void on_pushButtonSave_clicked();
            void on_pushButtonSaveAs_clicked();
            void on_pushButtonReload_clicked();
            void on_pushButtonClear_clicked();
            void on_pushButtonRun_clicked();
            void on_pushButtonStop_clicked();
            void on_pushButtonParticleList_clicked();

            void on_horizontalSliderPrecision_valueChanged ();
            void on_horizontalSliderShadow_valueChanged    ();
            void on_horizontalSliderZoom_valueChanged      ();
            void on_horizontalSliderSmartclean_valueChanged();
            void on_checkBoxAutoclean_toggled  ();
            void on_checkBoxSpheres_toggled    ();
            void on_checkBoxTraectories_toggled();
            void on_checkBoxSmartclean_toggled ();

    public slots:
            void on_runnerStateChanged(bool);
            void close();

        signals:
            void open(QString);
            void save(QString);

            void run();
            void stop();
            void clear();
            void changeZoom(long double);
            void quit();
    };
}

#endif // KILO_MAIN_WINDOW_HPP_INCLUDED
