#ifndef TURBOTRACK_MATHS_HPP
#define TURBOTRACK_MATHS_HPP

namespace turbotrack {

turbotrack_quat quat_from_vectors(const turbotrack_vec3 &vec_a,
                                  const turbotrack_vec3 &vec_b);

float squared_norm(const turbotrack_vec2 &v);

float get_x(const turbotrack_vec2 &v);
float get_y(const turbotrack_vec2 &v);

} // namespace turbotrack

#endif // TURBOTRACK_MATHS_HPP
