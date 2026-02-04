#include "ChatFrame.h"
#include <QVBoxLayout>
#include <QListView>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QStyleSheet>

ChatFrame::ChatFrame(QWidget *parent) : QFrame(parent) {
    setupUI();
    loadStyles();
}

void ChatFrame::setupUI() {
    QVBoxLayout *layout = new QVBoxLayout(this);
    
    messageListView = new QListView(this);
    messageInput = new QLineEdit(this);
    sendButton = new QPushButton("Send", this);

    layout->addWidget(messageListView);
    layout->addWidget(messageInput);
    layout->addWidget(sendButton);

    connect(sendButton, &QPushButton::clicked, this, &ChatFrame::sendMessage);
    connect(messageInput, &QLineEdit::returnPressed, this, &ChatFrame::sendMessage);
    
    setLayout(layout);
}

void ChatFrame::sendMessage() {
    QString message = messageInput->text();
    if (!message.isEmpty()) {
        // Logic to add message to the list view
        // For example, you could use a QStringListModel to manage the messages
        messageInput->clear();
    }
}

void ChatFrame::loadStyles() {
    QFile styleFile(":/styles/open_web_ui.qss");
    if (styleFile.open(QFile::ReadOnly)) {
        QString styleSheet = styleFile.readAll();
        this->setStyleSheet(styleSheet);
        styleFile.close();
    }
}