#include <sciplot/sciplot.hpp>
using namespace sciplot;

int main(int argc, char** argv)
{
    const vec x = linspace(0.0, PI, 200);

    plot plt;

    plt.xlabel("x");
    plt.ylabel("y");

    plt.xrange(0.0, PI);
    plt.yrange(0.0, 6.0);

    plt.draw(x, std::sin(x)).title("sin(x)");

    plt.save("my-sine-plot.pdf");
}
