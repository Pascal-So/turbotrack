#include <turbotrack.hpp>

namespace turbotrack {

turbotrack_quat mouse_move(turbotrack_vec2 const &old_pos,
                           turbotrack_vec2 const &new_pos, float radius,
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
