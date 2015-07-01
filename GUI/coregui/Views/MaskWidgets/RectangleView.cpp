
#include "RectangleView.h"
#include "RectangleItem.h"
#include <iostream>
#include <cmath>
#include "ParameterizedItem.h"



RectangleView::RectangleView() : m_resizeMode(false), m_rotationMode(false)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
}


// FIXME Color of items should be centrally defined, we use DesignerHelper.h
void RectangleView::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{

    // paint rectangle
    painter->setRenderHints(QPainter::Antialiasing);
    this->prepareGeometryChange();
    if (m_item->getRegisteredProperty(RectangleItem::P_COLOR).toInt() == 0) {
        QBrush transRed(QColor(0xFF, 0, 0, 0x80));
        painter->fillRect(0, 0, m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal(),
                          m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal(),
                          transRed);
    } else {
        QBrush transBlue(QColor(0, 0, 0xFF, 0x80));
        painter->fillRect(0, 0, m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal(),
                          m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal(),
                          transBlue);
    }

    // paint corner rectangles only if this item is selected
    if (this->isSelected()) {

        painter->setBrush(Qt::green);
        painter->drawRect(getTopLeftCorner());
        painter->drawRect(getBottomLeftCorner());
        painter->drawRect(getTopRightCorner());
        painter->drawRect(getBottomRightCorner());
    }
}

// FIXME Let's discuss this method, too much to type to explain

QRectF RectangleView::boundingRect() const
{
    return QRectF(0 - 10, 0 - 10,
                  m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal() + 15,
                  m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal() + 15);
}


// FIXME refactor this or explain me what is going on  here
void RectangleView::checkResizeRules(QGraphicsSceneMouseEvent *event)
{
    if (m_corner == TOPLEFT) {
        if (m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal() <= event->pos().x()) {
            m_corner = TOPRIGHT;
            setCursor(Qt::SizeBDiagCursor);

        } else if (m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal()
                   <= event->pos().y()) {
            m_corner = BOTTOMLEFT;
            setCursor(Qt::SizeBDiagCursor);
        }
    } else if (m_corner == TOPRIGHT) {
        if (event->pos().x() <= 0) {
            m_corner = TOPLEFT;
            setCursor(Qt::SizeFDiagCursor);

        } else if (m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal()
                   <= event->pos().y()) {
            m_corner = BOTTOMRIGHT;
            setCursor(Qt::SizeFDiagCursor);
        }
    } else if (m_corner == BOTTOMLEFT) {
        if (m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal() <= event->pos().x()) {
            m_corner = BOTTOMRIGHT;
            setCursor(Qt::SizeFDiagCursor);

        } else if (event->pos().y() <= 0) {
            m_corner = TOPLEFT;
            setCursor(Qt::SizeFDiagCursor);
        }
    } else if (m_corner == BOTTOMRIGHT) {
        if (event->pos().x() <= 0) {
            m_corner = BOTTOMLEFT;
            setCursor(Qt::SizeBDiagCursor);

        } else if (event->pos().y() <= 0) {
            m_corner = TOPRIGHT;
            setCursor(Qt::SizeBDiagCursor);
        }
    }
}

// FIXME refactor this or explain me what is going on  here
void RectangleView::calculateResize(QGraphicsSceneMouseEvent *event)
{
    this->setFlag(QGraphicsItem::ItemIsMovable, false);
    checkResizeRules(event);

    if (m_corner == TOPLEFT) {
        m_item->setRegisteredProperty(RectangleItem::P_WIDTH,
                                      m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal()
                                          - event->pos().x());
        m_item->setRegisteredProperty(
            RectangleItem::P_HEIGHT,
            m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal() - event->pos().y());
        this->setX(event->scenePos().x());
        this->setY(event->scenePos().y());

    } else if (m_corner == BOTTOMLEFT) {
        m_item->setRegisteredProperty(
            RectangleItem::P_WIDTH,
            x() + m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal()
                - event->scenePos().x());
        m_item->setRegisteredProperty(RectangleItem::P_HEIGHT, event->scenePos().y() - y());
        this->setX(event->scenePos().x());

    } else if (m_corner == TOPRIGHT) {
        m_item->setRegisteredProperty(RectangleItem::P_WIDTH, event->scenePos().x() - x());
        m_item->setRegisteredProperty(
            RectangleItem::P_HEIGHT,
            y() + m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal()
                - event->scenePos().y());
        this->setY(event->scenePos().y());
    }

    else if (m_corner == BOTTOMRIGHT) {
        m_item->setRegisteredProperty(RectangleItem::P_WIDTH, event->pos().x());
        m_item->setRegisteredProperty(RectangleItem::P_HEIGHT, event->pos().y());
    }
}


