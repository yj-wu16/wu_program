
#include "TH3.h"
#include <iostream>
#include <petsc.h>
#include <cmath>

TH3::TH3()
{
	n1 = 4784;
	THCVal = new PetscScalar [n1];
	n2 = 4725;
	THCVbl = new PetscScalar [n2];
	n3 = 4680;
	THCVdxl = new PetscScalar [n3];
	n4 = 4680;
	THCVdyl = new PetscScalar [n4];
	n5 = 4680;
	THCVvl = new PetscScalar [n5];
	n6 = 9000;
	THd = new PetscScalar [n6];
	n7 = 9000;
	THee = new PetscScalar [n7];
	n8 = 9000;
	THg = new PetscScalar [n8];
	n9 = 9000;
	THl = new PetscScalar [n9];
	mtth = new PetscInt  [n4];
	Kseff = new PetscScalar [n9];
	Kf    = new PetscScalar [n9];
	ROUf  = new PetscScalar [n9];
	Alpha = new PetscScalar [n9];
	KK    = new PetscScalar [n9];
	Kseffx= new PetscScalar [n9];
	Kseffy= new PetscScalar [n9];
	Kx    = new PetscScalar [n9];
	Ky    = new PetscScalar [n9];
	Kfx   = new PetscScalar [n9];
	Kfy   = new PetscScalar [n9];
	ROUfx = new PetscScalar [n9];
	ROUfy = new PetscScalar [n9];
	n21   = 1672;
	THP   = new PetscScalar [n21];
	THTf   = new PetscScalar [n21];
	THTs   = new PetscScalar [n3];
	ROUs   = new PetscScalar [n9];
	Cps    = new PetscScalar [n9];
	THU   = new PetscScalar [n21];
	THV   = new PetscScalar [n21];
	THQfth   = new PetscScalar [n3];
}

TH3::~TH3()
{
    delete []THCVal;
	delete []THCVbl;
	delete []THCVdxl;
	delete []THCVdyl;
	delete []THCVvl;
	delete []THd;
	delete []THee;
	delete []THg;
	delete []THl;
	delete []Kseff;
	delete []Kf;
	delete []ROUf;
	delete []Alpha;
	delete []KK;
	delete []Kseffx;
	delete []Kseffy;
	delete []Kx;
	delete []Ky;
	delete []Kfx;
	delete []Kfy;
	delete []ROUfx;
	delete []ROUfy;
	delete []THP;
	delete []THTf;
	delete []THTs;
	delete []THU;
	delete []THV;
	delete []THQfth;
	delete []ROUs;
	delete []Cps;
}

void TH3::setinitial(PetscScalar *array1,PetscScalar *array2,PetscScalar *array3,PetscScalar *array4,PetscScalar *array5,PetscScalar *array6,PetscScalar *array7,PetscScalar *array8,PetscScalar *array9,PetscScalar *array10)
{
	for (int i = 0; i < 4784; i++)
	{
		THCVal[i] = array1[i];
	}

	for (int i = 0; i < 4725; i++)
	{
		THCVbl[i] = array2[i];
	}

	for (int i = 0; i < 4680; i++)
	{
		THCVdxl[i] = array3[i];
	}

	for (int i = 0; i < 4680; i++)
	{
		THCVdyl[i] = array4[i];
	}

	for (int i = 0; i < 4680; i++)
	{
		THCVvl[i] = array5[i];
	}

	for (int i = 0; i < 9000; i++)
	{
		THd[i] = array6[i];
	}
	for (int i = 0; i < 9000; i++)
	{
		THee[i] = array7[i];
	}

	for (int i = 0; i < 9000; i++)
	{
		THg[i] = array8[i];
	}

	for (int i = 0; i < 9000; i++)
	{
		THl[i] = array9[i];
	}
	for (int i = 0; i < 4680; i++)
	{
		mtth[i] = array10[i];
	}
	for (int i = 0; i < 9000; i++)
	{
		Kseff[i] = 0.0;
		Kf[i]    = 0.0;
		KK[i]    = 0.0;
		ROUf[i]  = 0.0;
		Alpha[i] = 0.0;
		Kseffx[i]= 0.0;
		Kseffy[i]= 0.0;
		Kx[i]    = 0.0;
		Ky[i]    = 0.0;
		Kfx[i]   = 0.0;
		Kfy[i]   = 0.0;
		ROUfx[i] = 0.0;
		ROUfy[i] = 0.0;
		ROUs[i]  = 0.0;
		Cps[i]   = 0.0;
	}

}

