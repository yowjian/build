#ifndef COMMON_UAS_H
#define COMMON_UAS_H

namespace uas {
	typedef  unsigned UID;
	/**
	 * @brief a Point consiting of x and y values
	 * 
	 */
	struct Point {
		/// x value of point
		double x;
		/// y value of point
		double y;
		/// required empty constructor 
		Point() {

		}
		/// constructor with x and y values set
		Point(double nx, double ny) {
			x = nx;
			y = ny;
		}
	};
	/**
	 * @brief Location of an object on a 3D scale
	 * 
	 */
	struct Location {
		/// x or latitude value on a map
		double x; 
		/// y or longitude value on a map
		double y;
		/// z or latitude value on a map
		double z;
	};
	/**
	 * @brief Area bounded in a square with 2 points
	 * 
	 */
	struct Area {
		///required empty constructor
		Area() {

		}
		/// top left point of square
		Point upper_left;
		/// bottom right point of a square
		Point bottom_right;
	};
	/**
	 * @brief Time in any units represented as non-float
	 * 
	 */
	struct Time {
		/// long integer, usually millisecond
		long time;
	};
}
#endif
