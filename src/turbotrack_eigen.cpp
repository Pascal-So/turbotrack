#include <cmath>
#include <turbotrack.hpp>

namespace turbotrack {

float squared_norm(const vec2 &v) {
	return v.squaredNorm();
}

float get_x(const vec2 &v) {
	return v(0);
}

float get_y(const vec2 &v) {
	return v(1);
}

quat quat_from_vectors(const vec3 &vec_a,
                       const vec3 &vec_b) {
	return Eigen::Quaternionf::FromTwoVectors(vec_a, vec_b);
}

} // namespace turbotrack
