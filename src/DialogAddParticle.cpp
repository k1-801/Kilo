#include "src/DialogAddParticle.hpp"
#include "ui_DialogAddParticle.h"

namespace Kilo {

DialogAddParticle::DialogAddParticle(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddParticle)
{
    ui->setupUi(this);
}

DialogAddParticle::~DialogAddParticle()
{
    delete ui;
}

} // namespace Kilo
