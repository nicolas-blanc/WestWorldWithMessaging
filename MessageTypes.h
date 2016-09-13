#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES

#include <string>

enum message_type
{
  Msg_HiHoneyImHome,
  Msg_StewReady,
  Msg_HiMamImHome,
  Msg_LittleStewReady,
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

  default:

    return "Not recognized!";
  }
}

#endif