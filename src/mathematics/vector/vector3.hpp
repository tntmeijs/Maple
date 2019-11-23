#ifndef MAPLE_VECTOR3_HPP
#define MAPLE_VECTOR3_HPP

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

		/** Returns the X component of the vector */
		double x() const;

		/** Returns the Y component of the vector */
		double y() const;

		/** Returns the Z component of the vector */
		double z() const;

		/** Set the X component of the vector */
		void x(double x);

		/** Set the Y component of the vector */
		void y(double y);

		/** Set the Z component of the vector */
		void z(double z);

		/** Returns the R component of the vector */
		double r() const;

		/** Returns the G component of the vector */
		double g() const;

		/** Returns the B component of the vector */
		double b() const;

		/** Set the R component of the vector */
		void r(double r);

		/** Set the G component of the vector */
		void g(double g);

		/** Set the B component of the vector */
		void b(double b);

	private:
		// Holds the X, Y, and Z components
		double m_memory[3];
	};
}

#endif //! MAPLE_VECTOR3_HPP
