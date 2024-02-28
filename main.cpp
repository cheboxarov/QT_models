#include "mainwindow.h"

#include <QApplication>
#include <QStringListModel>
#include <QTreeView>
#include <QListView>
#include <QTableView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileSystemModel>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QStandardItemModel>
#include <proxymodel.h>

class SimpleDelegate : public QStyledItemDelegate {
public:
    SimpleDelegate(QObject* parent = nullptr) : QStyledItemDelegate(parent)
    {

    }

    void paint(QPainter* pPainter, const QStyleOptionViewItem& option,
               const QModelIndex& index) const
    {
        if (option.state & QStyle::State_MouseOver) {
            QRect rect= option.rect;
            QLinearGradient gradient(0,0,rect.width(), rect.height());
            gradient.setColorAt(0, Qt::white);
            gradient.setColorAt(0.2, Qt::blue);
            gradient.setColorAt(1, Qt::green);
            pPainter->setBrush(gradient);
            pPainter->drawRect(rect);
        }
        QStyledItemDelegate::paint(pPainter, option, index);
    }

    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex index) const
    {
        return QSize(option.rect.width(), option.rect.height());
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    QWidget wgt;
    QStringListModel model;
    model.setStringList(QStringList() << "1lst" << "2lst" << "3lst");
    QModelIndex index = model.index(1,0, QModelIndex());
    model.setData(index, "penis", Qt::WhatsThisRole);
    qDebug() << index.data().toString();

    QTreeView* pTreeView = new QTreeView;
    pTreeView->setModel(&model);

    QListView* pListView = new QListView;
    pListView->setModel(&model);
    pListView->setItemDelegate(new SimpleDelegate(pListView));
    pListView->viewport()->setAttribute(Qt::WA_Hover);


    QTableView* pTableView = new QTableView;
    pTableView->setModel(&model);

    QItemSelectionModel selection(&model);
    pTreeView->setSelectionModel(&selection);
    pListView->setSelectionModel(&selection);
    pTableView->setSelectionModel(&selection);

    QHBoxLayout* phbLayout = new QHBoxLayout;
    phbLayout->addWidget(pTreeView);
    phbLayout->addWidget(pListView);
    phbLayout->addWidget(pTableView);

    QFileSystemModel* fileSysModel = new QFileSystemModel;
    QTreeView* pfileTreeView = new QTreeView;
    fileSysModel->setRootPath(QDir::rootPath());
    pfileTreeView->setModel(fileSysModel);

    QTableView* pTableFileView = new QTableView;
    pTableFileView->setModel(fileSysModel);

    QObject::connect(pfileTreeView, &QTreeView::clicked, pTableFileView, &QTableView::setRootIndex);
    QObject::connect(pTableFileView, &QTableView::activated, pfileTreeView, &QTreeView::setCurrentIndex);
    QObject::connect(pTableFileView, &QTableView::activated, pTableFileView, &QTableView::setRootIndex);

    QHBoxLayout* pFileLayout = new QHBoxLayout;
    pFileLayout->addWidget(pfileTreeView);
    pFileLayout->addWidget(pTableFileView);

    QStandardItemModel* pMyModel = new QStandardItemModel(5,3);
    for(int i = 0; i < 5; ++i) {
        for(int j = 0; j < 3; ++j) {
            auto index = pMyModel->index(i, j);
            pMyModel->setData(pMyModel->index(i, j), QString::number(i) + " " + QString::number(j));
        }
    }

    QTableView* pMyTable = new QTableView();
    pMyTable->setModel(pMyModel);

    ProxyModel proxy_model;
    QVBoxLayout* p_m_layout = proxy_model.getLayout();

    QVBoxLayout* pMainLayout = new QVBoxLayout;
    pMainLayout->addLayout(phbLayout);
    pMainLayout->addLayout(pFileLayout);
    pMainLayout->addWidget(pMyTable);
    pMainLayout->addLayout(p_m_layout);

    wgt.setLayout(pMainLayout);

    wgt.show();

    return a.exec();
}
