# TurboTrack

A library for navigating around 3d space using a trackball-style input. Provides the Holroyd and Shoemake trackball algorithms [1]. The library currently supports both Eigen and glm as data representation.

## Usage

Link to the CMake target `turbotrack`, afterwards you can use the library like this:

```c++
#include <turbotrack.hpp>

Eigen::Quaternionf current_orientation;

// on mouse movement
Eigen::Vector2f old_mouse_pos /* = ... */, new_mouse_pos /* = ... */;
const Eigen::Quaternionf rot = turbotrack::mouse_move(old_mouse_pos, new_mouse_pos, radius);
current_orientation = rot * current_orientation;
```

Make sure that you first transform the mouse coordinates to have 0 at the centre of the screen. If the rotation is wrong then you might have to flip the y coordinate on the inputs to `mouse_move`.

Experiment with the radius to get something that feels right for your application. Just over half the window width seems to be a good starting point.

## Eigen / glm

Use the CMake cache variable `TURBOTRACK_LINALG_LIBRARY` to select either `EIGEN` or `GLM` as the linear algebra backend.

```c++
// set(TURBOTRACK_LINALG_LIBRARY "EIGEN" CACHE)
Eigen::Quaternionf turbotrack::mouse_move(
	const Eigen::Vector2f &old_pos,
	const Eigen::Vector2f &new_pos,
	float radius = 1.0,
	turbotrack::TrackballType type = turbotrack::TrackballType::holroyd
);

// set(TURBOTRACK_LINALG_LIBRARY "GLM" CACHE)
glm::quat turbotrack::mouse_move(
	const glm::vec2 &old_pos,
	const glm::vec2 &new_pos,
	float radius = 1.0,
	turbotrack::TrackballType type = turbotrack::TrackballType::holroyd
);
```

## Scope

For now this library only deals with the view rotation, not translation. This might be expanded in the future, depending on my needs / time.

## References

[1] K. Henriksen, J. Sporring, and K. Hornbæk. Virtual Trackballs Revisited. DSAGM, 2002.
