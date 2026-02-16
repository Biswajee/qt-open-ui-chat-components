#ifndef CHATMODEL_H
#define CHATMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QString>
#include <QDateTime>
#include <QtQml/qqml.h>
#include <QNetworkAccessManager>
#include <QNetworkReply>

struct ChatMessage {
    QString role; // "user" or "assistant"
    QString content;
    QDateTime timestamp;
};

enum ChatRoles {
    RoleRole = Qt::UserRole + 1,
    ContentRole,
    TimestampRole
};

class ChatModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(bool isDarkTheme READ isDarkTheme WRITE setIsDarkTheme NOTIFY isDarkThemeChanged)
    Q_PROPERTY(bool isProcessing READ isProcessing NOTIFY isProcessingChanged)
    Q_PROPERTY(QString remoteUrl READ remoteUrl WRITE setRemoteUrl NOTIFY remoteUrlChanged)

public:
    ChatModel(QObject *parent = Q_NULLPTR);
    ~ChatModel();

    Q_INVOKABLE void clear();
    Q_INVOKABLE void appendMessage(const QString &role, const QString &content);
    
    Q_INVOKABLE void sendMessage(const QString &message);
    
    QString remoteUrl() const;
    Q_INVOKABLE void setRemoteUrl(const QString &url);


    Q_INVOKABLE void toggleTheme();
    bool isDarkTheme() const;
    void setIsDarkTheme(bool isDark);
    
    bool isProcessing() const;

signals:
    void isDarkThemeChanged();
    void isProcessingChanged();
    void remoteUrlChanged();

private slots:
    void onReplyFinished(QNetworkReply *reply);

private:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    QList<ChatMessage>              _messages;
    bool                            _isDarkTheme{false};
    bool                            _isProcessing{false};
    QString                         _remoteUrl;

    QNetworkAccessManager*          _network{Q_NULLPTR};

    void setProcessing(bool processing);
};

#endif // CHATMODEL_H
