/*------------------------------------------------------------------------------
--                                                                                                                               --
--       This software is confidential and proprietary and may be used                                   --
--        only as expressly authorized by a licensing agreement from                                     --
--                                                                                                                               --
--                            Verisilicon.                                                                                    --
--                                                                                                                               --
--                   (C) COPYRIGHT 2014 VERISILICON                                                            --
--                            ALL RIGHTS RESERVED                                                                    --
--                                                                                                                               --
--                 The entire notice above must be reproduced                                                 --
--                  on all copies and should not be removed.                                                    --
--                                                                                                                               --
--------------------------------------------------------------------------------*/

#ifndef HAL_VIDEO_CMD_H
#define HAL_VIDEO_CMD_H

#include "base_type.h"
#include "hal_video.h"

struct option {
	char *long_opt;
	char short_opt;
	i32 enable;
};

struct parameter {
	i32 cnt;
	char *argument;
	char short_opt;
	char *longOpt;
	i32 enable;
};

i32 get_option(i32 argc, char **argv, struct option *, struct parameter *);
int ParseDelim(char *optArg, char delim);
int HasDelim(char *optArg, char delim);

i32 parameter_enc_get(i32 argc, char **argv, commandLine_s *cml) ;
int parameter_jpg_get(i32 argc, char **argv, commandLine_s *cml);

void default_parameter(commandLine_s *cml);



int parse_stream_cfg(const char *streamcfg, commandLine_s *pcml);


#endif //
