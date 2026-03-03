struct lconv_dummy{
	char decimal_point[1];
} dummy;

struct lconv_dummy* localeconv(){
	dummy.decimal_point[0] = '.';
	return &dummy;
}
