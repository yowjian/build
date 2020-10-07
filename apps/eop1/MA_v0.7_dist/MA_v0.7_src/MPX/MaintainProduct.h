#pragma once
#ifndef MAINTAIN_PRODUCT_H
#define MAINTAIN_PRODUCT_H
#ifdef _WIN32
# include <Windows.h>
#else
# include <unistd.h>
#endif
#include "Store.h"
#include "missions/Mission.h"
#include "missions/Product.h"


using namespace uas;
class MaintainProduct
{
private:
	int sleep_msec = 1000;
	time_t timer;
	Store<DetectedObj *> DETECT_Lst;
	Store<FixedObj *> TOI_Lst;
	Store<TrackingObj *> TRACK_Lst; 
	Store<TargetedObj *> TARGET_Lst;


public:
	MaintainProduct(int max_prod_size)
	:DETECT_Lst(Store<DetectedObj*>(max_prod_size)),
	TOI_Lst(Store<FixedObj*>(max_prod_size)),
	TRACK_Lst(Store<TrackingObj*>(max_prod_size)),
	TARGET_Lst(Store<TargetedObj*>(max_prod_size))
	{}

	~MaintainProduct() 
	{
		//DETECT_Lst.deleteAll();
		//TOI_Lst.deleteAll();
		//TRACK_Lst.deleteAll();
		//TARGET_Lst.deleteAll();
	}

	void onReceivingSensorProducts(const string& msg)
	{
		//convert msg to detects, fix, track, target  
		//save into storage accordingly 
	}

	void maintainStore(const SensingProductEnum& prod_type, string data)
	{
		switch (prod_type) {
		case FIND_P:
			getDetects(data);
			break;
		case FIX_P:
			getFIX(data);
			break;
		case TRACK_P:
			getTRACK(data);
			break;
		case TARGET_P:
			getTARGET(data);
			break;
		default:
			break;
		}
	}


	unsigned getDetects(string & data)
	{
		unsigned fnd_cf = 0;
		//fnd_cf =  update_DETECT_Lst.... 
		return fnd_cf; 
	}

	unsigned getFIX(string & data)
	{
		unsigned fix_cf = 0;
		//fnd_cf =  update_TOI_Lst.... 
		//send back to ISR Manager for valid  TOI entitied
		return fix_cf;
	}

	unsigned getTRACK(string & data)
	{
		unsigned trk_cf = 0;
		//fnd_cf =  update_TRACK_Lst.... 
		return trk_cf;
	}

	unsigned getTARGET(string & data)
	{
		unsigned tgt_cf = 0;
		//fnd_cf =  update_TARGET_Lst.... 
		return tgt_cf;
	}

};
#endif
