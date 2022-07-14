#include "view.h"

View::View() {
    setFixedSize(window_w, window_h);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    show();
}
