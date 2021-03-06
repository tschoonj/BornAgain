// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/SplashScreen.cpp
//! @brief     Implements class SplashScreen
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "SplashScreen.h"
#include "GUIHelpers.h"
#include <QStyleOptionProgressBarV2>

SplashScreen::SplashScreen(QWidget *parent) :
    QSplashScreen(parent),m_percentage_done(0)

{
    m_width = 480;
    m_height = 380;

    this->setPixmap(QPixmap(":/images/splashscreen.png"));
    this->setCursor(Qt::BusyCursor);

    QFont font;
    font.setPointSize(10);
    font.setBold(false);
    this->setFont(font);
}

void SplashScreen::setProgress(int value)
{
    m_percentage_done = value;
    if (m_percentage_done > 100)
        m_percentage_done = 100;
    if (m_percentage_done < 0)
        m_percentage_done = 0;
    update();
}

void SplashScreen::drawContents(QPainter *painter)
{
    QSplashScreen::drawContents(painter);

    QRect textRect( 15.0, m_height-40, 100, 30);

    QString versionText = QString("version ").append(GUIHelpers::getBornAgainVersionString());
    style()->drawItemText(painter, textRect, 0, this->palette(), true, versionText);

    QString loadingText("loading . ");
    for(size_t i=0; i<size_t(m_percentage_done/20); ++i) {
        loadingText.append(". ");
    }

    QRect loadingRect( 380.0, m_height-40, 100, 30);
    style()->drawItemText(painter, loadingRect, 0, this->palette(), true, loadingText);

}