void TH3::setTHinitial(PetscScalar *array21,PetscScalar *array22,PetscScalar *array23,PetscScalar *array24,PetscScalar *array25,PetscScalar *array26)
{
	for (int i = 0; i < 1672; i++)
	{
		THP[i] = array21[i];
		THTf[i]= array22[i];
		
		THU[i] = array24[i];
		THV[i] = array25[i];
		//THQfth[i] = array26[i];
	}
	for (int i = 0; i < 4680; i++)
	{
		THTs[i]   = array23[i];
		THQfth[i] = 0.0;
	}
}

void TH3::setparameter(PetscInt i , PetscInt j, PetscScalar Ts, PetscScalar Tf, PetscScalar P, PetscScalar U, PetscScalar V)
{
	PetscInt indexmtth,indexKseff,indexee,indexKf,indexROUf,indexTHd,indexTHl,indexAlpha,indexKK;
	PetscScalar Cpf,eta,Ref,Pr,Nu,nu1,nu11,nu2,nu3,nu31,k1;

	Cpf        = 5195.0;
	indexmtth  = 45*(j-1)+i-1;
	indexKseff = 45*(j-1)+i-1;
	indexee    = 45*(j-1)+i-1;
	indexKf    = 45*(j-1)+i-1;
	indexROUf  = 45*(j-1)+i-1;
	indexTHd   = 45*(j-1)+i-1;
	indexAlpha = 45*(j-1)+i-1;
	indexTHl   = 45*(j-1)+i-1;
	indexKK    = 45*(j-1)+i-1;
	/* part for Kseff */
	if (mtth[indexmtth] == 1)
	{
		Kseff[indexKseff] = 1.9*(1.0e-3)*pow(Ts+273.0-150.0,1.29);
		Kseff[indexKseff] = Kseff[indexKseff]*180;
		ROUs[indexKseff]  = 1.78e3;
		Cps[indexKseff]   = 1697.0;
	}
	else if (mtth[indexmtth]==2 || mtth[indexmtth]==3 || mtth[indexmtth]==4 || mtth[indexmtth]==5 || mtth[indexmtth]==6 || mtth[indexmtth]==7)
	{
		Kseff[indexKseff] = 1.2*100*(1+0.01*(156.48-3*log(Ts+144.0)));
		Kseff[indexKseff] = Kseff[indexKseff]*0.35*20;
		ROUs[indexKseff]  = 1.55e3;
		Cps[indexKseff]   = 1.0e6*1.75*(0.645+3.14*(Ts+273.0)/1000.0-2.809*pow((Ts+273.0)/1000.0,2.0)
			+0.959*pow((Ts+273.0)/1000.0,3.0))/ROUs[indexKseff];
	}
	else if (mtth[indexmtth]==8)
	{
		Kseff[indexKseff] = 100.0*(0.05+0.03*(Ts+273.0)*1.0e-3);
		Kseff[indexKseff] = Kseff[indexKseff]*10.0;
		ROUs[indexKseff]  = 1.75e3;
		Cps[indexKseff]   = 1.0e6*1.55*(0.645+3.14*(Ts+273.0)/1000.0-2.809*pow((Ts+273.0)/1000.0,2.0)
			+0.959*pow((Ts+273.0)/1000.0,3.0))/ROUs[indexKseff];
	}
	// else
	// {
	// 	Kseff[indexKseff] = 0.0;
	// }
	Kseff[indexKseff] = Kseff[indexKseff]*THee[indexee];

	if (mtth[indexmtth]==1)
	{
	
	/* part for Kf part for ROUf */
	if (mtth[indexmtth]==1 ||mtth[indexmtth]==2 ||mtth[indexmtth]==3 ||mtth[indexmtth]==4 || j==6 || j==7 || j==94)
	{
		Kf[indexKf] = 2.682*(1.0e-3)*(1.0+1.123*(1.0e-8 * P))*pow(Tf+273.15,0.71*(1.0-2.0*1.0e-9*P));
        ROUf[indexROUf] = (0.4814*P/1.0e3/(Tf+273.15))/(1.0+0.446*(1.0e-2)*P/1.0e3/(pow(Tf+273.15,1.2)));
        eta = (3.674*1.0e-7)*pow(Tf+273.15,0.7);
        Ref = THd[indexTHd]*sqrt(U*U+V*V)/eta;
        Pr  = eta*Cpf/Kf[indexKf];
	}

	/* part for alpha */
	if (mtth[indexmtth]==1 || j==7 || j==6)
	{
		Nu = 1.27*pow(Pr,1.0/3.0)*pow(Ref,0.36)/(pow(1.0-THee[indexee],1.18))+0.03*pow(Pr,0.5)*pow(Ref,0.86)/(pow(1.0-THee[indexee],1.07));
		Alpha[indexAlpha] = Nu*Kf[indexKf]*6.0*THee[indexee]/(THd[indexTHd]*THd[indexTHd]);
	}
	else if (mtth[indexmtth]==2 || mtth[indexmtth]==3)
	{
		nu11 = pow(3.66,3.0)+pow(1.61,3.0)*Ref*Pr/THl[indexTHl];
		nu1 = pow(nu11,1.0/3.0);
		nu2 = 0.664*pow(Pr,1.0/3.0)*sqrt(Ref*THd[indexTHd]/THl[indexTHl]);
		nu31= (1.82*pow(log10(Ref-1.64),-2.0))/8.0;
		nu3 = (1.82*pow(log10(Ref-1.64),-2.0))/8.0*(Ref-1000.0)*Pr*(1.0+pow(THd[indexTHd]/THl[indexTHl],2.0/3.0))/(1.0+1.27*sqrt(nu31)*(pow(Pr,2.0/3.0)-1.0));
		Nu  = max(nu1,nu2,nu3);
		Alpha[indexAlpha] = Nu*Kf[indexKf]/THd[indexTHd];
		//Alpha[indexAlpha] = 150.0;//force	
	}
	else if (mtth[indexmtth]==4)
	{
		Nu = 3.66;
		Alpha[indexAlpha] = Nu*Kf[indexKf]/THd[indexTHd];
	}
	else
	{
		Alpha[indexAlpha] = 0.0;//cut the transfer between soild and the fluid temperature outside the core
	}

	/* part for KK */

	if (mtth[indexmtth]==1 || j==6 || j==7)
	{
		k1 = 320.0/(Ref/THee[indexee])+6.0/pow(Ref/THee[indexee],0.1);
		KK[indexKK]=k1*(THee[indexee]/pow(1.0-THee[indexee],3))*(1.0/THd[indexTHd])*sqrt(U*U+V*V)/2.0;
		KK[indexKK]=KK[indexKK]/ROUf[indexROUf];
	}
	else if (mtth[indexmtth]==2 || mtth[indexmtth]==3 || mtth[indexmtth]==4 )
	{
		if (Ref<=2320.0)
		{
			k1 = 64.0/Ref;
		}
		else if (Ref<=1.0e5)
		{
			k1 = 0.3164/pow(Ref,0.25);
		}
		else
		{
			k1 = 0.0054+0.3964/pow(Ref,0.3);
		}
		KK[indexKK] = 10.0;
	}

    }


	

    
    

	// return Alpha[indexAlpha];
}

