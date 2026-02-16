#include "ChatModel.h"

// Qt
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkRequest>
#include <QUrl>

ChatModel::ChatModel(QObject *parent) : QAbstractListModel(parent)
{
    _network = new QNetworkAccessManager(this);
    connect(_network, &QNetworkAccessManager::finished, this, &ChatModel::onReplyFinished);
}

ChatModel::~ChatModel()
{
    if (_network != Q_NULLPTR)
        _network->deleteLater();
}

void ChatModel::appendMessage(const QString &role, const QString &content)
{
    beginInsertRows(QModelIndex(), _messages.count(), _messages.count());
    _messages.append({role, content, QDateTime::currentDateTime()});

    endInsertRows();
}

void ChatModel::clear()
{
    beginResetModel();

    _messages.clear();

    endResetModel();
}

void ChatModel::setRemoteUrl(const QString &url)
{
    if (_remoteUrl != url)
    {
        _remoteUrl = url;
        
        emit remoteUrlChanged();
    }
}

void ChatModel::sendMessage(const QString &message)
{
    if (message.isEmpty())
        return;

    appendMessage("user", message);
    
    if (_remoteUrl.isEmpty())
    {
        appendMessage("assistant", "Error: Remote URL not configured.");
        return;
    }

    setProcessing(true);

    QUrl url(_remoteUrl);
    if (!url.isValid()) {
         appendMessage("assistant", "Error: Invalid Remote URL.");
         setProcessing(false);
         return;
    }
    
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // Construct JSON payload
    QJsonObject userMessage;
    userMessage["role"] = "user";
    userMessage["content"] = message;

    QJsonArray messagesArray;
    messagesArray.append(userMessage);

    QJsonObject payload;
    payload["model"] = "llama"; 
    payload["messages"] = messagesArray;
    payload["stream"] = false; 

    QJsonDocument doc(payload);
    _network->post(request, doc.toJson());
}

QString ChatModel::remoteUrl() const
{
    return _remoteUrl;
}

void ChatModel::onReplyFinished(QNetworkReply *reply)
{
    setProcessing(false);
    
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray response = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(response);
        QJsonObject obj = doc.object();
        
        // Parse OpenAI format response
        if (obj.contains("choices") && obj["choices"].isArray())
        {
            QJsonArray choices = obj["choices"].toArray();
            if (!choices.isEmpty())
            {
                QJsonObject choice = choices[0].toObject();
                if (choice.contains("message") && choice["message"].isObject()) {
                    QJsonObject message = choice["message"].toObject();
                    QString content = message["content"].toString();
                    appendMessage("assistant", content);
                }
            }
        }
        else
        {
            appendMessage("assistant", "Error: Received unexpected response format.");
        }
    }
    else
    {
        QString errorStr = reply->errorString();

        QByteArray response = reply->readAll();

        appendMessage("assistant", QString("Error: Network/Server Error (%1). %2").arg(statusCode).arg(errorStr));
    }
    
    reply->deleteLater();
}

void ChatModel::toggleTheme()
{
    setIsDarkTheme(!_isDarkTheme);
}

bool ChatModel::isDarkTheme() const
{
    return _isDarkTheme;
}

void ChatModel::setIsDarkTheme(bool isDark)
{
    if (_isDarkTheme != isDark)
    {
        _isDarkTheme = isDark;
        emit isDarkThemeChanged();
    }
}

bool ChatModel::isProcessing() const
{
    return _isProcessing;
}

void ChatModel::setProcessing(bool processing)
{
    if (_isProcessing != processing)
    {
        _isProcessing = processing;
        emit isProcessingChanged();
    }
}

int ChatModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return _messages.count();
}

QVariant ChatModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const ChatMessage &msg = _messages[index.row()];
    switch (role)
    {
    case RoleRole:
        return msg.role;
    case ContentRole:
        return msg.content;
    case TimestampRole:
        return msg.timestamp;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> ChatModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[RoleRole] = "role";
    roles[ContentRole] = "content";
    roles[TimestampRole] = "timestamp";
    return roles;
}
