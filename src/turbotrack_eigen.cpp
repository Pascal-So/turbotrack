#include <cmath>
#include <turbotrack.hpp>

namespace turbotrack {

float squared_norm(const turbotrack_vec2 &v) {
	return v.squaredNorm();
}

float get_x(const turbotrack_vec2 &v) {
	return v(0);
}

float get_y(const turbotrack_vec2 &v) {
	return v(1);
}

turbotrack_quat quat_from_vectors(const turbotrack_vec3 &vec_a,
                                  const turbotrack_vec3 &vec_b) {
	return Eigen::Quaternionf::FromTwoVectors(vec_a, vec_b);
}

} // namespace turbotrack
