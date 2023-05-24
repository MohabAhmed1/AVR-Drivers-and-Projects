#ifndef BIT_MATH_H_INCLUDED
#define BIT_MATH_H_INCLU

#define SET_BIT(VAR,BIT_NUM) VAR|=(1<<BIT_NUM)
#define CLR_BIT(VAR,BIT_NUM) VAR&=~(1<<BIT_NUM)
#define TOGGLE_BIT(VAR,BIT_NUM) VAR^=(1<<BIT_NUM)
#define GET_BIT(VAR,BIT_NUM) ((VAR>>BIT_NUM)&1)


#endif // BIT_MATH_H_INCLUDED
