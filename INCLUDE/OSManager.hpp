#ifndef OSMANAGER_HPP
#define OSMANAGER_HPP

#include <Manager.hpp>

class COSManager : public CManager
{
  public:

    void Dispatch(Json& json) override
    {
      if (json.HasKey("req"))
      {
        auto req = json.GetKey("req");

        if (req == "get-active-sessions")
        {
          GetActiveSessions(json);
        }
        else if (req == "get-volumes")
        {
          GetVolumes(json);
        }
      }
      else
      {

      }
    }

    void GetActiveSessions(Json& json)
    {
      std::vector<Json> sv;

      auto& it = SessionMap.begin();

      while (it != SessionMap.end())
      {
        if (((*it).second)->IsConnected())
        {
          Json s;
          s.SetKey("sid", (*it).first);
          sv.push_back(s);
          ++it;
        } 
        else
        {
          it = SessionMap.erase(it);
        }
      }

      auto sa = Json::JsonListToArray(sv);
      json.SetKey("sessions", sa);
      SendResponse(json);
    }

    void GetVolumes(Json& json)
    {
      auto sid = json.GetKey("sid");


    }

};

using SPCOSManager = std::shared_ptr<COSManager>;
using WPCOSManager = std::weak_ptr<COSManager>;

#endif //OSMANAGER_HPP