#include "LatticeTypeItems.h"
#include "Units.h"

const QString BasicLatticeTypeItem::P_LATTICE_LENGTH1 = "Lattice_length_1";
const QString BasicLatticeTypeItem::P_LATTICE_LENGTH2 = "Lattice_length_2";
const QString BasicLatticeTypeItem::P_LATTICE_ANGLE = "Lattice_angle";
const QString SquareLatticeTypeItem::P_LATTICE_LENGTH = "Lattice_length";
const QString HexagonalLatticeTypeItem::P_LATTICE_LENGTH = "Lattice_length";


BasicLatticeTypeItem::BasicLatticeTypeItem(ParameterizedItem *parent)
    : ParameterizedItem(QString("BasicLatticeType"), parent)
{
    setItemName("BasicLatticeType");
    registerProperty(P_LATTICE_LENGTH1, 20.0);
    registerProperty(P_LATTICE_LENGTH2, 20.0);
    registerProperty(P_LATTICE_ANGLE, 90.0);
}

SquareLatticeTypeItem::SquareLatticeTypeItem(ParameterizedItem *parent)
    : ParameterizedItem(QString("SquareLatticeType"), parent)
{
    setItemName("SquareLatticeType");
    registerProperty(P_LATTICE_LENGTH, 20.0);
}

HexagonalLatticeTypeItem::HexagonalLatticeTypeItem(ParameterizedItem *parent)
    : ParameterizedItem(QString("HexagonalLatticeType"), parent)
{
    setItemName("HexagonalLatticeType");
    registerProperty(P_LATTICE_LENGTH, 20.0);
}