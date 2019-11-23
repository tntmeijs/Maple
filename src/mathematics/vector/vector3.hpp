#ifndef MAPLE_VECTOR3_HPP
#define MAPLE_VECTOR3_HPP

#include <cstddef>	// std::size_t

namespace mpl::math
{
	/**
	 * Vector 3 class that takes care of vector arithmetic
	 */
	class Vector3
	{
	public:
		/** Create a new vector 3 with zeroed-out members */
		Vector3();

		/** Create a new vector 3 and set all members to the same value */
		Vector3(double initial_xyz);

		/** Create a new vector3 and set all members to the specified value */
		Vector3(double initial_x, double initial_y, double initial_z);

		~Vector3();

		/** Positive vector, no need to do anything */
		const Vector3& operator+() const;

		/** Negate the vector */
		const Vector3 operator-() const;

		/** Add a vector to this vector */
		friend Vector3 operator+(const Vector3 a, const Vector3 b);

		/** Subtract a vector from this vector */
		friend Vector3 operator-(const Vector3 a, const Vector3 b);

		/** Multiply a vector by this vector */
		friend Vector3 operator*(const Vector3 a, const Vector3 b);

		/** Divide a vector by this vector */
		friend Vector3 operator/(const Vector3 a, const Vector3 b);

		/** Access a member by index */
		double operator[](std::size_t index) const;
		double& operator[](std::size_t index);

		/** Add a vector to this vector */
		Vector3& operator+=(const Vector3& other);

		/** Subtract a vector from this vector */
		Vector3& operator-=(const Vector3& other);

		/** Multiply this vector by a vector */
		Vector3& operator*=(const Vector3& other);

		/** Divide this vector by a vector */
		Vector3& operator/=(const Vector3& other);

		/** Multiply every component by a scalar value */
		Vector3& operator*=(const double scalar);

		/** Divide every component by a scalar value */
		Vector3& operator/=(const double scalar);

		/** Returns the X component of the vector */
		double X() const;

		/** Returns the Y component of the vector */
		double Y() const;

		/** Returns the Z component of the vector */
		double Z() const;

		/** Set the X component of the vector */
		void X(double x);

		/** Set the Y component of the vector */
		void Y(double y);

		/** Set the Z component of the vector */
		void Z(double z);

		/** Returns the R component of the vector */
		double R() const;

		/** Returns the G component of the vector */
		double G() const;

		/** Returns the B component of the vector */
		double B() const;

		/** Set the R component of the vector */
		void R(double r);

		/** Set the G component of the vector */
		void G(double g);

		/** Set the B component of the vector */
		void B(double b);

		/** Get the length of the vector */
		double Length() const;

		/** Get the squared length of the vector */
		double LengthSquared() const;

		/** Turn this vector into a unit vector */
		void Normalize();

		/** Return a new normalized vector */
		Vector3 Normalized() const;

		/** Dot product between this vector and the other vector */
		double Dot(const Vector3& other) const;
		
		/** Cross product between this vector and the other vector */
		Vector3 Cross(const Vector3& other) const;

	private:
		// Holds the X, Y, and Z components
		double m_memory[3];
	};
}

#endif //! MAPLE_VECTOR3_HPP
