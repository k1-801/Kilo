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

// Qt
#include <QDialog>
#include <QTreeWidgetItem>
// Kilo
#include "AbstractParticle.hpp"

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
            ParticleWP _p;
            void _update();
            void _loadParticle(ParticleWP);
            void _setParticle(ParticleWP);

        public:
            explicit DialogParticleList(QWidget *parent = 0);
            ~DialogParticleList();
            void run();

        private slots:
            void on_particleList_itemActivated(QTreeWidgetItem*, int);
            void on_particle_cellChanged(int row, int column);
            void on_pushButtonClose_clicked();
    };
}

#endif // KILO_DIALOG_PARTICLE_LIST_HPP
