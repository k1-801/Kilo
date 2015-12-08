#pragma once

#ifndef KILO_MAIN_WINDOW_HPP_INCLUDED
#define KILO_MAIN_WINDOW_HPP_INCLUDED

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

        signals:
            void open(QString);
            void save(QString);

            void run();
            void stop();
            void clear();
    };
}

#endif // KILO_MAIN_WINDOW_HPP_INCLUDED
