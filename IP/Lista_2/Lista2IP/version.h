#ifndef VERSION_H
#define VERSION_H

	//Software Status
	static const char STATUS[] =  "Alpha";
	static const char STATUS_SHORT[] =  "a";
	
	//Standard Version Type
	static const long MAJOR  = 1;
	static const long MINOR  = 4;
	static const long BUILD  = 142;
	static const long REVISION  = 119;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 189;
	#define RC_FILEVERSION 1,4,142,119
	#define RC_FILEVERSION_STRING "1, 4, 142, 119\0"
	static const char FULLVERSION_STRING [] = "1.4.142.119";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 2;
	

#endif //VERSION_H
