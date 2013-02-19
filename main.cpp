#include "qtview.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QtView qtView;
    qtView.show();

    return app.exec();
}
