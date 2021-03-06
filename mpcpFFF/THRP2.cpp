#include "TH2.h"
#include "RPower2.h"
#include "THRP2.h"
#include <iostream>
#include <petsc.h>
#include <cmath>


THRP2::THRP2()
{
	nRP = 18721;
	nTH = 11368;

	uRP = new PetscScalar [nRP];
	uTH = new PetscScalar [nTH];
}

THRP2::~THRP2()
{
	delete []uRP;
	delete []uTH;
}


void THRP2::settotalinitial(PetscScalar *array1,PetscScalar *array2,PetscScalar *array3,PetscScalar *array4,PetscScalar *array5,PetscScalar *array6,PetscScalar *array7,PetscScalar *array8,PetscScalar *array9,PetscScalar *array10,
		PetscScalar *array11,PetscScalar *array12,PetscScalar *array13,PetscScalar *array14,PetscScalar *array15,PetscScalar *array16,PetscScalar *array17,PetscScalar *array18,PetscScalar *array19,PetscScalar *array20)
		{
			TH2::setinitial(array1,array2,array3,array4,array5,array6,array7,array8,array9,array10);
			RPower2::setinitial(array11,array12,array13,array14,array15,array16,array17,array18,array19,array20);
		}

void THRP2::vecGetTHRPArray(const PetscScalar *u)
{
	PetscInt i;

	for (i = 0; i < 18721; i++)
	{
		uRP[i] = u[i];
	}
	for (i = 18721; i < 30089; i++)
	{
		uTH[i] = u[i];
	}
}

