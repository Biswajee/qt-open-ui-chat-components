#ifndef CHATFRAME_H
#define CHATFRAME_H

#include <QFrame>
#include <QListView>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QStringListModel>

class ChatFrame : public QFrame {
    Q_OBJECT

public:
    explicit ChatFrame(QWidget *parent = nullptr);
    void addMessage(const QString &message);

private:
    void setupUI();
    QListView *messageListView;
    QLineEdit *inputField;
    QStringListModel *model;
    QVBoxLayout *layout;
};

#endif // CHATFRAME_H