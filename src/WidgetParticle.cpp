#include "../include/WidgetParticle.hpp"

/**
 * This file is a part of Kilo project.
 * Kilo - basic physical particles' interaction simulator
 *
 * @project Kilo
 * @author k1-801
 */

// HCL
#include <HCL/Exception.hpp>

namespace Kilo
{
    WidgetParticle::WidgetParticle(QWidget* parent) : QTableWidget(parent)
    {
        update();
    }

    void WidgetParticle::update()
    {
        clear();
        ParticleSP p2 = _p.lock();
        if(p2)
        {
            QTableWidgetItem* header = new QTableWidgetItem;
            header->setText(p2->getName());
            setHorizontalHeaderItem(0, header);

            QVector<ParticleField*>& fields = p2->getFields();
            int i;
            ParticleField* curr;
            this->setRowCount(fields.size());
            for(i = 0; i < fields.size(); ++i)
            {
                curr = fields[i];
                QTableWidgetItem* name  = new QTableWidgetItem;
                QTableWidgetItem* value = new QTableWidgetItem;
                name ->setText( curr->name);
                value->setText(*curr->getValue());
                setVerticalHeaderItem(i, name);
                setItem(i, 0, value);
            }
        }
        else
        {
            QTableWidgetItem* header = new QTableWidgetItem;
            header->setText(tr("[No particle selected]"));
            setHorizontalHeaderItem(0, header);
        }
    }

    void WidgetParticle::setParticle(ParticleWP p)
    {
        ParticleSP sp = p.lock();
        if(sp)
        {
            _p = sp;
            update();
        }
        else
        {
            throw Hcl::Exception("WidgetParticle::setParticle(): Null pointer");
        }
    }

    void WidgetParticle::change(int num)
    {
        ParticleSP sp = _p.lock();
        if(sp)
        {
            QVector<ParticleField*>& fields = sp->getFields();
            QTableWidgetItem* item = this->item(num, 0);
            fields[num]->setValue(item->text());
            QString* buf = fields[num]->getValue();
            item->setText(*buf);
            delete buf;
        }
    }
}

