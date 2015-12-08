#pragma once

#ifndef KILO_DIALOG_PARTICLE_LIST_HPP
#define KILO_DIALOG_PARTICLE_LIST_HPP

/**
 * This file is a part of Kilo project.
 * Kilo - basic physical particles' interaction simulator
 *
 * @project Kilo
 * @author k1-801
 */

#include <QDialog>
#include <QTreeWidgetItem>

namespace Kilo
{
    namespace Ui
    {
        class DialogParticleList;
    }

    class DialogParticleList : public QDialog
    {
        Q_OBJECT

        private:
            Ui::DialogParticleList *ui;

            void _update();

        public:
            explicit DialogParticleList(QWidget *parent = 0);
            ~DialogParticleList();
            void run();

        private slots:
            void on_particleList_itemActivated(QTreeWidgetItem*, int);
    };
}

#endif // KILO_DIALOG_PARTICLE_LIST_HPP