void TH3::setboundarycoefficient(PetscInt i, PetscInt j)
{
	PetscInt indexmtth,indexKseff,indexKf,indexROUf,indexKK;
	PetscInt indexKseffx,indexKseffy,indexTHCVdxl,indexTHCVdyl,indexKx,indexKfx,indexROUfx,indexKy,indexKfy,indexROUfy; 

	indexmtth  = 45*(j-1)+i-1;
	indexKseff = 45*(j-1)+i-1;
	indexKf    = 45*(j-1)+i-1;
	indexKfx   = 45*(j-1)+i-1;
	indexKfy   = 45*(j-1)+i-1;
	indexROUf  = 45*(j-1)+i-1;
	indexROUfx = 45*(j-1)+i-1;
	indexROUfy = 45*(j-1)+i-1;
	indexKK    = 45*(j-1)+i-1;
	indexKx    = 45*(j-1)+i-1;
	indexKy    = 45*(j-1)+i-1;
	indexKseffx= 45*(j-1)+i-1;
	indexKseffy= 45*(j-1)+i-1;
	indexTHCVdxl = 45*(j-1)+i-1;
	indexTHCVdyl = 45*(j-1)+i-1;
	/* set boundary coefficient */
    if (i == 1)
    {
    	Kseffx[indexKseffx] = Kseff[indexKseff]; 
    }
    else
    {
    	Kseffx[indexKseffx] = (Kseff[indexKseff]*THCVdxl[indexTHCVdxl]+Kseff[indexKseff+1]*THCVdxl[indexTHCVdxl+1])/(THCVdxl[indexTHCVdxl]+THCVdxl[indexTHCVdxl+1]);
    }

    if (j == 104)
    {
    	Kseffy[indexKseffy] = Kseff[indexKseff];
    }
    else
    {
    	Kseffy[indexKseffy] = (Kseff[indexKseff]*THCVdyl[indexTHCVdyl]+Kseff[indexKseff+45]*THCVdyl[indexTHCVdyl+45])/(THCVdyl[indexTHCVdyl]+THCVdyl[indexTHCVdyl+45]);
    }

    if (mtth[indexmtth]==1)
    {

    if (i == 22)
    {
    	Kx[indexKx]       = KK[indexKK];
    	Kfx[indexKfx]     = Kf[indexKf];
    	ROUfx[indexROUfx] = ROUf[indexROUf];
    }
    else
    {
    	Kx[indexKx]       = (KK[indexKK]*THCVdxl[indexTHCVdxl]+KK[indexKK+1]*THCVdxl[indexTHCVdxl+1])/(THCVdxl[indexTHCVdxl]+THCVdxl[indexTHCVdxl+1]);
    	Kfx[indexKfx]     = (Kf[indexKf]*THCVdxl[indexTHCVdxl]+Kf[indexKf+1]*THCVdxl[indexTHCVdxl+1])/(THCVdxl[indexTHCVdxl]+THCVdxl[indexTHCVdxl+1]);
    	ROUfx[indexROUfx] = (ROUf[indexROUf]*THCVdxl[indexTHCVdxl]+ROUf[indexROUf+1]*THCVdxl[indexTHCVdxl+1])/(THCVdxl[indexTHCVdxl]+THCVdxl[indexTHCVdxl+1]);
    }

    if (j == 87)
    {
    	Ky[indexKx]       = KK[indexKK];
    	Kfy[indexKfx]     = Kf[indexKf];
    	ROUfy[indexROUfx] = ROUf[indexROUf];
    }
    else
    {
    	Ky[indexKy]       = (KK[indexKK]*THCVdyl[indexTHCVdyl]+KK[indexKK+45]*THCVdyl[indexTHCVdyl+45])/(THCVdyl[indexTHCVdyl]+THCVdyl[indexTHCVdyl+45]);
    	Kfy[indexKfy]     = (Kf[indexKf]*THCVdyl[indexTHCVdyl]+Kf[indexKf+45]*THCVdyl[indexTHCVdyl+45])/(THCVdyl[indexTHCVdyl]+THCVdyl[indexTHCVdyl+45]);
    	ROUfy[indexROUfy] = (ROUf[indexROUf]*THCVdyl[indexTHCVdyl]+ROUf[indexROUf+45]*THCVdyl[indexTHCVdyl+45])/(THCVdyl[indexTHCVdyl]+THCVdyl[indexTHCVdyl+45]);     
    }

    }
}

