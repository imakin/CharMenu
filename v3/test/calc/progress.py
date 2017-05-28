#!/usr/bin/env python3
def progress(pos, scale):
	pixels_per_char = 6
	max_chars = 16
	max_progress = max_chars * pixels_per_char
	
	progress = (pos/scale)*max_progress
	print(int ((pos/scale)*max_chars) )
	for i in range(0,max_chars):
		if i==int((pos/scale)*max_chars):
			print("|",end="")
		elif i< ((pos/scale)*max_chars):
			print(" ",end="")
		elif i> ((pos/scale)*max_chars):
			print(" ",end="")
	print("")

for x in range(0,20):
	progress(x,20)
	
"""

96-------------------------------------
20
20/96*16

	const uint8_t progresspixels_per_char = 6;
	
	cm_LcdGotoXY(0,1);
	//~ LCDprogressBar(sNum, sMax,16);
	//~ return;
	uint8_t progress=sNum; uint8_t maxprogress=sMax; uint8_t length=16;
	uint8_t i;
	uint16_t pixelprogress;
	uint8_t c;
	uint8_t progresswidth = length/maxprogress;
	pixelprogress = ((progress*(length*progresspixels_per_char))/maxprogress)/2;
	
	// print exactly "length" characters
	for(i=0; i<length; i++)
	{
		if (
			(
				((i*(uint16_t)progresspixels_per_char)+progresswidth)>(pixelprogress-progresswidth)
			)
			&&
			(
				((i*(uint16_t)progresspixels_per_char)+progresswidth)<(pixelprogress+progresswidth)
			)
		)
		{
			c = 5;
		}
		else
		{
			c = 0;
		}
		// write character to display
		LCDsendChar(c);
	}
	return;
"""
