#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>

#define IEEE80211_HT_MCS_MASK_LEN 256 

struct ieee80211_sub_if_data
{
	int x;
	struct ieee80211_sub_if_data *next;
};



//
// Linus: sizeof(mcs_mask)" is _shit_!! 這code簡直是一坨屎, 一坨屎, 一坨屎。很重要，念三次 XD
//原因是對array argument做sizeof會得到的是pointer的size。array argument不是真正的存在C語言，他只是被當作一個pointer。而且用錯就是算了，你不知道計算array size有 ARRAY_SIZE()可以用嗎？ 補充：include/linux/kernel.h #define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]) + __must_be_array(arr))

 static int rate_control_cap_mask(struct ieee80211_sub_if_data *sdata,
                                   unsigned int mcs_mask[IEEE80211_HT_MCS_MASK_LEN])
{
	unsigned int i;
	// sizeof’ on array function parameter ‘mcs_mask’ will return size of ‘unsigned in
	printf("mcsmask %u \n",sizeof(mcs_mask));
	for (i = 0; i < sizeof(mcs_mask); i++)
		printf(" %d ",mcs_mask[i]);
}

int main(){
	unsigned int array[100]={0};
	rate_control_cap_mask(0,array);
}
