# TurboTrack

A library for navigating around 3d space using a trackball-style input. Provides the Holroyd and Shoemake trackball algorithms [1].

## Usage

Link to the CMake target `turbotrack`, afterwards you can use the library like this:

```c++
#include <turbotrack.hpp>

Eigen::Quaternionf current_orientation;

// on mouse movement
Eigen::Vector2f old_mouse_pos /* = ... */, new_mouse_pos /* = ... */;
const Eigen::Quaternionf rot = turbotrack::mouse_move(old_mouse_pos, new_mouse_pos, window_width / 2);
current_orientation = rot * current_orientation;
```

Experiment with the radius to get something that feels right for your application. Just over half the window width seems to be a good starting point.

If the rotation is wrong then you might have to flip the y coordinate on the inputs to `mouse_move`.

## Scope

For now this library only deals with the view rotation, not translation. This might be expanded in the future, depending on my needs / time.

If you prefer to handle all the data in glm format rather than in Eigen then feel free to send a PR that allows the user to select the linalg library at compile time so that the user doesn't need to have both libraries installed.

## References

[1] K. Henriksen, J. Sporring, and K. Hornbæk. Vitrual Trackballs Revisited. DSAGM, 2002.
