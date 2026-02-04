#include "MainWindow.h"
#include <QVBoxLayout>
#include <QResizeEvent>
#include "ChatFrame.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Chat Application");
    resize(800, 600);

    // Create a central widget and set it as the main window's central widget
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Create a vertical layout
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    // Create and add the ChatFrame to the layout
    ChatFrame *chatFrame = new ChatFrame(this);
    layout->addWidget(chatFrame);

    // Set the layout to the central widget
    centralWidget->setLayout(layout);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    // Handle any additional resizing logic if needed
}