// FIXME Rename function, it returns some value, getRotationAngle() ?
qreal RectangleView::calculateRotation(QGraphicsSceneMouseEvent *event)
{
    QPointF middlePoint
        = mapToScene(m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal() / 2,
                     m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal() / 2);
    qreal lengthOfHypotenuse
        = sqrt(pow(m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal() / 2, 2)
               + pow(m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal() / 2, 2));
    qreal offsetAngle = acos((m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal() / 2)
                             / lengthOfHypotenuse) * 180 / M_PI;
    qreal radians = atan((event->scenePos().y() - middlePoint.y())
                         / (event->scenePos().x() - middlePoint.x()));

    if (m_corner == TOPLEFT) {
        return radians * 180 / M_PI - offsetAngle;

    } else if (m_corner == TOPRIGHT) {
        return radians * 180 / M_PI + offsetAngle - 180;

    } else if (m_corner == BOTTOMLEFT) {
        return radians * 180 / M_PI + offsetAngle - 180;

    } else if (m_corner == BOTTOMRIGHT) {
        return radians * 180 / M_PI - offsetAngle;
    }
    return 0;
}


// FIXME Refactor this
// You should split if's --> Create nested if.
//      In one 'if' you check event->button() == Qt::LeftButton,
//      In another (nested) 'if' you check corner position

// FIXME The logic of action is also bad. It is a mouse press event, and you calculate right here which corner it is.
// You have to pass event->pos() to another function which calculates the corners.


void RectangleView::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->setFlag(QGraphicsItem::ItemIsMovable, false);

    // if one of the corners is clicked then go in to resize Mode
    if (event->button() == Qt::LeftButton && getTopLeftCorner().contains(event->pos())) {
        m_resizeMode = true;
        m_corner = TOPLEFT;
        setCursor(Qt::SizeFDiagCursor);

    } else if (event->button() == Qt::LeftButton && getBottomLeftCorner().contains(event->pos())) {
        m_resizeMode = true;
        m_corner = BOTTOMLEFT;
        setCursor(Qt::SizeBDiagCursor);

    } else if (event->button() == Qt::LeftButton && getTopRightCorner().contains(event->pos())) {
        m_resizeMode = true;
        m_corner = TOPRIGHT;
        setCursor(Qt::SizeBDiagCursor);
    }

    else if (event->button() == Qt::LeftButton && getBottomRightCorner().contains(event->pos())) {
        m_resizeMode = true;;
        m_corner = BOTTOMRIGHT;
        setCursor(Qt::SizeFDiagCursor);

        // process as usual
    } else {
        this->setFlag(QGraphicsItem::ItemIsMovable, true);
        QGraphicsItem::mousePressEvent(event);
    }
}

void RectangleView::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "RectangleView::mouseMoveEvent()";

    // check which mode is active and process with the active mode
    if (m_resizeMode) {
        calculateResize(event);

    } else if (m_corner != NONE && m_rotationMode) {
        QTransform transform;
        transform.translate(m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal() * 0.5,
                            m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal() * 0.5);
        transform.rotate(calculateRotation(event));
        transform.translate(
            -(m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal() * 0.5),
            -(m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal() * 0.5));
        setTransform(transform);

        // process as usual
    } else {
        this->setFlag(QGraphicsItem::ItemIsMovable, true);
        QGraphicsItem::mouseMoveEvent(event);
    }
}

void RectangleView::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    // set all modes off, change cursor and process as usual
    this->setFlag(QGraphicsItem::ItemIsMovable, true);
    m_resizeMode =  false;
    m_rotationMode = false;
    setCursor(Qt::ArrowCursor);
    QGraphicsItem::mouseReleaseEvent(event);
}

