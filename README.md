This sample aims to reproduce inconsistencies between the state of the relative
mouse mode and the cursor visibility on macOS with SDL 2.0.20.

It opens a SDL window (with garbage content) and toggle relative mouse mode on
pressing <kbd>Alt</kbd>.

When relative mouse mode is enabled, mouse events are logged to the console.

To build and execute:

```bash
meson x
ninja -Cx
x/sample-relativemouse
```
