#include <sciplot/sciplot.hpp>
using namespace sciplot;

int main(int argc, char** argv)
{
    const Vec x = linspace(0.0, PI, 200);

    Figure fig;

    fig.xlabel("x");
    fig.ylabel("y");

    fig.xrange(0.0, PI);
    fig.yrange(0.0, 6.0);

    fig.drawCurve(x, std::sin(x)).label("sin(x)");

    fig.save("my-sine-plot.pdf");
}