PetscScalar TH3::getTsa1(PetscInt i, PetscInt j)
{
	PetscInt indexTHCVal,indexTHCVdxl,index;
	PetscScalar a1;

	indexTHCVal   = 46*(j-1)+i-1;
	indexTHCVdxl  = 45*(j-1)+i-1;
	index         = 45*(j-1)+i-1;
	if (i == 1)
	{
		a1 = 0.0;
	}
	else
	{
		a1 = THCVal[indexTHCVal]*Kseffx[index-1]/((THCVdxl[indexTHCVdxl]+THCVdxl[indexTHCVdxl-1])/2.0);
	}

	return a1;
}

PetscScalar TH3::getTsa2(PetscInt i, PetscInt j)
{
	PetscInt indexTHCVal,indexTHCVdxl,index;
	PetscScalar a2;

	indexTHCVal   = 46*(j-1)+i-1;
	indexTHCVdxl  = 45*(j-1)+i-1;
	index         = 45*(j-1)+i-1;
	if (i == 45)
	{
		a2 = THCVal[indexTHCVal+1]*Kseffx[index]/((THCVdxl[indexTHCVdxl]+THCVdxl[indexTHCVdxl])/2.0);
	}
	else
	{
		a2 = THCVal[indexTHCVal+1]*Kseffx[index]/((THCVdxl[indexTHCVdxl]+THCVdxl[indexTHCVdxl+1])/2.0);
	}

	return a2;
}

