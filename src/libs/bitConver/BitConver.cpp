#include "BitConver.h"

union p {
	int a;
	char b;
};

int panduan_2( ) {
	p p1;
	p1.a = 1;
	return p1.a == p1.b;
}

bool bitConver::set::isLittleEndian( ) {
	static int32_t flage = 0;
	if( flage > 0 )
		return true;
	if( flage < 0 )
		return false;
	if( panduan_2() )
		flage = 1;
	else
		flage = -1;
	return flage > 0 ? true : false;
}