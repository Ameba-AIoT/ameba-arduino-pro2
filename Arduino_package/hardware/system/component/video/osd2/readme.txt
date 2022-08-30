//-------------------------isp_osd_example.c----------------------------//
For general usage, please refers to isp_osd_example.c to apply your OSD.
1. Add source isp_osd_example.c to your project.
2. After opening video, use below API to demonstrate OSD of each channel.
	-- void example_isp_osd(int idx, int ch_id, int txt_w, int txt_h);
	[int idx  ]:	Set 0 as default.
	[int ch_id]:	Channel ID. (Only available for 0~1)
	[int txt_w]:	Text width. (For example: 28)
	[int txt_h]:	Text height, which is twice of text width. (For example: 56)

	For example, show text size 28X56 in channel-0
	example_isp_osd(0, 0, 28, 56);


//--------------------------isp_osd_example_ext.c---------------------------//
For long run application, please refers to isp_osd_example_ext.c
1. Add source isp_osd_example_ext.c to your project.
2. After opening video, use below API to demonstrate OSD of each channel.
	-- void example_isp_osd(int idx, int ch_id, int txt_w, int txt_h, int scale);
	[int idx  ]:	Set 0 as default.
	[int ch_id]:	Channel ID. (Only available for 0~2)
	[int txt_w]:	Text width. (For example: 28)
	[int txt_h]:	Text height, which is twice of text width. (For example: 56)
	[int scale]:	scale value based on 100. (Suggest: set 100 for 1920X1080; 66 for 1280X720; 33 for 640X480...)

	For example, show text size 28X56 in channel-1 in resolution 1280X720
	example_isp_osd(0, 1, 28, 56, 66);
