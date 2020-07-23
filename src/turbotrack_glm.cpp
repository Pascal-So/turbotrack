#include <cmath>
#include <turbotrack.hpp>

namespace turbotrack {

turbotrack_vec3 shoemake_projection(turbotrack_vec2 const &mouse,
                                    float radius) {
	const float r2 = radius * radius;
	const float d2 = glm::dot(mouse, mouse);

	if (d2 <= r2) {
		// sphere
		return {mouse.x, mouse.y, std::sqrt(r2 - d2)};
	} else {
		// scaled sphere
		const float factor = radius / std::sqrt(d2);
		return {factor * mouse.x, factor * mouse.y, 0};
	}
}

turbotrack_vec3 holroyd_projection(turbotrack_vec2 const &mouse, float radius) {
	const float r2 = radius * radius;
	const float d2 = glm::dot(mouse, mouse);

	if (d2 <= r2 / 2) {
		// sphere
		return {mouse.x, mouse.y, std::sqrt(r2 - d2)};
	} else {
		// hyperbola
		return {mouse.x, mouse.y, r2 / 2 / std::sqrt(d2)};
	}
}

turbotrack_quat quat_from_vectors(const turbotrack_vec3 &vec_a,
                                  const turbotrack_vec3 &vec_b) {
	const glm::vec3 n_a = glm::normalize(vec_a);
	const glm::vec3 n_b = glm::normalize(vec_b);

	const float cos_angle = glm::dot(n_a, n_b);
	const glm::vec3 axis = glm::cross(n_a, n_b);
	const float s = std::sqrt((1 + cos_angle) * 2);
	return {s / 2, axis.x / s, axis.y / s, axis.z / s};
}

} // namespace turbotrack
