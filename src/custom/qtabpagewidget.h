#ifndef QTABPAGEWIDGET_H
#define QTABPAGEWIDGET_H

#include <QWidget>
#include <QTabWidget>

class QTabPageWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit QTabPageWidget(QWidget *parent = nullptr);
    //默认设置
    void defaultSetting();
    //只添加一次
    int addTabOnly(QWidget *widget, const QString &);

signals:

};

#endif // QTABPAGEWIDGET_H
