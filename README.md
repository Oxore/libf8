## libf8
![WTFPL](http://www.wtfpl.net/wp-content/uploads/2012/12/wtfpl-badge-2.png "WTFPL")

This is small unicode library made by myself for my little demands.

If you think you can use my library as is, then **think twice**, because it has no unicode validity check and almost certainly lacks of some crucial functionality you need.
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

v0.1.0
