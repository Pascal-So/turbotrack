#ifndef TURBOTRACK_HPP
#define TURBOTRACK_HPP

#if defined TURBOTRACK_USE_EIGEN
	#include <Eigen/Dense>

	namespace turbotrack {
		using vec2 = Eigen::Vector2f;
		using vec3 = Eigen::Vector3f;
		using quat = Eigen::Quaternionf;
	}
#elif defined TURBOTRACK_USE_GLM
	#include <glm/glm.hpp>
	#include <glm/gtc/quaternion.hpp>

	namespace turbotrack {
		using vec2 = glm::vec2;
		using vec3 = glm::vec3;
		using quat = glm::quat;
	}
#endif

namespace turbotrack {

enum class TrackballType {
	// chen_et_al, not implemented yet
	shoemake,
	holroyd
};

// See equation 33 in Henriksen et al.
vec3 shoemake_projection(const vec2 &mouse, float radius);

// See equation 46 in Henriksen et al.
vec3 holroyd_projection(const vec2 &mouse, float radius);

quat mouse_move(const vec2 &old_pos,
                const vec2 &new_pos, float radius = 1.0,
                TrackballType type = TrackballType::holroyd);

} // namespace turbotrack

#endif // TURBOTRACK_HPP
