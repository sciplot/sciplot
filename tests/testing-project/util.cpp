#include <sciplot/sciplot.hpp>
using namespace sciplot;

void plot()
{
    const Vec x = linspace(0.0, 5.0, 8);
    const Vec y = linspace(2.0, 6.0, 8);

    Figure fig;

    fig.palette("dark2");

    fig.samples(200);

    fig.drawCurve(x, y).label("A");

    fig.show();
}
