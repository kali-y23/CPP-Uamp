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
    removeAction = new QAction(tr("&Remove from media"), this);
    mainMenu->addAction(removeAction);
    playlistMenu = mainMenu->addMenu(tr("&Add to playlist"));

    connect(this, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(sendNextSong(const QModelIndex &)));
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(showContextMenuRequested(const QPoint &))); 
}

MyTable::~MyTable()
{

}

void MyTable::sendNextSong(const QModelIndex &index) {
    emit sendSongToPlayer(getModel()->rowData(index));
}

void MyTable::showContextMenuRequested(const QPoint &pos) {
    QModelIndex index = currentIndex();

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
        mainMenu->popup(viewport()->mapToGlobal(pos));
    }
}