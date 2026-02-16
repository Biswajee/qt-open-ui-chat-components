#include "ChatModel.h"

// Qt
#include <QGuiApplication>
#include <QQuickView>
#include <QQmlEngine>
#include <QQmlContext>
#include <QQuickItem>
#include <QQuickStyle>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickStyle::setStyle("Basic");

    QQuickView view;
    view.setTitle("Qt Open UI Chat Example");
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.resize(480, 800);

    view.engine()->addImportPath("qrc:/");

    ChatModel model;

    model.appendMessage("assistant", "Hello! Please connect to a server to start chatting.");

    view.setSource(QUrl("qrc:/ChatExample/Main.qml"));

    if (view.status() == QQuickView::Error)
        return -1;

    QQuickItem *root = view.rootObject();
    if (root)
        root->setProperty("chatModel", QVariant::fromValue(&model));
    else
        return -1;


    view.show();

    return app.exec();
}
