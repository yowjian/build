#ifndef PROGRESS_MATRIC_H
#define PROGRESS_MATRIC_H
#include "CommonUAS.h"
namespace uas {
	enum  KillChainEnum {
		INGRESS,
		FIND,
		FIX,
		TRACK,
		TARGET,
		ENGAGE,
		ASSESS,
		ENGRESS
	};

	struct ProgressMatric {
		unsigned confidence_percentage;
		KillChainEnum kill_chain_state;
	};
}
#endif
