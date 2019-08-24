#ifndef PHYS_H
#define PHYS_H

#ifndef ACTION_C
extern double lagrangian(double x, double y);
extern double action(void);
extern double delta_S(int i, double alpha);
#endif

#ifndef CORR_C
extern double correlator(int t);
extern double deltaE(double c1, double c2, double c3);
extern double matrix_el(double c, double E, int t);
#endif

#endif
