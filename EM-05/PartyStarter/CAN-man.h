/*I'm the CAN-man

Ski-bi dibby dib yo da dub dub
Yo da dub dub
Ski-bi dibby dib yo da dub dub
Yo da dub dub
(I'm the CAN-man)
Ski-bi dibby dib yo da dub dub
Yo da dub dub
Ski-bi dibby dib yo da dub dub
Yo da dub dub

Ba-da-ba-da-ba-be bop bop bodda bope
Bop ba bodda bope
Be bop ba bodda bope
Bop ba bodda 
Ba-da-ba-da-ba-be bop ba bodda bope
Bop ba bodda bope
Be bop ba bodda bope
Bop ba bodda bope*/
#pragma once
#include "chip.h"
#define TEST_CCAN_BAUD_RATE 500000
CCAN_MSG_OBJ_T msg_obj;


void baudrateCalculate(uint32_t baud_rate, uint32_t *can_api_timing_cfg)
 {
	  uint32_t pClk, div, quanta, segs, seg1, seg2, clk_per_bit, can_sjw;
	 Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_CAN);
	 pClk = Chip_Clock_GetMainClockRate();
	
		  clk_per_bit = pClk / baud_rate;
 for (div = 0; div <= 15; div++) {
		   for (quanta = 1; quanta <= 32; quanta++) {
			    for (segs = 3; segs <= 17; segs++) {
				     if (clk_per_bit == (segs * quanta * (div + 1))) {
					      segs -= 3;
					      seg1 = segs / 2;
					      seg2 = segs - seg1;
					      can_sjw = seg1 > 3 ? 3 : seg1;
					      can_api_timing_cfg[0] = div;
					      can_api_timing_cfg[1] =
					       ((quanta - 1) & 0x3F) | (can_sjw & 0x03) << 6 | (seg1 & 0x0F) << 8 | (seg2 & 0x07) << 12;
					      return;
					
				}
				
			}
			
		}
		
	}
	 }

/* CAN receive callback */
 /* Function is executed by the Callback handler after
     a CAN message has been received */
 void CAN_rx(uint8_t msg_obj_num) {
  /* Determine which CAN message has been received */
		 msg_obj.msgobj = msg_obj_num;
	  /* Now load up the msg_obj structure with the CAN message */
	  LPC_CCAN_API->can_receive(&msg_obj);
	  if (msg_obj_num == 1) {
	   /* Simply transmit CAN frame (echo) with with ID +0x100 via buffer 2 */
	   msg_obj.msgobj = 2;
	   msg_obj.mode_id += 0x100;
	   LPC_CCAN_API->can_transmit(&msg_obj);
	
	}
	
}