PetscScalar TH3::getTsa3(PetscInt i, PetscInt j)
{
	PetscInt indexTHCVbl,indexTHCVdyl,index;
	PetscScalar a3;

	indexTHCVbl  = 45*(j-1)+i-1;
	indexTHCVdyl = 45*(j-1)+i-1;
	index        = 45*(j-1)+i-1;
	if (j == 1)
	{
		a3 = THCVbl[indexTHCVbl]*Kseffy[index]/((THCVdyl[indexTHCVdyl]+THCVdyl[indexTHCVdyl])/2.0);
	}
	else
	{
		a3 = THCVbl[indexTHCVbl]*Kseffy[index-45]/((THCVdyl[indexTHCVdyl]+THCVdyl[indexTHCVdyl-45])/2.0);
	}

	return a3;
}

PetscScalar TH3::getTsa4(PetscInt i, PetscInt j)
{
	PetscInt indexTHCVbl,indexTHCVdyl,index;
	PetscScalar a4;

	indexTHCVbl  = 45*(j-1)+i-1;
	indexTHCVdyl = 45*(j-1)+i-1;
	index        = 45*(j-1)+i-1;
	if (j == 104)
	{
		a4 = THCVbl[indexTHCVbl+45]*Kseffy[index]/((THCVdyl[indexTHCVdyl]+THCVdyl[indexTHCVdyl])/2.0);
	}
	else
	{
		a4 = THCVbl[indexTHCVbl+45]*Kseffy[index]/((THCVdyl[indexTHCVdyl]+THCVdyl[indexTHCVdyl+45])/2.0);
	}

	return a4;
}

PetscScalar TH3::getTsa0(PetscInt i, PetscInt j,PetscScalar a1,PetscScalar a2,PetscScalar a3,PetscScalar a4)
{
	PetscInt indexTHCVvl,index;
	PetscScalar a0;

	indexTHCVvl = 45*(j-1)+i-1;
	index       = 45*(j-1)+i-1;
	a0 = -a1 - a2 - a3 - a4 - Alpha[index]*THCVvl[indexTHCVvl];

	return a0;
}

