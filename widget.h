/*
#ifndef WINDOW_H
#define WINDOW_H

#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QWidget>
#include <QMouseEvent>
#include <vector>
#include <map>

using namespace std;

class Window : public QWidget
{
    Q_OBJECT
    int sudoku[9][9];
    void readDataFromFile(const QString& fileName);

public:
    Window(QWidget *parent = 0);
    ~Window();

protected:
    void paintEvent(QPaintEvent *event);
    void mouseReleaseEvent(QMouseEvent * event);

};

#endif*/
#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QFileDialog>
#include <QPushButton>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>

class Window : public QWidget
{
    Q_OBJECT

public:
    Window(QWidget *parent = nullptr);
    ~Window();

protected:
    void paintEvent(QPaintEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void openFile();
    void checkSudoku();

private:
    int sudoku[9][9];
    void readDataFromFile(const QString& fileName);
    QPoint clickedCell(const QPoint& pos);
};

#endif // WINDOW_H
