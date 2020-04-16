
extern void to_umode();

void user_wrapper(void (*entry)(), void *p1, void *p2){
	to_umode();
	entry(p1, p2);

}
