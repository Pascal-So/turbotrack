#include <cmath>
#include <turbotrack.hpp>

namespace turbotrack {

turbotrack_vec3 shoemake_projection(turbotrack_vec2 const &mouse,
                                    float radius) {
	const float r2 = radius * radius;
	const float d2 = mouse.squaredNorm();

	if (d2 <= r2) {
		// sphere
		return {mouse(0), mouse(1), std::sqrt(r2 - d2)};
	} else {
		// scaled sphere
		const float factor = radius / std::sqrt(d2);
		return {factor * mouse(0), factor * mouse(1), 0};
	}
}

turbotrack_vec3 holroyd_projection(turbotrack_vec2 const &mouse, float radius) {
	const float r2 = radius * radius;
	const float d2 = mouse.squaredNorm();

	if (d2 <= r2 / 2) {
		// sphere
		return {mouse(0), mouse(1), std::sqrt(r2 - d2)};
	} else {
		// hyperbola
		return {mouse(0), mouse(1), r2 / 2 / std::sqrt(d2)};
	}
}

turbotrack_quat quat_from_vectors(const turbotrack_vec3 &vec_a,
                                  const turbotrack_vec3 &vec_b) {
	return Eigen::Quaternionf::FromTwoVectors(vec_a, vec_b);
}

} // namespace turbotrack
