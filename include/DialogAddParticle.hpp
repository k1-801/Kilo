#ifndef KILO_DIALOG_ADD_PARTICLE_HPP
#define KILO_DIALOG_ADD_PARTICLE_HPP

#include <QDialog>

namespace Kilo {

namespace Ui {
class DialogAddParticle;
}

class DialogAddParticle : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddParticle(QWidget *parent = 0);
    ~DialogAddParticle();

private:
    Ui::DialogAddParticle *ui;
};


} // namespace Kilo
#endif // KILO_DIALOG_ADD_PARTICLE_HPP
