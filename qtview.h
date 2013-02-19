#include <QtWidgets>

class QtView : public QGraphicsView
{
public:
    QtView();

    bool viewportEvent(QEvent *event);
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void touchEvent(QTouchEvent *event);

    void maybeAddQtLogo(QPoint position);
private:
    QGraphicsScene *scene;
};
