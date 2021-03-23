#ifndef TURBOTRACK_HPP
#define TURBOTRACK_HPP

#include <type_traits>
#include <utility>
#include <cassert>
#include <cmath>

namespace Eigen {
template<typename _Scalar, int _Rows, int _Cols, int _Options, int _MaxRows, int _MaxCols>
class Matrix;
template<typename _Scalar, int _Options>
class Quaternion;
}

namespace turbotrack {

template<typename vector2_t>
struct vec2_traits {
	static_assert(std::is_same_v<vector2_t, std::decay_t<vector2_t>>, "vector2_t has to be in its decayed form");

	static constexpr bool is_specialized = false;

	struct scalar{};
	using vec2 = vector2_t;
	struct vec3{};
	struct quat{};

	static bool is_valid_vec2(const vec2 &v) noexcept;

	static vec2 construct_vec2(scalar x, scalar y) noexcept;
	static vec3 construct_vec3(scalar x, scalar y, scalar z) noexcept;
	static quat construct_quat(const vec3 &a, const vec3 &b) noexcept;

	static scalar const& get_x(const vec2 &v) noexcept;
	static scalar const& get_y(const vec2 &v) noexcept;

	static scalar squared_norm(const vec2 &v) noexcept;
};

template<typename _Scalar, int _Rows, int _Cols, int _Options, int _MaxRows, int _MaxCols>
struct vec2_traits<Eigen::Matrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols>> {
	static constexpr int Dynamic = -1;

	using scalar = _Scalar;
	using vec2 = Eigen::Matrix<scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols>;
	using vec3 = Eigen::Matrix<scalar, _Rows == Dynamic ? Dynamic : _Rows + 1, _Cols, _Options, _MaxRows == Dynamic ? Dynamic : _MaxRows + 1, _MaxCols>;
	using quat = Eigen::Quaternion<scalar, _Options>;

	static bool is_valid_vec2(const vec2 &v) noexcept {
		return v.rows() == 2 && v.rows() == 1;
	}

	static vec2 construct_vec2(scalar x, scalar y) {
		return { std::move(x), std::move(y) };
	}
	static vec3 construct_vec3(scalar x, scalar y, scalar z) {
		return { std::move(x), std::move(y), std::move(z) };
	}
	static quat construct_quat(const vec3 &a, const vec3 &b) {
		return quat::FromTwoVectors(a, b);
	}

	static scalar const& get_x(const vec2 &v) noexcept {
		assert(is_valid_vec2(v));
		return v(0);
	}
	static scalar const& get_y(const vec2 &v) noexcept {
		assert(is_valid_vec2(v));
		return v(1);
	}

	static scalar squared_norm(const vec2 &v) {
		assert(is_valid_vec2(v));
		return v.squaredNorm();
	}
};

// Just some random macro to check if GLM has been included.
// This is ugly for two reasons:
//   - It prescribes the include order.
//   - It doesn't ensure that e.g. the quaternion extension has been included.
#ifdef GLM_FUNC_QUALIFIER

template<typename T, glm::qualifier Q>
struct vec2_traits<glm::vec<2, T, Q>> {
	static constexpr int Dynamic = -1;

	using scalar = T;
	using vec2 = glm::vec<2, T, Q>;
	using vec3 = glm::vec<3, T, Q>;
	using quat = glm::qua<T, Q>;

	static constexpr bool is_valid_vec2(const vec2 &v) noexcept {
		(void)v; // -Wunused-parameter
		return true;
	}

	static constexpr vec2 construct_vec2(scalar x, scalar y) {
		return { std::move(x), std::move(y) };
	}
	static constexpr vec3 construct_vec3(scalar x, scalar y, scalar z) {
		return { std::move(x), std::move(y), std::move(z) };
	}
	static quat construct_quat(const vec3 &a, const vec3 &b) {
		const vec3 n_a = glm::normalize(a);
		const vec3 n_b = glm::normalize(b);
		return glm::rotation(n_a, n_b);
	}

	static constexpr scalar const& get_x(const vec2 &v) noexcept {
		return v.x;
	}
	static constexpr scalar const& get_y(const vec2 &v) noexcept {
		return v.y;
	}

	static scalar squared_norm(const vec2 &v) {
		return glm::dot(v, v);
	}
};

#endif // defined(GLM_FUNC_QUALIFIER)

enum class TrackballType {
	// chen_et_al, not implemented yet
	shoemake,
	holroyd
};

// See equation 33 in Henriksen et al.
template<typename vec2, typename traits = vec2_traits<vec2>>
typename traits::vec3 shoemake_projection(const vec2 &mouse, typename traits::scalar radius) {
	const typename traits::scalar r2 = radius * radius;
	const typename traits::scalar d2 = traits::squared_norm(mouse);

	if (d2 <= r2) {
		// sphere
		return traits::construct_vec3(traits::get_x(mouse), traits::get_y(mouse), std::sqrt(r2 - d2));
	} else {
		// scaled sphere
		const typename traits::scalar factor = radius / std::sqrt(d2);
		return traits::construct_vec3(factor * traits::get_x(mouse), factor * traits::get_y(mouse), 0);
	}
}

// See equation 46 in Henriksen et al.
template<typename vec2, typename traits = vec2_traits<vec2>>
typename traits::vec3 holroyd_projection(const vec2 &mouse, typename traits::scalar radius) {
	const typename traits::scalar r2 = radius * radius;
	const typename traits::scalar d2 = traits::squared_norm(mouse);

	if (d2 <= r2 / 2) {
		// sphere
		return traits::construct_vec3(traits::get_x(mouse), traits::get_y(mouse), std::sqrt(r2 - d2));
	} else {
		// hyperbola
		return traits::construct_vec3(traits::get_x(mouse), traits::get_y(mouse), r2 / 2 / std::sqrt(d2));
	}
}

template<typename vec2, typename traits = vec2_traits<vec2>>
typename traits::quat mouse_move(const vec2 &old_pos, const vec2 &new_pos,
                                 typename traits::scalar radius, TrackballType type) {
	typename traits::vec3 p1, p2;

	switch (type) {
	case TrackballType::shoemake:
		p1 = shoemake_projection(old_pos, radius);
		p2 = shoemake_projection(new_pos, radius);
		break;
	case TrackballType::holroyd:
		p1 = holroyd_projection(old_pos, radius);
		p2 = holroyd_projection(new_pos, radius);
		break;
	}

	return traits::construct_quat(p1, p2);
}

} // namespace turbotrack

#endif // TURBOTRACK_HPP
