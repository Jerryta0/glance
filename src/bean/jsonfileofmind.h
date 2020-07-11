#ifndef JSONFILEOFMIND_H
#define JSONFILEOFMIND_H
#include "mindnodemodel.h"
#include <QObject>

//qt中怎么添加文件夹
//1.在外面新建文件夹
//创建cpp文件在这个文件夹
class JsonFileOfMind
{
public:
    MindNodeModel root;
    JsonFileOfMind();
};

#endif // JSONFILEOFMIND_H
