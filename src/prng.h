#ifndef PNRG_H
#define PNRG_H


typedef unsigned long int  u4;
typedef struct ranctx { u4 a; u4 b; u4 c; u4 d; } ranctx;

extern ranctx gRanctx;
u4 ranval( ranctx *x );
void raninit( ranctx *x, u4 seed );

#define rand() (ranval(&gRanctx))
#define srand(a) (raninit(&gRanctx, a))

#define RAND_MAX 1024

#endif //PNRG_H
