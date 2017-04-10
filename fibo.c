#include "m_pd.h" 

static char *version = "[fibo] v. 1 (2017) for Pd written by Ricky Graham <ricky@rickygraham.net>";

static t_class *fibo_class;

typedef struct _fibo {
t_object x_obj;
t_float a, time;
t_int i, order;
t_inlet *in_2; 
t_outlet *out;

}t_fibo;


int fibonacci(int i) {

   if(i == 0) {
      return 0;
   }
	
   if(i == 1) {
      return 1;
   }
   return fibonacci(i-1) + fibonacci(i-2);
}


void *fibo_new(void){
t_fibo *x = (t_fibo *) pd_new(fibo_class); /*this is pointer*/
x->in_2 = floatinlet_new(&x->x_obj, &x->a); //length of fibonacci sequence
x->a = 10;
x->order = 0;
x->out = outlet_new(&x->x_obj, &s_float);
return (void *)x; /*return x cast as generic pointer */
}

void fibo_free(t_fibo *x){
inlet_free(x->in_2);
outlet_free(x->out);
}


void forward(t_fibo *x){
x->order = 1;
}

void backward(t_fibo *x){
x->order = 0;	
}

void clear(t_fibo *x){

x->a = 0;
x->order = 1;
x->i = 0;
	
}


void fibo_bang(t_fibo *x) {  

   if(x->i <= x->a && x->order == 0){
   x->time = fibonacci(x->a - x->i);
   outlet_float(x->out, x->time);
   x->i++; 
   //post("%d", x->i);
   } else if(x->i <= x->a && x->order == 1){
   x->time = fibonacci(x->i);
   outlet_float(x->out, x->time);
   x->i++; 
   } else {
   x->i = 0;   
   }
}
    

void fibo_setup(void){
fibo_class = class_new(gensym("fibo"), (t_newmethod)fibo_new, 
(t_method)fibo_free,
sizeof(t_fibo),
CLASS_DEFAULT, 0);
class_addbang(fibo_class, fibo_bang);
class_addmethod(fibo_class, (t_method)forward, gensym("forward"), 0);
class_addmethod(fibo_class, (t_method)backward, gensym("backward"), 0);
class_addmethod(fibo_class, (t_method)clear, gensym("clear"), 0);
class_sethelpsymbol(fibo_class, gensym("fibo"));
post(version);
}   
