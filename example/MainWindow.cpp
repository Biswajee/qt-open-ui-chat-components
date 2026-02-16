#include "MainWindow.h"
#include <QVBoxLayout>
#include <QResizeEvent>
#include "ChatFrame.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Chat Application");
    resize(800, 600);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    ChatFrame *chatFrame = new ChatFrame(this);
    layout->addWidget(chatFrame);

    centralWidget->setLayout(layout);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
}