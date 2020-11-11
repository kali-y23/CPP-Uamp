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
    action_import_recursive = new QAction(("Add songs from this directory recursively"), this);

    connect(action_import, SIGNAL(triggered()), SLOT(importSong()));
    connect(action_import_recursive, SIGNAL(triggered()), SLOT(importSongRecursive()));
    connect(this, SIGNAL(songImported(const QString&, bool)), reinterpret_cast<const QObject *>(mediator), SLOT(initImport(const QString &, bool)));
}

MyTreeView::~MyTreeView() {
    delete model_filesystem;
    delete context_menu;
    delete action_import;
    delete action_import_recursive;
}

void MyTreeView::mouseDoubleClickEvent(QMouseEvent *event) {
    QModelIndex index = currentIndex();

    if (!model_filesystem->isDir(index))
        action_import->triggered();
    else
        expand(index);
}

void MyTreeView::mousePressEvent(QMouseEvent *event) {
    QTreeView::mousePressEvent(event);
    QModelIndex index = currentIndex();

    context_menu->clear();
    context_menu->addAction(action_import);

    if (event->button() == Qt::RightButton) {
        if (model_filesystem->isDir(index)) {
            context_menu->addAction(action_import_recursive);
            action_import->setText("Add songs from this directory");
        }
        else
            action_import->setText("Add song");
        context_menu->popup(this->mapToGlobal(event->pos()));
    }
}

void MyTreeView::importSong() {
    QString path = model_filesystem->filePath(currentIndex());

    emit songImported(path, false);
}

void MyTreeView::importSongRecursive() {
    QString path = model_filesystem->filePath(currentIndex());

    emit songImported(path, true);
}
