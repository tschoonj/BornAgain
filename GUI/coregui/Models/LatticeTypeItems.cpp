// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/LatticeTypeItems.cpp
//! @brief     Implements classes LatticeTypeItems
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "LatticeTypeItems.h"

const QString BasicLatticeTypeItem::P_LATTICE_LENGTH1 = "Lattice_length_1";
const QString BasicLatticeTypeItem::P_LATTICE_LENGTH2 = "Lattice_length_2";
const QString BasicLatticeTypeItem::P_LATTICE_ANGLE = "Lattice_angle";
const QString SquareLatticeTypeItem::P_LATTICE_LENGTH = "Lattice_length";
const QString HexagonalLatticeTypeItem::P_LATTICE_LENGTH = "Lattice_length";


BasicLatticeTypeItem::BasicLatticeTypeItem()
    : SessionItem(QString("BasicLatticeType"))
{
    addProperty(P_LATTICE_LENGTH1, 20.0);
    addProperty(P_LATTICE_LENGTH2, 20.0);
    addProperty(P_LATTICE_ANGLE, 90.0);
}

SquareLatticeTypeItem::SquareLatticeTypeItem()
    : SessionItem(QString("SquareLatticeType"))
{
    addProperty(P_LATTICE_LENGTH, 20.0);
}

HexagonalLatticeTypeItem::HexagonalLatticeTypeItem()
    : SessionItem(QString("HexagonalLatticeType"))
{
    addProperty(P_LATTICE_LENGTH, 20.0);
}
