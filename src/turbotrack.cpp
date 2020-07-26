#include <turbotrack.hpp>
#include "maths.hpp"

namespace turbotrack {

vec3 shoemake_projection(const vec2 &mouse, float radius) {
	const float r2 = radius * radius;
	const float d2 = squared_norm(mouse);

	if (d2 <= r2) {
		// sphere
		return {get_x(mouse), get_y(mouse), std::sqrt(r2 - d2)};
	} else {
		// scaled sphere
		const float factor = radius / std::sqrt(d2);
		return {factor * get_x(mouse), factor * get_y(mouse), 0};
	}
}

vec3 holroyd_projection(const vec2 &mouse, float radius) {
	const float r2 = radius * radius;
	const float d2 = squared_norm(mouse);

	if (d2 <= r2 / 2) {
		// sphere
		return {get_x(mouse), get_y(mouse), std::sqrt(r2 - d2)};
	} else {
		// hyperbola
		return {get_x(mouse), get_y(mouse), r2 / 2 / std::sqrt(d2)};
	}
}

quat mouse_move(const vec2 &old_pos, const vec2 &new_pos,
                float radius, TrackballType type) {
	vec3 p1, p2;

	switch (type) {
	case TrackballType::shoemake:
		p1 = shoemake_projection(old_pos, radius);
		p2 = shoemake_projection(new_pos, radius);
		break;
	case TrackballType::holroyd:
		p1 = holroyd_projection(old_pos, radius);
		p2 = holroyd_projection(new_pos, radius);
		break;
	}

	return quat_from_vectors(p1, p2);
}

} // namespace turbotrack
