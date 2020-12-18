#pragma once
#ifndef ISRM_FIND_FIX_H
#define ISRM_FIND_FIX_H
#include <random>
#include <string>
#include <amqm/AMQManager.h>

static const int MAX_RETURN_LIMIT = 10;
static const int TGT_LIST_SIZE = 11;
static const std::string ISRM_MPU_DATA_CHANNEL_NAME = "ISRM_Data";


class ISRM_Data
{

public:
    ISRM_Data()
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> bearing_Random(0.0, 360.0); // 0 -360 heading in degrees
        std::uniform_real_distribution<double> speed_Random(0.0, 25.0); // 0-25 KpH
        std::uniform_real_distribution<double> y_Random(-180.0, 180.0); // 
        std::uniform_real_distribution<double> x_Random(-90.0, 90.0); // 
        std::uniform_int_distribution<int> tgt_Lst_Random(0, (TGT_LIST_SIZE));
        std::uniform_int_distribution<int> tgt_Confidence_Random(0, 100);
        for (auto i = 0; i < MAX_RETURN_LIMIT; i++)
        {
            all_Tgt_Data[i].tgt_ID = i + 1;
            all_Tgt_Data[i].tgt_Find_Speed = -1;
            all_Tgt_Data[i].tgt_Find_Bearing = -1;
            all_Tgt_Data[i].tgt_Fix_Speed = speed_Random(mt);
            all_Tgt_Data[i].tgt_Fix_Bearing = bearing_Random(mt);
            all_Tgt_Data[i].tgt_Find_Confidence = tgt_Confidence_Random(mt);
            all_Tgt_Data[i].tgt_Fix_Confidence = tgt_Confidence_Random(mt);
            int temp_Tgt_ID_List_It = tgt_Lst_Random(mt);
            all_Tgt_Data[i].tgt_Find_ID = tgt_Id_List[temp_Tgt_ID_List_It].generic_Id;
            std::stringstream ss;
            ss << tgt_Id_List[temp_Tgt_ID_List_It].generic_Id << " - " << tgt_Id_List[temp_Tgt_ID_List_It].detailed_Id;
            all_Tgt_Data[i].tgt_Fix_ID = ss.str();
            double temp_Coord_Double = y_Random(mt);
            all_Tgt_Data[i].tgt_Y_Fix_Coords = temp_Coord_Double;
            all_Tgt_Data[i].tgt_Y_Find_Coords = round_Double(temp_Coord_Double);
            temp_Coord_Double = x_Random(mt);
            all_Tgt_Data[i].tgt_X_Fix_Coords = temp_Coord_Double;
            all_Tgt_Data[i].tgt_X_Find_Coords = round_Double(temp_Coord_Double);
        }
    }

    json send_Fix_Level_Detail(void)
    {
        json jsonObjects = json::array();

        for (auto i = 0; i < MAX_RETURN_LIMIT; i++)
        {
            json j = json::object();
            j["TGT_ISRM_ID"] = all_Tgt_Data[i].tgt_ID;
            j["classification"] = all_Tgt_Data[i].tgt_Fix_ID;
            j["confidence"] = all_Tgt_Data[i].tgt_Fix_Confidence;
            j["x"] = all_Tgt_Data[i].tgt_X_Fix_Coords;
            j["y"] = all_Tgt_Data[i].tgt_Y_Fix_Coords;
            j["bearing"] = all_Tgt_Data[i].tgt_Fix_Bearing;
            j["speed"] = all_Tgt_Data[i].tgt_Fix_Speed;
            jsonObjects.push_back(j);
        }
        return jsonObjects;
        //amq.publish(ISRM_MPU_DATA_CHANNEL_NAME, jsonObjects, true);
    }
    json send_Find_Level_Detail(void)
    {

        json jsonObjects = json::array();

        for (auto i = 0; i < MAX_RETURN_LIMIT; i++)
        {
            json j = json::object();
            j["TGT_ISRM_ID"] = all_Tgt_Data[i].tgt_ID;
            j["classification"] = all_Tgt_Data[i].tgt_Find_ID;
            j["confidence"] = all_Tgt_Data[i].tgt_Find_Confidence;
            j["x"] = all_Tgt_Data[i].tgt_X_Find_Coords;
            j["y"] = all_Tgt_Data[i].tgt_Y_Find_Coords;
            j["bearing"] = all_Tgt_Data[i].tgt_Find_Bearing;
            j["speed"] = all_Tgt_Data[i].tgt_Find_Speed;
            jsonObjects.push_back(j);
        }

        return jsonObjects;
        //amq.publish(ISRM_MPU_DATA_CHANNEL_NAME, jsonObjects, true);
    }
private:
   // AMQManager amq;

    struct tgt_Data {
        int tgt_ID;
        std::string tgt_Find_ID;
        double tgt_X_Find_Coords;
        double tgt_Y_Find_Coords;
        double tgt_Find_Bearing;
        double tgt_Find_Speed;
        int tgt_Find_Confidence;

        std::string tgt_Fix_ID;
        double tgt_X_Fix_Coords;
        double tgt_Y_Fix_Coords;
        double tgt_Fix_Speed;
        double tgt_Fix_Bearing;
        int tgt_Fix_Confidence;
    };

    tgt_Data all_Tgt_Data[10];

    struct tgt_Id
    {
        std::string generic_Id;
        std::string detailed_Id;
    };

    tgt_Id tgt_Id_List[12] =
    {
        {"Standard_Vehicle", "Pickup Truck"},
        {"Standard_Vehicle", "Sedan"},
        {"Standard_Vehicle", "Motorcycle"},
        {"Standard_Vehicle", "Semi"},
        {"Standard_Vehicle", "SUV"},
        {"Military_Vehicle", "Tank"},
        {"Military_Vehicle", "APC"},
        {"Military_Vehicle", "Amphibious_Assault"},
        {"Military_Vehicle", "LAV"},
        {"Military_Vehicle", "Artillery"},
        {"Military_Vehicle", "Anti-Aircraft"},
        {"Military_Vehicle", "Prime_Mover"}
    };

    double round_Double(double full_Length_Double)
    {
        double rounded_Double = std::round(full_Length_Double *10.0) / 10.0;
        return rounded_Double;
    }
};




#endif