#ifndef PRODUCT_H
#define PRODUCT_H
#include "CommonUAS.h"
namespace uas {
	typedef unsigned ID;
	enum  SensingProductEnum {
		FIND_P,
		FIX_P,
		TRACK_P,
		TARGET_P
	};
	struct Image {
	
	};
	
	struct DetectedObj {
		Location object_location; 
		time_t time_stamp; 
		ID  image_id;
		Image image;
	};

	struct FixedObj {
		ID image_id;
		ID toi_id;
		Objective objective;
	};

	struct TrackingObj {
		Location object_location;
		time_t time_stamp;
		ID toi_id;
	};

	struct TargetedObj {
		Location object_location;
		time_t time_stamp;
		ID toi_id;
		ID verified_by;
		ID approved_by;
	};

}
#endif