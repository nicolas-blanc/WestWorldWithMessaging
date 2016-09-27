#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES

#include <string>

enum message_type
{
  Msg_HiHoneyImHome,
  Msg_StewReady,
  Msg_HiMamImHome,
  Msg_LittleStewReady,
  Msg_DadWork,
  Msg_BeerReady,
  Msg_PretzelReady,
  Msg_MinerAtSaloon,
  Msg_DrunkStartFight,
  Msg_DrunkStopFight
};


inline std::string MsgToStr(int msg)
{
  switch (msg)
  {
  case Msg_HiHoneyImHome:
    
    return "HiHoneyImHome"; 

  case Msg_StewReady:
    
    return "StewReady";

  case Msg_HiMamImHome:
	
	  return "HiMamImHome";

  case Msg_LittleStewReady:

	  return "LittleStewReady";

  case Msg_DadWork:

	  return "DadWork";
  case Msg_BeerReady:

	  return "BeerReady";
  case Msg_PretzelReady:
	  return "PretzelReady";
  case Msg_DrunkStartFight:
	  return "DrunkStartFight";
  case Msg_DrunkStopFight:
	  return "DrunkStopFight";
  case Msg_MinerAtSaloon:
	  return "MinerAtSaloon";

  default:

    return "Not recognized!";
  }
}

#endif