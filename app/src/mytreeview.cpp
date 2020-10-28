#include "mytreeview.h"

MyTreeView::MyTreeView(const Mediator *mediator) : Component(mediator) {
    model_filesystem = new QFileSystemModel();
    model_filesystem->setRootPath(QDir::homePath());
    model_filesystem->setNameFilters(mediator->getLibraryManager()->getMask()->text().split(" "));
    model_filesystem->setNameFilterDisables(false);

    setModel(model_filesystem);
    setRootIndex(model_filesystem->index(QDir::homePath()));

    hideColumn(1);
    hideColumn(2);
    hideColumn(3);

    context_menu = new QMenu(this);
    action_import = new QAction((""), this);

    connect(action_import, SIGNAL(triggered()), SLOT(importSong()));
    connect(this, SIGNAL(songImported(const QString&)), reinterpret_cast<const QObject *>(mediator), SLOT(initImport(const QString &)));

    context_menu->addAction(action_import);
}

MyTreeView::~MyTreeView() {
    delete model_filesystem;
    delete context_menu;
    delete action_import;
}

void MyTreeView::mouseDoubleClickEvent(QMouseEvent *event) {
    QModelIndex index = currentIndex();

    if (!model_filesystem->isDir(index)) {
        action_import->triggered();
    }
    else {
        expand(index);
    }
}

void MyTreeView::mousePressEvent(QMouseEvent *event) {
    QTreeView::mousePressEvent(event);
    QModelIndex index = currentIndex();

    if (event->button() == Qt::RightButton) {
        if (model_filesystem->isDir(index))
            action_import->setText("Add songs from this directory");
        else
            action_import->setText("Add song");
        context_menu->popup(this->mapToGlobal(event->pos()));
    }
}

void MyTreeView::importSong() {
    QString path = model_filesystem->filePath(currentIndex());

    emit songImported(path);
}
