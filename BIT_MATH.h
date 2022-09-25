#ifndef  BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(num,index)        num=(1<<index)|num
#define CLR_BIT(num,index)        num=num&(~(1<<index))
#define GET_BIT(num,index)        num&(1<<index)
#define TOGGLE_BIT(num,index) 	  num=num^(1<<index)

#endif
