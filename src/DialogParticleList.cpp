#include "../include/DialogParticleList.hpp"
#include "ui_DialogParticleList.h"

/**
 * This file is a part of Kilo project.
 * Kilo - basic physical particles' interaction simulator
 *
 * @project Kilo
 * @author k1-801
 */

#include "../include/Universe.hpp"

namespace Kilo
{
    DialogParticleList::DialogParticleList(QWidget *parent) : QDialog(parent), ui(new Ui::DialogParticleList)
    {
        ui->setupUi(this);
    }

    DialogParticleList::~DialogParticleList()
    {
        delete ui;
    }

    void DialogParticleList::_update()
    {
        ui->particleList->clear();
        Universe::getInstance();
    }

    void DialogParticleList::run()
    {
        setModal(true);
        show();
        exec();
    }

    void DialogParticleList::on_particleList_itemActivated(QTreeWidgetItem* item, int)
    {
        ui->particle->setParticle(ui->particleList->_c[item].first);
    }

    void DialogParticleList::on_particle_cellChanged(int row, int)
    {
        ui->particle->change(row);
    }

    void DialogParticleList::on_pushButtonClose_clicked()
    {
        close();
    }
}

