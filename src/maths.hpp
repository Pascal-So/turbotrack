#ifndef TURBOTRACK_MATHS_HPP
#define TURBOTRACK_MATHS_HPP

namespace turbotrack {

quat quat_from_vectors(const vec3 &vec_a,
                       const vec3 &vec_b);

float squared_norm(const vec2 &v);

float get_x(const vec2 &v);
float get_y(const vec2 &v);

} // namespace turbotrack

#endif // TURBOTRACK_MATHS_HPP
