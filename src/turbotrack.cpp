#include <turbotrack.hpp>
#include "maths.hpp"

namespace turbotrack {

turbotrack_vec3 shoemake_projection(const turbotrack_vec2 &mouse,
                                    float radius) {
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

turbotrack_vec3 holroyd_projection(const turbotrack_vec2 &mouse, float radius) {
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

turbotrack_quat mouse_move(const turbotrack_vec2 &old_pos,
                           const turbotrack_vec2 &new_pos, float radius,
                           TrackballType type) {
	turbotrack_vec3 p1, p2;

	if (type == TrackballType::shoemake) {
		p1 = shoemake_projection(old_pos, radius);
		p2 = shoemake_projection(new_pos, radius);
	} else {
		p1 = holroyd_projection(old_pos, radius);
		p2 = holroyd_projection(new_pos, radius);
	}

	return quat_from_vectors(p1, p2);
}

} // namespace turbotrack
