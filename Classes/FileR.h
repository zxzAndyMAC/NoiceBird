#ifndef __FILE_R__
#define __FILE_R__

#include "Resource.h"
#ifdef BIRD_DEBUG

#include<stdio.h>
#include <stdlib.h>
#include "cocos2d.h"
USING_NS_CC;
class FileR
{
public:
	inline static void ReadConfig()
	{
#ifdef WIN32
		FILE *fp = fopen("configure.txt", "r");
#else
        FILE *fp = fopen("/Volumes/Development/NoiceBird/Resources/configure.txt", "r");
#endif

		char buf[30];
		char *x = fgets(buf, 50, fp);
		strncpy(buf,x+17,10);
		FLOOR_SPEED = atof(buf);

		x = fgets(buf, 50, fp);
		strncpy(buf,x+17,10);
		BIRD_ANIM_S = atof(buf);

		x = fgets(buf, 50, fp);
		strncpy(buf,x+17,10);
		MIN_LEFT_RIGHT = atof(buf);

		x = fgets(buf, 50, fp);
		strncpy(buf,x+17,10);
		MIN_DIS = atof(buf);

		x = fgets(buf, 50, fp);
		strncpy(buf,x+17,10);
		MAX_DIS = atof(buf);

		x = fgets(buf, 50, fp);
		strncpy(buf,x+17,10);
		BIRD_GRAVITY = atof(buf);

		x = fgets(buf, 50, fp);
		strncpy(buf,x+17,10);
		BIRD_VELOCITY = atof(buf);

		x = fgets(buf, 50, fp);
		strncpy(buf,x+17,10);
		BIRD_UP_VELOCITY = atof(buf);
        
        x = fgets(buf, 50, fp);
		strncpy(buf,x+17,10);
		MIN_UP_DOWN = atof(buf);

		fclose(fp);
	}
};

#endif

#endif