PetscScalar TH3::getTsrs(PetscInt i, PetscInt j,PetscScalar a2,PetscScalar a3,PetscScalar a4)
{
	PetscInt indexTHCVvl,index,indexTH,indexmtth;
	PetscScalar rs;

	indexTHCVvl = 45*(j-1)+i-1;
	index       = 45*(j-1)+i-1;
	indexmtth   = 45*(j-1)+i-1;
	indexTH     = 22*(j-12)+i-1;
	if (mtth[indexmtth]==1)
	{
		rs = -THCVvl[indexTHCVvl]*Alpha[index]*THTf[indexTH] - THCVvl[indexTHCVvl]* THQfth[index];
	}
	else
	{
		rs = 0.0;
	}
	
	if (i == 45)
	{
		rs = rs - a2*200.0;
	}
	if (j == 1)
	{
		rs = rs - a3*200.0;
	}
	if (j == 104)
	{
		rs = rs - a4*200.0;
	}

	return rs;
}

PetscScalar TH3::getTfa1(PetscInt i, PetscInt j)
{
	PetscInt index,indexTHCVal,indexTH;
	PetscScalar a1,Cpf;

	index = 45*(j-1)+i-1;
	indexTHCVal = 46*(j-1)+i-1;
	indexTH = (j-12)*22+i-1;
	Cpf = 5195.0;
    if (i == 1)
    {
    	a1 = 0.0;
    }
    else
    {
    	a1 = (1 - THee[index])*THCVal[indexTHCVal]*Kfx[index-1]/((THCVdxl[index]+THCVdxl[index-1])/2.0)+THCVal[indexTHCVal]*Cpf*THU[indexTH-1];
    }

    return a1;
}

PetscScalar TH3::getTfa2(PetscInt i, PetscInt j)
{
	PetscInt index, indexTHCVal;
	PetscScalar a2;

	index = 45*(j-1)+i-1;
	indexTHCVal = 46*(j-1)+i-1;
	if (i == 22)
	{
		a2 = 0.0;
	}
	else
	{
		a2 = (1 - THee[index])*THCVal[indexTHCVal+1]*Kfx[index]/((THCVdxl[index]+THCVdxl[index+1])/2.0);
	}

	return a2;
}

PetscScalar TH3::getTfa3(PetscInt i, PetscInt j)
{
	PetscInt index,indexTH;
	PetscScalar a3,Cpf;

	Cpf = 5195.0;
	index = 45*(j-1)+i-1;
	indexTH = (j-12)*22+i-1;
	if (j == 12)//if there is 12-1???
	{
		a3 = (1- THee[index])*THCVbl[index]*Kfy[index]/((THCVdyl[index]+THCVdyl[index])/2.0);
	}
	else
	{
		a3 = (1- THee[index])*THCVbl[index]*Kfy[index-45]/((THCVdyl[index]+THCVdyl[index-45])/2.0)+THCVbl[index]*Cpf*THV[indexTH-22];
	}

	return a3;
}

PetscScalar TH3::getTfa4(PetscInt i,PetscInt j)
{
	PetscInt index;
	PetscScalar a4;

	index = 45*(j-1)+i-1;
	if (j == 87)
	{
		a4 = 0.0;
	}
	else
	{
		a4 = (1- THee[index])*THCVbl[index+45]*Kfy[index]/((THCVdyl[index]+THCVdyl[index+45])/2.0);
	}

	return a4;
}

PetscScalar TH3::getTfa0(PetscInt i, PetscInt j,PetscScalar a1,PetscScalar a2,PetscScalar a3,PetscScalar a4)
{
	PetscInt index,indexTHCVal,indexTH;
	PetscScalar a0,Cpf;

	index = 45*(j-1)+i-1;
	indexTHCVal = 46*(j-1)+i-1;
	indexTH = (j-12)*22+i-1;
	Cpf = 5195.0;
	a0 = -a1 -a2 -a3 -a4 -THCVvl[index]*Alpha[index];
	if (i == 1)
	{
		a0 = a0 - THCVal[indexTHCVal+1]*Cpf*THU[indexTH];
	}
	else
	{
		a0 = a0 - THCVal[indexTHCVal+1]*Cpf*THU[indexTH] + THCVal[indexTHCVal]*Cpf*THU[indexTH-1];
	}

	if (j == 12)
	{
		a0 = a0 - THCVbl[index+45]*Cpf*THV[indexTH];
	}
	else
	{
		a0 = a0 - THCVbl[index+45]*Cpf*THV[indexTH] + THCVbl[index]*Cpf*THV[indexTH-22];
	}

	return a0;
}

