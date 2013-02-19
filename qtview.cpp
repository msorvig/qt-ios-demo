#include "qtview.h"

#include <QtWidgets>

QtView::QtView()
{
    scene = new QGraphicsScene;

    scene->setBackgroundBrush(QColor("#486E96"));
    setScene(scene);

    setFrameStyle(QFrame::NoFrame);

    QPixmap qtLogo(":/qt-logo.png");
    QGraphicsItem *newItem = scene->addPixmap(qtLogo);
    newItem->setPos(QPointF(width() / 2, height() / 2));
    newItem->setScale(0.5);

    this->setAttribute(Qt::WA_AcceptTouchEvents);
}

bool QtView::viewportEvent(QEvent *event)
{
    // forward touch events
    switch (event->type()) {
    case QEvent::TouchBegin:
    case QEvent::TouchUpdate:
    case QEvent::TouchEnd:
        touchEvent(static_cast<QTouchEvent *>(event));
        break;
    default:
        return QGraphicsView::viewportEvent(event);
    }
    return true;
}

void QtView::resizeEvent(QResizeEvent *event)
{
    // Keep scene rect set to view size
    scene->setSceneRect(QRectF(QPointF(0,0), this->size()));
}

void QtView::mousePressEvent(QMouseEvent *event)
{
    maybeAddQtLogo(event->pos());
}

void QtView::touchEvent(QTouchEvent *event)
{
    QList<QTouchEvent::TouchPoint> touchPoints = static_cast<QTouchEvent *>(event)->touchPoints();
    foreach (const QTouchEvent::TouchPoint &touchPoint, touchPoints) {
        switch (touchPoint.state()) {
            case Qt::TouchPointStationary:
                continue;  // don't do anything if this touch point hasn't moved
            default:
                maybeAddQtLogo(touchPoint.rect().center().toPoint());
            break;
        }
    }
}

void QtView::maybeAddQtLogo(QPoint position)
{
     // Add Qt logo if there is no item at the current position
    if (QGraphicsItem *item = itemAt(position)) {
        // noop
    } else {
        QPixmap qtLogo(":/qt-logo.png");
        QGraphicsItem *newItem = scene->addPixmap(qtLogo);
        newItem->setPos(position - QPoint(qtLogo.width(), qtLogo.height()) / 4); // center item on position
        newItem->setScale(0.5);
    }
}
