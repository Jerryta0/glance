#ifndef QTABPAGEWIDGET_H
#define QTABPAGEWIDGET_H

#include <QWidget>
#include <QTabWidget>

/**
* @author taojiayu
* @date 2020-07-19
* @desc tab控件
*/
class TabPageWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit TabPageWidget(QWidget *parent = nullptr);
    //默认设置
    void defaultSetting();
    //只添加一次
    int addTabOnly(QWidget *widget, const QString &);

signals:

};

#endif // QTABPAGEWIDGET_H
