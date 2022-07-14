# FAQ

## How are my plots generated?

All plotting capabilities of {{sciplot}} are powered by [gnuplot].  Your
plotting code, using a modern and elegant C++ API provided by {{sciplot}}, is
converted to a gnuplot script, which is then executed to generate the desired
figure. Note that gnuplot 4.2+ is needed for multiplots, but a version higher than 5.4.1 is recommended.

## Something is not working for me. Is it a known issue?

Some known issues are documented [here](known_issues.md). Also make sure you check already [closed issues](https://github.com/sciplot/sciplot/issues?q=is%3Aissue+is%3Aclosed) too.

## How do I report issues?

If you found an issue with {{sciplot}}, please create a new
[GitHub Issue](https://github.com/sciplot/sciplot/issues/new).

## How can I contribute?

You can contribute with {{sciplot}} in many ways. It would be great to have
more examples demonstrating its use. We also need to extend the plotting
capabilities and customizations of {{sciplot}}. Not every capability of Gnuplot
has been made available in {{sciplot}} yet.

## How can I cite?

You can cite {{sciplot}} using the following bibtex entry:
~~~
@ONLINE {sciplot2018,
    author = "Allan M. M. Leal",
    title  = "sciplot, a modern C++ plotting library powered by gnuplot",
    month  = "August",
    year   = "2018",
    url    = "sciplot.github.io"
}
~~~

[gnuplot]: http://gnuplot.info/
