#ifndef PROXYMODEL_H
#define PROXYMODEL_H

#include <QObject>
#include <QVBoxLayout>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include <QLineEdit>
#include <QListView>

class ProxyModel : public QObject
{
    Q_OBJECT
private:
    QVBoxLayout* p_main_layout;
    QStandardItemModel* p_model;
    QSortFilterProxyModel* p_proxy_model;
    QLineEdit* p_line_edit;
    QListView* p_list_view_sotred;
public:
    ProxyModel(QObject* parent = nullptr);
    virtual ~ProxyModel();
public slots:
    void setFilter(const QString &reg);
public:
    QVBoxLayout* getLayout();
};

#endif // PROXYMODEL_H
