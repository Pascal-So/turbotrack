#include <cmath>
#include <turbotrack.hpp>

namespace turbotrack {

Eigen::Vector3f shoemake_projection(const Eigen::Vector2f &mouse,
                                    float radius) {
	const float d2 = mouse.squaredNorm();
	const float r2 = radius * radius;

	if (d2 <= r2) {
		// sphere
		return {mouse(0), mouse(1), std::sqrt(r2 - d2)};
	} else {
		// scaled sphere
		const float factor = radius / std::sqrt(d2);
		return {factor * mouse(0), factor * mouse(1), 0};
	}
}

Eigen::Vector3f holroyd_projection(const Eigen::Vector2f &mouse, float radius) {
	const float d2 = mouse.squaredNorm();
	const float r2 = radius * radius;

	if (d2 <= r2 / 2) {
		// sphere
		return {mouse(0), mouse(1), std::sqrt(r2 - d2)};
	} else {
		// hyperbola
		return {mouse(0), mouse(1), r2 / 2 / std::sqrt(d2)};
	}
}

Eigen::Quaternionf mouse_move(const Eigen::Vector2f &old_pos,
                              const Eigen::Vector2f &new_pos, float radius,
                              TrackballType type) {
	if (type == TrackballType::shoemake) {
		return Eigen::Quaternionf::FromTwoVectors(
		    shoemake_projection(old_pos, radius),
		    shoemake_projection(new_pos, radius));
	} else {
		return Eigen::Quaternionf::FromTwoVectors(
		    holroyd_projection(old_pos, radius),
		    holroyd_projection(new_pos, radius));
	}
}

} // namespace turbotrack
