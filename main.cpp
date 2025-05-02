#include <QApplication>
#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>

#include <QDebug>

void setBtnProp(QPushButton* btn) {
    btn->setMinimumHeight(45);
    QFont btnFont("Arial", 14, 700);
    btn->setFont(btnFont);
    btn->setCursor(Qt::PointingHandCursor);
}

void writeNum(int num, QLineEdit* view) {
    if(view->text() == "0")
        view->setText("");
    view->setText(view->text() + QString::number(num));
}

void writePlus(QLineEdit* view)
{
    QString text = view->text().at(view->text().length() - 1);
    if(text == "+" || text == "-") return;
    view->setText(view->text() + "+");
}

void writeMinus(QLineEdit* view)
{
    QString text = view->text().at(view->text().length() - 1);
    if(text == "+" || text == "-") return;
    view->setText(view->text() + "-");
}

void clear(QLineEdit* view) {
    view->setText("0");
}

int cal(QChar op, int sum, int num)
{
    switch (op.toLatin1()) {
    case '+':
        sum += num;
        break;
    case '-':
        sum -= num;
        break;
    }
    return sum;
}

void sum(QLineEdit* view) {
    QString text = view->text().at(view->text().length() - 1);
    if(text == "+" || text == "-") return;
    view->setText(view->text() + "=");

    QStringList list = view->text().split("", Qt::SkipEmptyParts);

    QString num = "";
    int sum = 0;
    QChar op = QChar::Null;
    for (const QString &ch : list) {
        if(ch == "-" || ch == "+" || ch == "=")
        {
            if(op.isNull()){
                sum += num.toInt();
            } else {
                sum = cal(op, sum, num.toInt());
            }
            op = ch.at(0);
            num = "";
        } else
            num += ch;
    }

    view->setText(view->text() + QString::number(sum));

}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;

    // layouts
    QVBoxLayout* mainLayout = new QVBoxLayout();
    QVBoxLayout* topLayout = new QVBoxLayout();
    QHBoxLayout* middleLayout = new QHBoxLayout();
    QGridLayout* numberBtnLayout = new QGridLayout();
    QVBoxLayout* opBtnLayout = new QVBoxLayout();

    // Objects
    QLineEdit* view = new QLineEdit();
    view->setText("0");
    QFont font("Arial", 20, 700);
    view->setFont(font);
    view->setAlignment(Qt::AlignBottom);

    QPushButton* buttons[12];


    // Operator Button
    QPushButton* sumBtn = new QPushButton("=");
    setBtnProp(sumBtn);
    QObject::connect(sumBtn, &QPushButton::clicked, [&app, &view]() {
        sum(view);
    });
    opBtnLayout->addWidget(sumBtn);

    QPushButton* plusBtn = new QPushButton("+");
    setBtnProp(plusBtn);
    QObject::connect(plusBtn, &QPushButton::clicked, [&app, &view]() {
        writePlus(view);
    });
    opBtnLayout->addWidget(plusBtn);

    QPushButton* minusBtn = new QPushButton("-");
    setBtnProp(minusBtn);
    QObject::connect(minusBtn, &QPushButton::clicked, [&app, &view]() {
        writeMinus(view);
    });


    opBtnLayout->addWidget(minusBtn);

    QPushButton* clearBtn = new QPushButton("C");
    setBtnProp(clearBtn);

    QObject::connect(clearBtn, &QPushButton::clicked, [&app, &view]() {
        clear(view);
    });

    opBtnLayout->addWidget(clearBtn);

    opBtnLayout->setAlignment(Qt::AlignBottom);
    opBtnLayout->setDirection(QBoxLayout::BottomToTop);

    // Property
    //sumBtn->setC

    // Add Number Button

    for(int i = 0, j = 0; i < 12; i++, j++){
        QString txtBtn;

        txtBtn = QString::number(j);

        if(i==0){
            txtBtn = "+/-";
            j--;
        }

        if(i==2) {
            txtBtn = ".";
            j--;
        }
        buttons[i] = new QPushButton(txtBtn);
        QObject::connect(buttons[i], &QPushButton::clicked, [&app, &view, j]() {
            writeNum(j, view);
        });
        setBtnProp(buttons[i]);
        numberBtnLayout->addWidget(buttons[i], 4-i/3, i%3);
    }

    middleLayout->addLayout(numberBtnLayout);
    middleLayout->addLayout(opBtnLayout);

    topLayout->addWidget(view);
    view->setReadOnly(true);
    view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(middleLayout);

    window.setLayout(mainLayout);

    window.show();

    return app.exec();
}
