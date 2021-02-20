#include <sciplot/sciplot.hpp>
using namespace sciplot;

int main(int argc, char** argv)
{
    Vec x = linspace(0.0, PI, 200);

    Plot plot;

    plot.xlabel("x");
    plot.ylabel("y");

    plot.xrange(0.0, PI);
    plot.yrange(0.0, 6.0);

    plot.drawCurve(x, std::sin(x)).label("sin(x)");

    plot.save("my-sine-plot.pdf");
}
