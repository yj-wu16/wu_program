#
CFLAGS		 =
FFLAGS		 =
CPPFLAGS         =
FPPFLAGS         =
MANSEC           = Vec
LOCDIR		 = src/vec/vec/examples/tutorials/
EXAMPLESC	 = ex1.cpp Point.cpp ex2.c ex3.c ex5.c ex6.c ex7.c ex8.c ex9.c ex10.c \
                ex11.c ex12.c ex15.c ex16.c  ex18.c ex19.c ex42.c ex42a.c ex21.c ex43.c readsn2d.c
EXAMPLESF	 = ex1f.F90 ex1f90.F90 ex2f.F ex3f.F ex4f.F ex4f90.F90 ex7f.F ex9f.F90 ex11f.F ex14f.F90 ex20f90.F90 ex21f90.F90 ex43f.F90

include ${PETSC_DIR}/lib/petsc/conf/variables
include ${PETSC_DIR}/lib/petsc/conf/rules
include ${PETSC_DIR}/lib/petsc/conf/test

ex7: ex7.o ex7f.o
ex21f90: ex21f90.o ex21.o
ex43f: ex43.o ex43f.o
myprogram: myprogram.o Point.o chkopts
	${CLINKER} -o myprogram myprogram.o Point.o ${PETSC_LIB}
