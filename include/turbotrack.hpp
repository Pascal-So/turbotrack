#ifndef TURBOTRACK_HPP
#define TURBOTRACK_HPP

#include <Eigen/Dense>

namespace turbotrack {

enum class TrackballType {
	// chen_et_al, not implemented yet
	shoemake,
	holroyd
};

// See equation 33 in Henriksen et al.
Eigen::Vector3f shoemake_projection(Eigen::Vector2f const &mouse, float radius);

// See equation 46 in Henriksen et al.
Eigen::Vector3f holroyd_projection(Eigen::Vector2f const &mouse, float radius);

Eigen::Quaternionf mouse_move(Eigen::Vector2f const &old_pos,
                              Eigen::Vector2f const &new_pos,
                              float radius = 1.0,
                              TrackballType type = TrackballType::holroyd);

} // namespace turbotrack

#endif // TURBOTRACK_HPP
