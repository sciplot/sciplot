
<p align="center">
    <img src="art/sciplot-logo.svg" width=100%;" title="sciplot">
</p>

# Overview

**So, you have an amazing C++ application for which you need plotting capabilities.** You have searched around and discovered that the available options for C++ plotting libraries is rather limited compared to other programming languages, such as Python, for example, which has **[matplotlib]**. 

The goal of the **sciplot project** is to enable you, C++ programmer, to **conveniently plot beautiful graphs** as easy as in other high-level programming languages. 

Here is an example of **sciplot** in action:

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

> Do you want to change the colors? Simple - just use the `plot::pallete` method to set your preferred color pallete. For example, `plot::pallete("parula")` sets the [**parula**](https://www.mathworks.com/help/matlab/ref/parula.html) color scheme. All available color palletes and their names can be found [**here**][gnuplot-palletes]. Many thanks to [**Anna Schneider**][AnnaSchneider] for this incredible work of art!

# sciplot and gnuplot

All plotting capabilities of **sciplot** are powered by **[gnuplot]**.  Your plotting code, using a modern and elegant C++ API provided by **sciplot**, is converted to a gnuplot script, which is then executed to generate the desired figure.

# Come back soon for further instructions and demonstration.

[gnuplot]: http://gnuplot.info/
[gnuplot-palletes]: https://github.com/sciplot/gnuplot-palettes
[matplotlib]: https://matplotlib.org/
[AnnaSchneider]: https://github.com/aschn


