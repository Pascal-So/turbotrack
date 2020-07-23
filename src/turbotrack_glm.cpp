#include <cmath>
#include <turbotrack.hpp>

namespace turbotrack {

float squared_norm(const turbotrack_vec2 &v) {
	return glm::dot(v, v);
}

float get_x(const turbotrack_vec2 &v) {
	return v.x;
}

float get_y(const turbotrack_vec2 &v) {
	return v.y;
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
