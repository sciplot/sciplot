
<p align="center">
    <img src="art/sciplot-logo.svg" width=100%;" title="sciplot">
</p>

# Overview

**So, you have an amazing C++ application for which you need some plotting capability.** You have searched around, and discovered that C++ is not very famous when it comes to plotting libraries compared to other programming languages, such as Python, for example, which has the nice package **[matplotlib]**. 

The goal of the **sciplot project** is to enable you, C++ programmer, to conveniently plot beautiful graphs as easy as in other high-level programming languages. 

All plotting capabilities of **sciplot** are powered by the amazing **[gnuplot]** application.  Your plotting code using a modern and elegant C++ API provided by **sciplot** is converted to a gnuplot script, which is then executed to generate the desired figure.

Here is an example:

~~~c++
#include <sciplot/sciplot.hpp>
using namespace sciplot;

int main()
{
    const vec x = linspace(0.0, 5.0, 100);

    plot plt;

    plt.pallete("set2");

    plt.draw(x, std::sin(x)).title("sin(x)").linewidth(8);
    plt.draw(x, std::cos(x)).title("cos(x)").linewidth(8);

    plt.show();
    plt.save("figure.pdf");
}
~~~

<p align="center">
    <img src="art/example-sincos.svg" width=90%;" title="sincos">
</p>

# Come back soon for further instructions and demonstration.

[gnuplot]: http://gnuplot.info/
[matplotlib]: https://matplotlib.org/


