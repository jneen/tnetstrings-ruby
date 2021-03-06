This is a general-purpose [tnetstrings][] library for Ruby.

# Installation

```
% gem install tnetstrings
```

# Usage

The `TNETS` module has the same familiar interface as `JSON` - just `TNETS.load(tnetstring)` and `TNETS.dump(obj)` (or `obj.to_tnets`).  To dump arbitrary objects, define `#as_tnets`.  As a convenience, `#as_json` is used otherwise, if it is defined.

If you have an `Enumerable` you'd like to stream, call `my_enum.stream_tnets(io)`, and your `io` will receive one write for every object your enumerable yields.

# Why would I want such a thing?

Tnetstrings (or "tagged netstrings") are a data serialization format that support the same data serialization structures as JSON\*.  You can read more about it on the tnetstrings site at <http://tnetstrings.org>, but the main advantage is that all the juicy bits are length-specified instead of delimiter-specified, making it much safer and faster to parse from a socket.

\* one not-insignificant difference is that tnetstrings currently have no support for floating-point or decimal numbers.  But it may be coming soon.

# How do I build it / run tests?

You will need a couple of things:

* A working C compiler
* Ruby, along with rake and bundler.
* For testing, you will need a few gems, which will install automatically with a call to `bundle`

To build the project, run `rake build`.  To build and run tests, simply run `rake`.

# OMG how could you possibly make such a n00bish mistake?  Do you even know C?
Fair warning.  This is my first project using C - I'm normally a scripting-language guy.  If you are a more experienced developer (i.e. have written a project in C before), I would appreciate it a lot if you could let me know of any ways to improve my code.  I'm always looking to improve my craft, and definitely appreciate any and all input.

# What is the current state of development?
This library is currently super-alpha - as in not even fully implemented yet.  Here are some of the things on my list:

* parsing from a stream rather than an in-memory string (this is what tnetstrings are for, after all)
* handle and test more error cases, and fix a few that I know aren't handled
* separating the parser from the Ruby implementation, in case anyone else wants to use it for another purpose (like embedding into another language, for example).

# How do I contribute?
Fork it and send me a pull request.  If you're super-enthusiastic, I might add you as a contributor.  I would especially appreciate help with any of the above items.

Enjoy!
--Jay

[tnetstrings]: http://tnetstrings.org "tnetstrings"
