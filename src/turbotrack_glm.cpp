#include <cmath>
#include <turbotrack.hpp>

namespace turbotrack {

float squared_norm(const vec2 &v) {
	return glm::dot(v, v);
}

float get_x(const vec2 &v) {
	return v.x;
}

float get_y(const vec2 &v) {
	return v.y;
}

quat quat_from_vectors(const vec3 &vec_a,
                       const vec3 &vec_b) {
	const glm::vec3 n_a = glm::normalize(vec_a);
	const glm::vec3 n_b = glm::normalize(vec_b);
	return glm::rotation(n_a, n_b);
}

} // namespace turbotrack
