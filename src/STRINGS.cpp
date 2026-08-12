#include "STRINGS.h"

 std::string getTitleByStatistic(int stat, bool first)
 {
	 switch (stat)
	 {
	 case STATISTIC_DISTANCE:
		 return first ? "Gotta go far" : "Secret Society BLANKET";
	 case STATISTIC_TARGET:
		 return first ? "Most wanted" : "Low profile";
	 case STATISTIC_FAILED:
		 return first ? "It was not me" : "The expert";
	 case STATISTIC_GREED:
		 return first ? "The greed God" : "The floor is lava";
	 case STATISTIC_INSHARE:
		 return first ? "Heart of the party" : "True egoist";
	 case STATISTIC_STILL:
		 return first ? "Prettiest Statue" : "Hyperactive";
	 default:
		 return "";
	 }
 }

 std::string getDescriptionByStatistic(int stat, bool first)
 {
	 switch (stat)
	 {
	 case STATISTIC_DISTANCE:
		 return first ? "the player that traveled the most." : "the player that traveled the least.";
	 case STATISTIC_TARGET:
		 return first ? "the player who got targeted the most." : "the player who got targeted the least.";
	 case STATISTIC_FAILED:
		 return first ? "the player who failed the most." : "the player who failed the least.";
	 case STATISTIC_GREED:
		 return first ? "the player who spent the most time in dangerous zones." : "the player who spent the least time in dangerous zones.";
	 case STATISTIC_INSHARE:
		 return first ? "the player who went in towers with other players the most." : "the player who went in towers with other players the least.";
	 case STATISTIC_STILL:
		 return first ? "the player who stood still the most." : "the player who stood still the least.";
	 default:
		 return "";
	 }
 }
