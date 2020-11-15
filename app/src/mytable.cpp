#include "general.h"

MyTable::MyTable(Mediator *mediator, QWidget *parent) :
                        QTableView(parent), Component(mediator)
{
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setModel(model);
    setSortingEnabled(true);
    verticalHeader()->setVisible(false);
    horizontalHeader()->setMinimumSectionSize(50);
    setShowGrid(false);
    setContextMenuPolicy(Qt::CustomContextMenu);
    horizontalHeader()->setStretchLastSection(true);
    setAlternatingRowColors(true);

    mainMenu = new QMenu(this);
    editAction = new QAction(tr("&Edit tag"), this);
    mainMenu->addAction(editAction); 
    removeAction = new QAction(tr("&Remove from media"), this);
    mainMenu->addAction(removeAction);
    playlistMenu = new QMenu(tr("&Add to playlist"));
    mainMenu->addMenu(playlistMenu);

    connect(this, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(sendNextSong(const QModelIndex &)));
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(showContextMenuRequested(const QPoint &))); 
    connect(removeAction, SIGNAL(triggered()), this, SLOT(removeSong()));
    connect(this , SIGNAL(removeSong(int)), reinterpret_cast<const QObject *>(mediator), SLOT(removeSong(int)));

    setItemDelegate(new StarDelegate);
}

MyTable::~MyTable()
{

}

void MyTable::removeSong() {
    emit removeSong(model->rowData(currentIndex())->getId());
    model->remove(currentIndex());
}

void MyTable::sendNextSong(const QModelIndex &index) {
    emit sendSongToPlayer(getModel()->rowData(index));
    emit updateQueue(getModel()->rowData(index));
}

void MyTable::showContextMenuRequested(const QPoint &pos) {
    QModelIndex index = indexAt(pos);

    if (index.isValid()) {
        for (QAction *action : playlistActions) {
            delete action;
        }
        playlistActions.clear();
        for (Playlist *playlist : mediator->getGeneralScreen()->getSidebar()->getList()->getModel()->data()) {
            if (playlist->getId() != mediator->currentPlaylist) {
                playlistActions.push_back(new QAction(playlist->getName().toString()));
                connect(playlistActions[playlistActions.size() - 1], &QAction::triggered, [this, playlist, index]() {
                            this->mediator->getLibraryManager()->addSongToPlaylist(playlist->getId(), model->rowData(index)->getId());
                        });
                playlistMenu->addAction(playlistActions[playlistActions.size() - 1]);
            }
        }
        if (mediator->currentPlaylist == -1) {
            removeAction->setText(tr("&Remove from media"));
        }
        else {
            removeAction->setText(tr("&Remove from playlist"));
        }
        editAction->disconnect();
        connect(editAction, &QAction::triggered, [this, index]() {

            // if (index.column() != this->model->columnCount() - 1) {
                this->model->setEditable(true);
                edit(index);
                this->model->setEditable(false);
            // }
            // else {
            //     QMessageBox::warning(this, "Alert", "You do not have permissions\nto change this file.");
            // }
        });
        mainMenu->popup(viewport()->mapToGlobal(pos));
    }
}