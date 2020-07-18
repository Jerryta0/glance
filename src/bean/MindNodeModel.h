#ifndef MINDNODEMODEL_H
#define MINDNODEMODEL_H

#include <QObject>

class MindNodeModel
{
public:
    // 主键 google的风格 变量注释
    qint32 id;
    //创建时间 QDateTime::currentMSecsSinceEpoch()
    qint64 created;
    qint64 modified;
    QString content;
    QList<MindNodeModel> children;
    MindNodeModel();
};

#endif // MINDNODEMODEL_H