PetscScalar TH3::getTfrs(PetscInt i, PetscInt j,PetscScalar a3)
{
	PetscInt index,indexTHTs;
	PetscScalar rs,Tfboundary,Vin,Cpf;

	Tfboundary = 250.0;
	Cpf = 5195.0;
	Vin = 0.129022e2;
	index = 45*(j-1)+i-1;
	indexTHTs = (j-1)*45+i-1;
	rs = -THCVvl[index]*Alpha[index]*THTs[indexTHTs];
	if (j == 12)
	{
		rs = rs - a3*Tfboundary- Tfboundary* THCVbl[index]*Cpf*Vin;
	}

	return rs;
}

PetscScalar TH3::getUrs(PetscInt i, PetscInt j)
{
	PetscInt index,indexTH;
	PetscScalar rs;

	index = 45*(j-1)+i-1;
	indexTH = (j-12)*22+i-1;
	if (i == 22)
	{
		rs = 0.0;
	}
	else
	{
		rs = -(THP[indexTH+1]- THP[indexTH])/(Kx[index]*(THCVdxl[index]+THCVdxl[index+1])/2.0);
	}

	return rs;
}

PetscScalar TH3::getVrs(PetscInt i, PetscInt j)
{
	PetscInt index,indexTH;
	PetscScalar rs,Pboundary;

	index = 45*(j-1)+i-1;
	indexTH = (j-12)*22+i-1;
	Pboundary = 7.0e6;
	if (j == 87)
	{
		rs = (-1.0*(Pboundary-THP[indexTH])/(Ky[index]*(THCVdyl[index]+THCVdyl[index])/2.0)+ROUfy[index]*THg[index]/Ky[index]);
	}
	else
	{
		rs = (-1.0*(THP[indexTH+22]-THP[indexTH])/(Ky[index]*(THCVdyl[index]+THCVdyl[index+45])/2.0)+ROUfy[index]*THg[index]/Ky[index]);
	}

	return rs;
}

PetscScalar TH3::getPa1(PetscInt i, PetscInt j)
{
	PetscInt index,indexTHCVal;
	PetscScalar a1;

	index = 45*(j-1)+i-1;
	indexTHCVal = 46*(j-1)+i-1;
	if (i == 1)
	{
		a1 = 0.0;
	}
	else
	{
		a1 = -THCVal[indexTHCVal]/(Kx[index-1]*(THCVdxl[index-1]+THCVdxl[index])/2.0);
	}

	return a1;
}

PetscScalar TH3::getPa2(PetscInt i,PetscInt j)
{
	PetscInt index,indexTHCVal;
	PetscScalar a2;

	index = 45*(j-1)+i-1;
	indexTHCVal = 46*(j-1)+i-1;
	if (i == 22)
	{
		a2 = 0.0;
	}
	else
	{
		a2 = -THCVal[indexTHCVal+1]/(Kx[index]*(THCVdxl[index]+THCVdxl[index+1])/2.0);
	}

	return a2;
}

PetscScalar TH3::getPa3(PetscInt i,PetscInt j)
{
	PetscInt index;
	PetscScalar a3;

	index = 45*(j-1)+i-1;
	if (j == 12)
	{
		a3 = 0.0;
	}
	else
	{
		a3 = -THCVbl[index]/(Ky[index-45]*(THCVdyl[index-45]+THCVdyl[index])/2.0);
	}

	return a3;
}

PetscScalar TH3::getPa4(PetscInt i,PetscInt j)
{
	PetscInt index;
	PetscScalar a4;

	index = 45*(j-1)+i-1;
	if (j == 87)
	{
		a4 = -THCVbl[index+45]/(Ky[index]*(THCVdyl[index]+THCVdyl[index])/2.0);
	}
	else
	{
		a4 = -THCVbl[index+45]/(Ky[index]*(THCVdyl[index+45]+THCVdyl[index])/2.0);
	}

	return a4;
}

