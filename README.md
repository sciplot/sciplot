
<p align="center">
    <img src="art/sciplot-logo.svg" width=100%;" title="sciplot">
</p>

<p align="center">
    <img src="docs/website/img/warning.svg" width=100%;" title="warning">
</p>

# Overview

**So, you have an amazing C++ application for which you need plotting capabilities.** You have searched around and discovered that the available options for C++ plotting libraries is rather limited compared to other programming languages, such as Python, for example, which has [matplotlib].

The goal of the **sciplot project** is to enable you, C++ programmer, to **conveniently plot beautiful graphs** as easy as in other high-level programming languages. **sciplot** is a header-only library that needs a C++17-capable compiler, but has no external dependencies for compiling. The only external runtime dependencies are [gnuplot-palettes] for providing color palettes and a [gnuplot] executable.

Here is an example of **sciplot** in action:

```c++
#include <sciplot/sciplot.hpp>
using namespace sciplot;

int main(int argc, char** argv)
{
    // Create values for your x-axis
    Vec x = linspace(0.0, 5.0, 100);

    // Create a Plot object
    Plot2D plot;

    // Set color palette
    plot.palette("set2");

    // Draw a sine graph putting x on the x-axis and sin(x) on the y-axis
    plot.drawCurve(x, std::sin(x)).label("sin(x)").lineWidth(4);

    // Draw a cosine graph putting x on the x-axis and cos(x) on the y-axis
    plot.drawCurve(x, std::cos(x)).label("cos(x)").lineWidth(4);

    // Show the plot in a pop-up window
    plot.show();

    // Save the plot to a PDF file
    plot.save("plot.pdf");
}
```

After compiling and executing this C++ application, the following plot (`plot.pdf`) is produced:


<p align="center">
    <img src="docs/website/img/home/demo-plot-palette-set2.svg" width=60%;" title="sincos">
</p>

Do you want to change the colors?

Simple - just use method `Plot::palette` to set your preferred color palette. For example, using `plot.palette("parula")` in the previous code sets the [parula](https://www.mathworks.com/help/matlab/ref/parula.html) color scheme and produces the following plot:

<p align="center">
    <img src="docs/website/img/home/demo-plot-palette-parula.svg" width=60%;" title="sincos">
</p>

All available color palettes and their names can be found [here][gnuplot-palettes]. Many thanks to [Anna Schneider][AnnaSchneider] for this incredible work of art!

[gnuplot-palettes]: https://github.com/sciplot/gnuplot-palettes
[AnnaSchneider]: https://github.com/aschn
