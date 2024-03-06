#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private slots:
    void NumPressed();
    void OperationButtonPressed();
    void EqualButtonPressed();
    void ChangeNumberSignPressed();
    void ACPressed();
    void CommaPressed();

private:
    Ui::Calculator *ui;
    double calcValue = 0.0;
};
#endif 
