#ifndef COMMON_UAS_H
#define COMMON_UAS_H

namespace uas {
	typedef  unsigned UID;
	struct Point {
		double x;
		double y;
		Point() {

		}
		Point(double nx, double ny) {
			x = nx;
			y = ny;
		}
	};
	struct Location {
		double x; 
		double y;
		double z;
	};

	struct Area {
		Area() {

		}
		Point upper_left;
		Point bottom_right;
	};

	struct Time {
		long time;
	};
}
#endif
