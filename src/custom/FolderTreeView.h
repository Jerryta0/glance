#ifndef FOLDERTREEVIEW_H
#define FOLDERTREEVIEW_H

#include <QTreeView>

/**
* @author taojiayu
* @date 2020-07-19
* @desc 文件树
*/
class FolderTreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit FolderTreeView(QWidget *parent = nullptr);

    void defaultSetting();

signals:

public slots:
};

#endif // FOLDERTREEVIEW_H