PetscScalar TH3::getPa0(PetscInt i,PetscInt j, PetscScalar a1,PetscScalar a2,PetscScalar a3, PetscScalar a4)
{
	PetscScalar a0;

	a0 = -a1 -a2 -a3 -a4;
	return a0;
}

PetscScalar TH3::getPrs(PetscInt i,PetscInt j,PetscScalar a4)
{
	PetscInt index;
	PetscScalar rs,Vin,Pboundary;

	index = 45*(j-1)+i-1;
	Vin = 0.129022e2;
	Pboundary = 7.0e6;
	if (j == 12)
	{
		rs = 0.0;
	}
	else
	{
		rs = THCVbl[index]*ROUfy[index-45]*THg[index-45]/Ky[index-45] -THCVbl[index+45]*ROUfy[index]*THg[index]/Ky[index];
	}

	if (j == 12)
	{
		rs = rs + THCVbl[index]*Vin - THCVbl[index+45]*ROUfy[index]*THg[index]/Ky[index];
	}

	if (j == 87)
	{
		rs = rs - Pboundary*a4;
	}

	return rs;
}


void TH3::setCurrentVariables(const PetscScalar *u)
{
	PetscInt i,Interval1,Interval2,Interval3,Interval4,ith;
	Interval1 = 1672;
    Interval2 = 3344;
    Interval3 = 5016;
    Interval4 = 6688;
    ith       = 18720;


    for (i = 0; i < 1672; i++)
    {
      THP[i]  = u[i+ith];
      THTf[i] = u[i+Interval1+ith];
      THU[i]  = u[i+Interval2+ith];
      THV[i]  = u[i+Interval3+ith];
    }
    for (i = 0; i < 4680 ; i++)
    {
      THTs[i] = u[i+Interval4+ith];
    }

}

void TH3::setParameterAll()
{
	PetscInt    i,j,indexTH,indexTHTs;
	PetscScalar P,Tf,UU,V,Ts;


	for (i = 1; i < 45+1; i++)
    {
      for (j = 1; j < 104+1; j++)
      {
        if (i>=1 && i<=22 && j>=12 && j<=87)
        {
          indexTH = (j-12)*22+i-1;
          P       = THP[indexTH];
          Tf      = THTf[indexTH];
          // Ts      = user->THTs[indexTH];
          UU      = THU[indexTH];
          V       = THV[indexTH];
        }
        else
        {
          P  = 0.0;
          Tf = 0.0;
          UU = 0.0;
          V  = 0.0;
        }
        indexTHTs = (j-1)*45+i-1;
        Ts = THTs[indexTHTs];
        setparameter(i,j,Ts,Tf,P,UU,V);
      }
    }
}

void TH3::setBoundaryCoefficientAll()
{
	PetscInt i,j;
	
	for (i = 1; i < 45+1; i++)
    {
      for (j = 1; j < 104+1; j++)
      {
        setboundarycoefficient(i,j);
      }
    }

}

void TH3::setQf(PetscScalar *Qf)
{
	PetscInt i;

	for (i = 0; i < 4680; i++)
	{
		THQfth[i] = Qf[i];
	}

}

PetscScalar TH3::getTsTimeCoefficient(PetscInt i, PetscInt j)
{
	PetscInt    index9000;
	PetscScalar TSCoefficient;

	index9000 = 45*(j-1)+i-1;
	TSCoefficient = THCVvl[index9000]*(1.0 - THee[index9000]) * ROUs[index9000] * Cps[index9000];

	return TSCoefficient;
}

PetscScalar TH3::getTfTimeCoefficient(PetscInt i, PetscInt j)
{
	PetscInt  index9000;
	PetscScalar Cpf,TFCoefficient;

	Cpf = 5195.0;
	index9000 = 45*(j-1)+i-1;
	TFCoefficient = THCVvl[index9000] * THee[index9000] * ROUf[index9000] * Cpf ;

	return TFCoefficient;
}