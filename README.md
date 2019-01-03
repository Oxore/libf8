## libf8
[![Build Status](https://travis-ci.org/Oxore/libf8.svg?branch=master)](https://travis-ci.org/Oxore/libf8)
![WTFPL](http://www.wtfpl.net/wp-content/uploads/2012/12/wtfpl-badge-2.png "WTFPL")

This is small library of unicode helper functions made for my little demands.
In is like a `string.h` for unicode in some way.

If you think you could use my library as is, then **look carefully**, because it has no unicode validity check and almost certainly lacks of some crucial functionality you need.
If I need something, I implement this.
If you want, you can do it too - welcome.

## Dependencies

`munit` for testing - added as a git submodule, use `git submodule update --init` to pull it.

## Compilation and usage

Compilation:

```
make
```

It will produce a `libf8.a` archive you can use for static linkage.
Use `-l:libf8.a` flag while linking with it.

Build without tests:

```
make NOTEST=1
```

Clean:

```
make clean
```

---

v0.2.2
