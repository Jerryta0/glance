#ifndef FOLDERTREEVIEW_H
#define FOLDERTREEVIEW_H

#include <QTreeView>


class FolderTreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit FolderTreeView(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // FOLDERTREEVIEW_H