void RectangleView::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    // activate rotation mode
    if (event->button() == Qt::LeftButton && getTopLeftCorner().contains(event->pos())) {
        m_resizeMode =  false;
        m_rotationMode = true;
        m_corner = TOPLEFT;
        this->setFlag(QGraphicsItem::ItemIsMovable, false);
        setCursor(Qt::ClosedHandCursor);

    } else if (event->button() == Qt::LeftButton && getBottomLeftCorner().contains(event->pos())) {
        m_resizeMode =  false;;
        m_rotationMode = true;
        ;
        m_corner = BOTTOMLEFT;
        this->setFlag(QGraphicsItem::ItemIsMovable, false);
        setCursor(Qt::ClosedHandCursor);

    } else if (event->button() == Qt::LeftButton && getTopRightCorner().contains(event->pos())) {
        m_resizeMode =  false;
        m_rotationMode = true;
        m_corner = TOPRIGHT;
        this->setFlag(QGraphicsItem::ItemIsMovable, false);
        setCursor(Qt::ClosedHandCursor);
    }

    else if (event->button() == Qt::LeftButton && getBottomRightCorner().contains(event->pos())) {
        m_resizeMode =  false;
        m_rotationMode = true;
        m_corner = BOTTOMRIGHT;
        this->setFlag(QGraphicsItem::ItemIsMovable, false);
        setCursor(Qt::ClosedHandCursor);

    } else {
        m_rotationMode = false;
        this->setFlag(QGraphicsItem::ItemIsMovable, true);
        QGraphicsItem::mouseDoubleClickEvent(event);
    }
}

void RectangleView::setInclude()
{
    m_item->setRegisteredProperty(RectangleItem::P_COLOR, 0);
}

void RectangleView::setExclude()
{
    m_item->setRegisteredProperty(RectangleItem::P_COLOR, 1);
}

// FIXME Remove 5,10 hardoced values, what if I want smaller rectangles?
//       I have to be able to replace numbers in one place

QRectF RectangleView::getTopLeftCorner()
{
    return QRectF(0 - 5, 0 - 5, 10, 10);
}

QRectF RectangleView::getTopRightCorner()
{
    return QRectF(0 + m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal() - 5, 0 - 5, 10,
                  10);
}

QRectF RectangleView::getBottomLeftCorner()
{
    return QRectF(0 - 5, 0 + m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal() - 5,
                  10, 10);
}

QRectF RectangleView::getBottomRightCorner()
{
    return QRectF(0 + m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal() - 5,
                  0 + m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal() - 5, 10, 10);
}

void RectangleView::setParameterizedItem(ParameterizedItem *item)
{
    m_item = item;
    setX(m_item->getRegisteredProperty(RectangleItem::P_POSX).toReal() - 5);
    setY(m_item->getRegisteredProperty(RectangleItem::P_POSY).toReal() - 5);
    connect(m_item, SIGNAL(propertyChanged(const QString &)), this,
            SLOT(onPropertyChange(const QString &)));
}

void RectangleView::onChangedX()
{
    m_block_update = true;
    qDebug() << "onXValueChanged(double xValue)-> x value changed" << x()
             << m_item->getRegisteredProperty(RectangleItem::P_POSX).toReal();
    m_item->setRegisteredProperty(RectangleItem::P_POSX, x());
    m_block_update = false;
}

void RectangleView::onChangedY()
{
    m_block_update = true;
    qDebug() << "onYValueChanged(double yValue)-> y value changed" << y()
             << m_item->getRegisteredProperty(RectangleItem::P_POSY).toReal();
    m_item->setRegisteredProperty(RectangleItem::P_POSY, y());
    m_block_update = false;
}

void RectangleView::onPropertyChange(const QString &propertyName)
{
    if (m_block_update)
        return;
    qDebug() << "void EllipseView::onPropertyChange(const QString &propertyName)"
             << m_item->getRegisteredProperty(RectangleItem::P_POSX).toReal()
             << m_item->getRegisteredProperty(RectangleItem::P_POSY).toReal()
             << m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal()
             << m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal();

    if (propertyName == RectangleItem::P_POSX) {
        setX(m_item->getRegisteredProperty(RectangleItem::P_POSX).toReal() + 5);
    } else if (propertyName == RectangleItem::P_POSY) {
        setY(m_item->getRegisteredProperty(RectangleItem::P_POSY).toReal() + 5);
    }
}

ParameterizedItem *RectangleView::getParameterizedItem()
{
    return m_item;
}
