#ifndef TURBOTRACK_HPP
#define TURBOTRACK_HPP

#if defined TURBOTRACK_USE_EIGEN
	#include <Eigen/Dense>

	using turbotrack_vec2 = Eigen::Vector2f;
	using turbotrack_vec3 = Eigen::Vector3f;
	using turbotrack_quat = Eigen::Quaternionf;
#elif defined TURBOTRACK_USE_GLM
	#include <glm/glm.hpp>
	#include <glm/gtc/quaternion.hpp>

	using turbotrack_vec2 = glm::vec2;
	using turbotrack_vec3 = glm::vec3;
	using turbotrack_quat = glm::quat;
#endif

namespace turbotrack {

enum class TrackballType {
	// chen_et_al, not implemented yet
	shoemake,
	holroyd
};

// See equation 33 in Henriksen et al.
turbotrack_vec3 shoemake_projection(turbotrack_vec2 const &mouse, float radius);

// See equation 46 in Henriksen et al.
turbotrack_vec3 holroyd_projection(turbotrack_vec2 const &mouse, float radius);

turbotrack_quat quat_from_vectors(const turbotrack_vec3 &vec_a,
                                  const turbotrack_vec3 &vec_b);

turbotrack_quat mouse_move(turbotrack_vec2 const &old_pos,
                           turbotrack_vec2 const &new_pos, float radius = 1.0,
                           TrackballType type = TrackballType::holroyd);

} // namespace turbotrack

#endif // TURBOTRACK_HPP
