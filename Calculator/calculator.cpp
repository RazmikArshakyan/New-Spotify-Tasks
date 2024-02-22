#include "calculator.h"
#include "ui_calculator.h"

#include <QRegularExpression>

struct Triggers {
    inline static bool divideTrigger = false;
    inline static bool multTrigger = false;
    inline static bool addTrigger = false;
    inline static bool subTrigger = false;
    inline static bool probTrigger = false;
};

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    setMaximumSize(QSize(495, 664));
    setMinimumSize(QSize(495, 664));
    ui->setupUi(this);

    ui->Display->setText(QString::number(calcValue));
    QPushButton* numButtons[10];
    for (int i = 0; i < 10; ++i) {
        QString buttonName = "Button" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton*>(buttonName);
        connect(numButtons[i], SIGNAL(released()), this,
                SLOT(NumPressed()));
    }

    connect(ui->Add, SIGNAL(released()), this,
            SLOT(OperationButtonPressed()));
    connect(ui->Divide, SIGNAL(released()), this,
            SLOT(OperationButtonPressed()));
    connect(ui->Multiply, SIGNAL(released()), this,
            SLOT(OperationButtonPressed()));
    connect(ui->Subtract, SIGNAL(released()), this,
            SLOT(OperationButtonPressed()));
    connect(ui->Probabiliity, SIGNAL(released()), this,
            SLOT(OperationButtonPressed()));

    connect(ui->Equals, SIGNAL(released()), this,
            SLOT(EqualButtonPressed()));

    connect(ui->ChangeSign, SIGNAL(released()), this,
            SLOT(ChangeNumberSignPressed()));

    connect(ui->Clear, SIGNAL(released()), this,
            SLOT(ACPressed()));

    connect(ui->FloatingPoint, SIGNAL(released()), this,
            SLOT(CommaPressed()));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumPressed()
{
    QPushButton* button = (QPushButton*)sender();
    QString buttonValue = button->text();
    QString displayValue = ui->Display->text();

    if (displayValue.toDouble() == 0)
        ui->Display->setText(buttonValue);
    else {
        QString newValue = displayValue + buttonValue;
        double doubleNewValue = newValue.toDouble();
        ui->Display->setText(QString::number(doubleNewValue, 'g', 15));
    }
}

void Calculator::OperationButtonPressed()
{
    Triggers::divideTrigger = false;
    Triggers::addTrigger = false;
    Triggers::subTrigger = false;
    Triggers::multTrigger = false;
    Triggers::probTrigger = false;

    QString displayValue = ui->Display->text();
    calcValue = displayValue.toDouble();

    QPushButton* button = (QPushButton*)sender();
    QString buttonValue = button->text();

    if (QString::compare(buttonValue, "/", Qt::CaseInsensitive) == 0) {
        Triggers::divideTrigger = true;
    }
    else if (QString::compare(buttonValue, "+", Qt::CaseInsensitive) == 0) {
        Triggers::addTrigger = true;
    }
    else if (QString::compare(buttonValue, "*", Qt::CaseInsensitive) == 0) {
        Triggers::multTrigger = true;
    }
    else if (QString::compare(buttonValue, "-", Qt::CaseInsensitive) == 0) {
        Triggers::subTrigger = true;
    }
    else if (QString::compare(buttonValue, "%", Qt::CaseInsensitive) == 0) {
        Triggers::probTrigger = true;
    }
    ui->Display->setText("");
}

void Calculator::EqualButtonPressed()
{
    double solution = 0.0;
    QString displayValue = ui->Display->text();
    double doubleDisplayValue = displayValue.toDouble();

    if (Triggers::addTrigger || Triggers::divideTrigger || Triggers::multTrigger
        || Triggers::subTrigger || Triggers::probTrigger) {
        if (Triggers::addTrigger)
            solution = calcValue + doubleDisplayValue;
        else if (Triggers::divideTrigger)
            solution = calcValue / doubleDisplayValue;
        else if (Triggers::multTrigger)
            solution = calcValue * doubleDisplayValue;
        else if (Triggers::subTrigger)
            solution = calcValue - doubleDisplayValue;
        else
            solution = fmod(calcValue, doubleDisplayValue);
    }
    ui->Display->setText(QString::number(solution));
}

void Calculator::ChangeNumberSignPressed()
{
    QString displayValue = ui->Display->text();
    static const QRegularExpression reg("[-]?[0-9.]*");

    if (reg.match(displayValue).hasMatch()) {
        double doubleDisplayValue = displayValue.toDouble();
        double doubleDisplayValueSigned = -1 * doubleDisplayValue;
        ui->Display->setText(QString::number(doubleDisplayValueSigned));
    }
}

void Calculator::ACPressed()
{
    ui->Display->clear();

    calcValue = 0.0;
    Triggers::divideTrigger = false;
    Triggers::addTrigger = false;
    Triggers::subTrigger = false;
    Triggers::multTrigger = false;
    Triggers::probTrigger = false;
}

void Calculator::CommaPressed()
{
    QString displayText = ui->Display->text();

    if (!displayText.contains(".")) {
        displayText += ".";
        ui->Display->setText(displayText);
    }
}
