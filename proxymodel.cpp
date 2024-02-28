#include "proxymodel.h"

ProxyModel::ProxyModel(QObject* parent) :
    QObject(parent),
    p_main_layout(new QVBoxLayout()),
    p_model(new QStandardItemModel(5,1)),
    p_proxy_model(new QSortFilterProxyModel()),
    p_line_edit(new QLineEdit()),
    p_list_view_sotred(new QListView)
{
    for(int i = 0; i < 5; ++i) {
        auto index = p_model->index(i, 0);
        p_model->setData(index, QString(('a'+i) + "pedik"));
    }
    p_proxy_model->setSourceModel(p_model);
    p_list_view_sotred->setModel(p_proxy_model);
    p_main_layout->addWidget(p_line_edit);
    p_main_layout->addWidget(p_list_view_sotred);
    QObject::connect(p_line_edit, &QLineEdit::textEdited, this, &ProxyModel::setFilter);
}

ProxyModel::~ProxyModel()
{
    delete p_main_layout;
    delete p_model;
    delete p_proxy_model;
    delete p_line_edit;
    delete p_list_view_sotred;
}

void ProxyModel::setFilter(const QString &reg)
{
    QString cast_reg = const_cast<QString&>(reg);
    cast_reg += '*';
    p_proxy_model->setFilterWildcard(reg);
}

QVBoxLayout* ProxyModel::getLayout()
{
    return p_main_layout;
}

