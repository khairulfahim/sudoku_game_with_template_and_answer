/*
#include "widget.h"

#include <QPainter>
#include <QDebug>
#include <QTextStream>
#include <QMessageBox>
#include <QFile>
#include <QLabel>

#include <map>
#include <vector>

using namespace std;

Window::Window(QWidget *parent) : QWidget(parent)
{
    // set form size
    setFixedSize(400,600);
    setWindowTitle("Sudoku");
    for (int i=0; i<9; i++){
        for (int j=0; j<9; j++){
            sudoku[i][j] = 0;
        }
    }
    readDataFromFile("C:/Qt/sudoku_1.txt");

}

Window::~Window(){}

void Window::readDataFromFile(const QString& fileName){
    QFile file (fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Failed to open file" << fileName;
        return;
    }
    QTextStream in(&file);
    int row = 0;
    while(!in.atEnd() && row<9){
        QString line  = in.readLine();
        for(int col = 0; col < line.length() && col<9; ++col){
            QChar ch = line.at(col);
            if (ch.isDigit()){
                sudoku[row][col] = ch.digitValue();}
            else{
                sudoku[row][col] = 0;
            }
        }
        ++row;
    }
    file.close();
    qDebug() << "file loaded: " << fileName;
}

void Window::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    QPen pen;
    QFont font;

    float boxWidth = 400 / 9;
    float boxHeight = 600 / 9;
    for(int i=0; i<=9; i++){
        for(int j=0; j<=9; j++){
            if (i % 3 == 0){
                painter.setPen(QPen(Qt::black, 3));
            }
            else {
                painter.setPen(QPen(Qt::cyan, 2));
            }
            painter.drawLine(i*boxWidth, 0, i*boxWidth, 600); //vertical
            painter.drawLine(0, i*boxHeight, 400, i*boxHeight); //horizontal
        }
    }
    painter.setPen(QPen(Qt::white, 3));
    for (int i=0; i<9; i++){
        for (int j=0; j<9; j++){
            painter.drawText((j + 0.5) * boxWidth - 10, (i + 0.5) * boxHeight + 10, QString::number(sudoku[i][j]));

        }
    }
}

void Window::mouseReleaseEvent(QMouseEvent * event)
{
    // get click position
    qDebug() << "Mouse x " << event->x() << " Mouse y " << event->y();
}*/

#include "widget.h"

Window::Window(QWidget *parent) : QWidget(parent)
{
    setFixedSize(400, 400);
    setWindowTitle("Sudoku");
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            sudoku[i][j] = 0;
        }
    }

    QPushButton *openButton = new QPushButton("Open", this);
    openButton->setGeometry(10, 10, 80, 30);
    connect(openButton, SIGNAL(clicked()), this, SLOT(openFile()));

    QPushButton *checkButton = new QPushButton("Check", this);
    checkButton->setGeometry(100, 10, 80, 30);
    connect(checkButton, SIGNAL(clicked()), this, SLOT(checkSudoku()));
}

Window::~Window() {}

void Window::readDataFromFile(const QString& fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Failed to open file: " + fileName);
        return;
    }

    QTextStream in(&file);
    int row = 0;
    while (!in.atEnd() && row < 9) {
        QString line = in.readLine();
        for (int col = 0; col < line.length() && col < 9; ++col) {
            QChar ch = line.at(col);
            if (ch.isDigit()) {
                sudoku[row][col] = ch.digitValue();
            } else {
                sudoku[row][col] = 0;
            }
        }
        ++row;
    }
    file.close();
    update();
}

void Window::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::black, 2));

    float boxWidth = width() / 9.0;
    float boxHeight = height() / 9.0;

    for (int i = 1; i <= 9; i++) {
        if (i % 3 == 0)
            painter.setPen(QPen(Qt::black, 3));
        else
            painter.setPen(QPen(Qt::black, 1));
        painter.drawLine(i * boxWidth, 0, i * boxWidth, height());
        painter.drawLine(0, i * boxHeight, width(), i * boxHeight);
    }

    QFont font = painter.font();
    font.setPointSizeF(20);
    painter.setFont(font);

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            int value = sudoku[i][j];
            if (value != 0) {
                painter.drawText((j + 0.5) * boxWidth - 10, (i + 0.5) * boxHeight + 10, QString::number(value));
            }
        }
    }
}

void Window::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint pos = event->pos();
    QPoint cell = clickedCell(pos);
    if (cell.x() != -1 && cell.y() != -1) {
        sudoku[cell.y()][cell.x()]++; // Increase the value in the clicked cell
        if (sudoku[cell.y()][cell.x()] > 9) { // Limit the value to 9
            sudoku[cell.y()][cell.x()] = 1; // Wrap around to 1 if it exceeds 9
        }
        update();
    }
}


QPoint Window::clickedCell(const QPoint& pos)
{
    int boxWidth = width() / 9;
    int boxHeight = height() / 9;
    int col = pos.x() / boxWidth;
    int row = pos.y() / boxHeight;
    if (col >= 0 && col < 9 && row >= 0 && row < 9) {
        return QPoint(col, row);
    } else {
        return QPoint(-1, -1);
    }
}

void Window::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open Sudoku File", "", "Text Files (*.txt)");
    if (!fileName.isEmpty()) {
        readDataFromFile(fileName);
    }
}

void Window::checkSudoku()
{
    // Implement Sudoku validation logic here
    // Display QMessageBox with result
}

