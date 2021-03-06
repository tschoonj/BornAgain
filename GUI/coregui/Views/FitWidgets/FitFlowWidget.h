// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitFlowWidget.h
//! @brief     Defines class FitFlowWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef FITFLOWWIDGET_H
#define FITFLOWWIDGET_H

#include "WinDllMacros.h"
#include <QFrame>

class HistogramPlot;
class FitSuiteItem;

//! The FitFlowWidget class is intended for showing chi2 .vs interation count dependency.
//! The main goal is to fill vacant place in FitComparisonWidget.

//  FIXME Switch to SessionItemWidget

class BA_CORE_API_ FitFlowWidget : public QFrame
{
    Q_OBJECT
public:
    explicit FitFlowWidget(QWidget *parent = 0);
    ~FitFlowWidget();

    void setItem(FitSuiteItem *fitSuiteItem);

private:
    HistogramPlot *m_histPlot;
    FitSuiteItem *m_fitSuiteItem;
    QVector<double> m_x;
    QVector<double> m_y;
};



#endif // FITFLOWWIDGET_H

