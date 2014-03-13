#ifndef JOBPROPERTIESWIDGET_H
#define JOBPROPERTIESWIDGET_H

#include <QWidget>
#include <QMap>

class QtProperty;
class QtVariantProperty;
class JobQueueModel;
class JobQueueItem;

//! Widget to show and change properties of currently selected JobQueueItem
//! Left buttom corner of JobQueueView

class JobPropertiesWidget : public QWidget
{
    Q_OBJECT
public:
    explicit JobPropertiesWidget(QWidget *parent = 0);

    void setModel(JobQueueModel *model);

public slots:
    void itemClicked(JobQueueItem *item);

private slots:
    void valueChanged(QtProperty *property, const QVariant &value);


private:
    void updateExpandState();
    void addProperty(QtVariantProperty *property, const QString &id);

    JobQueueModel *m_jobQueueModel;
    class QtVariantPropertyManager *m_variantManager;
    class QtTreePropertyBrowser *m_propertyBrowser;
    QMap<QtProperty *, QString> propertyToId;
    QMap<QString, QtVariantProperty *> idToProperty;
    QMap<QString, bool> idToExpanded;

    JobQueueItem *m_currentItem;
};



#endif
